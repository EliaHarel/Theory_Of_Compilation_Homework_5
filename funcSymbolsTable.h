//
// Created by EliaHarel on 23/12/2020.
//

#ifndef HOMEWORK_3_FUNCSYMBOLSTABLE_H
#define HOMEWORK_3_FUNCSYMBOLSTABLE_H

#include <map>
#include <vector>
#include "function.h"
#include "hw3_output.hpp"
#include "globalFuncs.h"

class FuncSymbolsTable {
    int curr_func;
    std::vector<Function> funcs_vec;
    std::map<std::string, int> funcs_map;
    bool main_func;

public:
    FuncSymbolsTable() : curr_func(-1), funcs_vec(std::vector<Function>()),
                         funcs_map(std::map<std::string, int>()),
                         main_func(false){}
//    static FuncSymbolsTable *funcs_table;

//    static FuncSymbolsTable& getSymbolFunc();

    bool isDefined(const std::string& id){
        return funcs_map.find(id) != funcs_map.end();
    }

    bool isValidName(const string& id, void* VarsSymbolsTable_t);

    void addFunc(const std::string& id, const std::vector<Var>& args, Types ret_type,
                 void* VarsSymbolsTable_t){
        if(!isValidName(id, VarsSymbolsTable_t)){
            errorDef(yylineno, id);
            exit(1);
        }

        int num_of_args = args.size();

        if(id.compare("main") == 0 && ret_type == Types_enum::VOID_TYPE && num_of_args == 0){
            main_func = true;
        }

        std::vector<Var> ordered_args;
        for(auto& iter : args){ ordered_args.insert(ordered_args.begin(), iter); }

        funcs_vec.emplace_back(id, num_of_args, ordered_args, ret_type);
        curr_func++;
        funcs_map[id] = curr_func;

        //print func
        if(id == "print" || id == "printi") return;

        std::string func_dec = "define " + TypeTollvmStr(ret_type.getType()) + " " +
                               funcs_vec[curr_func].getllvmName() + "(";

        for(int i = 0; i < num_of_args; i++){
            if(i > 0){
                func_dec += ", ";
            }
            func_dec += TypeTollvmStr(ordered_args[i].getVarType().getType());
        }

        func_dec += ") {";
        std::string arg_num_str = to_string(num_of_args);

        CodeBuffer::instance().emit(func_dec);
        CodeBuffer::instance().emit("%locals = alloca [50 x i32]");
        CodeBuffer::instance().emit("%locals_set = alloca [50 x [256 x i1]*]");
        //TODO: check numbers
/*        std::string temp_ptr_1 = Expression::gimmeANewCuteVar();

        CodeBuffer::instance().emit(
                temp_ptr_1 + " = getelementptr [50 x i32], [50 x i32]* %locals, i32 0, i32 0");
        std::string temp_ptr_2 = Expression::gimmeANewCuteVar();
        CodeBuffer::instance().emit(
                temp_ptr_2 + " = bitcast i32* " + temp_ptr_1 + " to i8*");
        CodeBuffer::instance().emit("call void @llvm.memset.p0i8.i64(i8* " + temp_ptr_2
                                    + ", i8 0, i64 1600 , i1 false)");


        temp_ptr_1 = Expression::gimmeANewCuteVar();
        CodeBuffer::instance().emit(temp_ptr_1 +
                                    " = getelementptr [50 x [256 x i1]*], [50 x [256 x i1]*]* %locals_set, [256 x i1]* 0, [256 x i1]* 0");
        temp_ptr_2 = Expression::gimmeANewCuteVar();
        CodeBuffer::instance().emit(
                temp_ptr_2 + " = bitcast [256 x i1]** " + temp_ptr_1 + " to i8*");
        CodeBuffer::instance().emit(
                "call void @llvm.memset.p0i8.i64(i8* " + temp_ptr_2 + ", i8 0, i64 400 , i1 false)");
*/

        CodeBuffer::instance().emit("%args = alloca [" + arg_num_str + " x i32]");
        CodeBuffer::instance().emit("%args_set = alloca [" + arg_num_str + " x [256 x i1]*]");

        for(int i = 0; i < num_of_args; i++){
            std::string new_var_name = Expression::gimmeANewCuteVar();
            if(ordered_args[i].getVarType().getType() == Types_enum::SET_TYPE){
                CodeBuffer::instance().emit(
                        new_var_name + " = getelementptr [" + arg_num_str + " x [256 x i1]*], [" +
                        arg_num_str + " x [256 x i1]*]* %args_set, [256 x i1]* 0, [256 x i1]* " +
                        to_string(i));
                std::string set_alloc = Expression::gimmeANewCuteVar();
                CodeBuffer::instance().emit(set_alloc + " = alloca [256 x i1]");
                CodeBuffer::instance().emit(
                        "store [256 x i1]* " + set_alloc + ", [256 x i1]** " + new_var_name);

                CodeBuffer::instance().emit("store i256 %" + to_string(i) + ", [256 x i1]* " + set_alloc);

            }else if(ordered_args[i].getVarType() == Types_enum::BOOL_TYPE){
                CodeBuffer::instance().emit(
                        new_var_name + " = getelementptr [" + arg_num_str + " x i32], [" + arg_num_str +
                        " x i32]* %args, i32 0, i32 " + to_string(i));
                std::string bool_name = Expression::gimmeANewCuteVar();
                CodeBuffer::instance().emit(bool_name + " = zext i1 %" + to_string(i) + " to i32");
                CodeBuffer::instance().emit("store i32 " + bool_name + ", i32* " + new_var_name);
            }else{
                CodeBuffer::instance().emit(
                        new_var_name + " = getelementptr [" + arg_num_str + " x i32], [" + arg_num_str +
                        " x i32]* %args, i32 0, i32 " + to_string(i));
                CodeBuffer::instance().emit("store i32 %" + to_string(i) + ", i32* " + new_var_name);
            }
        }
    }


    static void afterFunc(const Types& type){
        printRet(type);
        CodeBuffer::instance().emit("}");
    }

    static void printRet(const Types& type){
        CodeBuffer::instance().emit(
                "ret " + TypeTollvmStr(type.getType()) + " " + defaultVal(type.getType()));
    }


    static void returnExp(const Expression& exp){
        switch (exp.type.getType()){
            case Types_enum::INT_TYPE:
            case Types_enum::BYTE_TYPE:
                CodeBuffer::instance().emit("ret " + TypeTollvmStr(exp.type.getType()) + " " + exp.var_name);
                break;
            case Types_enum::BOOL_TYPE:{
                std::string true_label = CodeBuffer::instance().genLabel();
                CodeBuffer::instance().emit("ret i1 1");
                std::string false_label = CodeBuffer::instance().genLabel();
                CodeBuffer::instance().emit("ret i1 0");
                CodeBuffer::instance().bpatch(exp.true_list, true_label);
                CodeBuffer::instance().bpatch(exp.false_list, false_label);
                break;
            }
            case Types_enum::SET_TYPE:{
                std::string loaded_arr = Expression::gimmeANewCuteVar();
                CodeBuffer::instance().emit(loaded_arr + " = load i256, i256* " + exp.var_name);
                CodeBuffer::instance().emit("ret i256 " + loaded_arr);
                /*   std::string ret_val = Expression::gimmeANewCuteVar();
                   CodeBuffer::instance().emit(ret_val + " =  call i8* @malloc(i64 32)");
                   Expression dest_set (Types_enum::SET_TYPE);
                   CodeBuffer::instance().emit(dest_set.var_name + " = bitcast i8* " + ret_val + " to [256 x i1]*");

                   Expression::handleSet(exp, dest_set, "copy");
                   CodeBuffer::instance().emit("ret [256 x i1]* " + dest_set.var_name);
                   break;*/


            }
            default:
                break;
        }
    }

    static string defaultVal(Types_enum type){
        string val_str;
        switch (type){
            case Types_enum::INT_TYPE :
                val_str = "0";
                break;
            case Types_enum::BYTE_TYPE :
                val_str = "0";
                break;
            case Types_enum::BOOL_TYPE :
                val_str = "0";
                break;
            case Types_enum::VOID_TYPE :
                val_str = "";
                break;
            case Types_enum::SET_TYPE :
                val_str = "0";
                break;
            default:
                break;
        }
        return val_str;

    }

    static string TypeTollvmStr(Types_enum type){
        string type_str;
        switch (type){
            case Types_enum::INT_TYPE :
            case Types_enum::BYTE_TYPE :
                type_str = "i32";
                break;
            case Types_enum::BOOL_TYPE :
                type_str = "i1";
                break;
            case Types_enum::VOID_TYPE :
                type_str = "void";
                break;
            case Types_enum::SET_TYPE :
                type_str = "i256";
                break;
            default:
                break;
        }
        return type_str;
    }

    Expression callFunc(const std::string& id, std::vector<Expression> exps_vec){
        if(!isDefined(id)){
            errorUndefFunc(yylineno, id);
            exit(1);
        }

        std::vector<Var> args = funcs_vec[funcs_map[id]].args;

        std::vector<std::string> args_types;
        for(auto& arg : args){
            args_types.emplace_back(enumToString(arg.getVarType()));
        }

        if(args.size() != exps_vec.size()){
            errorPrototypeMismatch(yylineno, id, args_types);
            exit(1);
        }

        int back_index = exps_vec.size() - 1;
        for(int i = 0; i < args.size(); i++){
            if(args[i].getVarType() != exps_vec[back_index].type){
                if(!(args[i].getVarType() == Types_enum::INT_TYPE &&
                     exps_vec[back_index].type == Types_enum::BYTE_TYPE)){
                    errorPrototypeMismatch(yylineno, id, args_types);
                    exit(1);
                }
            }
            back_index--;
        }

        return printCallingFunc(id, exps_vec);
    }

    Expression printCallingFunc(const std::string& id, const std::vector<Expression>& exps_vec){
        std::vector<Expression> ordered_params;
        for(int i = exps_vec.size() - 1; i >= 0; i--){
            ordered_params.emplace_back(exps_vec[i]);
        }

        Function func = funcs_vec[funcs_map[id]];
        Expression ret_exp(func.getRetType());

        std::string func_call;
        if(func.getRetType() != Types_enum::VOID_TYPE){
            func_call += ret_exp.var_name + " = ";
        }

        func_call += "call " + TypeTollvmStr(func.getRetType().getType()) + " " + func.getllvmName() + "( ";
        for(int i = 0; i < ordered_params.size(); i++){
            if(i > 0){
                func_call += ", ";
            }
            switch (ordered_params[i].type.getType()){
                case Types_enum::INT_TYPE:
                case Types_enum::BYTE_TYPE:
                    func_call += "i32 " + ordered_params[i].var_name;
                    break;
                case Types_enum::BOOL_TYPE:{
                    std::string true_list_label = CodeBuffer::instance().genLabel();
                    int true_loc = CodeBuffer::instance().emit("br label @");
                    std::string false_list_label = CodeBuffer::instance().genLabel();
                    int false_loc = CodeBuffer::instance().emit("br label @");

                    CodeBuffer::instance().bpatch(ordered_params[i].true_list, true_list_label);
                    CodeBuffer::instance().bpatch(ordered_params[i].false_list, false_list_label);

                    std::string new_var = Expression::gimmeANewCuteVar();
                    std::string exit = CodeBuffer::instance().genLabel();
                    CodeBuffer::instance().emit(
                            new_var + " = phi i1 [ 1, %" + true_list_label + " ], [ 0, %" + false_list_label +
                            " ]");

                    CodeBuffer::instance().bpatch(CodeBuffer::makelist({true_loc, FIRST}), exit);
                    CodeBuffer::instance().bpatch(CodeBuffer::makelist({false_loc, FIRST}), exit);

                    func_call += "i1 " + new_var;
                    break;
                }
                case Types_enum::SET_TYPE:{
                    std::string loaded_arr = Expression::gimmeANewCuteVar();
                    CodeBuffer::instance().emit(loaded_arr + " = load i256, i256* "
                                                + ordered_params[i].var_name);
                    func_call += "i256 " + loaded_arr;
                    break;
                }
                case Types_enum::STRING_TYPE:{
                    func_call += "i8* getelementptr ([" + to_string(ordered_params[i].str_length) +
                                 " x i8], [" + to_string(ordered_params[i].str_length) + " x i8]* " +
                                 ordered_params[i].var_name + ", i32 0, i32 0)";
                }
                default:
                    break;
            }
        }

        func_call += ")";
        CodeBuffer::instance().emit(func_call);
        return ret_exp;
    }

    bool isMain(){
        return main_func;
    }

    void removeFuncs(){
        for(auto& func : funcs_vec){
            std::string ret_type = enumToString(func.getRetType());
            std::vector<std::string> args_types;
            for(auto& arg : func.args){
                args_types.emplace_back(enumToString(arg.getVarType()));
            }
//            output::printID(func.getID(), 0, output::makeFunctionType(ret_type, args_types));
        }
    }
};


#endif //HOMEWORK_3_FUNCSYMBOLSTABLE_H
