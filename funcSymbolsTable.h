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
                         main_func(false) {}
//    static FuncSymbolsTable *funcs_table;

//    static FuncSymbolsTable& getSymbolFunc();

    bool isDefined(const std::string &id) {
        return funcs_map.find(id) != funcs_map.end();
    }

    bool isValidName(const string &id, void *VarsSymbolsTable_t);

    void addFunc(const std::string &id, const std::vector<Var> &args, Types ret_type,
                 void *VarsSymbolsTable_t) {
        if (!isValidName(id, VarsSymbolsTable_t)) {
            errorDef(yylineno, id);
            exit(1);
        }

        int num_of_args = args.size();

        if (id.compare("main") == 0 && ret_type == Types_enum::VOID_TYPE && num_of_args == 0) {
            main_func = true;
        }

        std::vector<Var> ordered_args;
        for (auto &iter : args) { ordered_args.insert(ordered_args.begin(), iter); }

        funcs_vec.emplace_back(id, num_of_args, ordered_args, ret_type);
        curr_func++;
        funcs_map[id] = curr_func;

        //print func
        string func_dec = "define " + TypeTollvmStr(ret_type.getType()) + " " +
                          funcs_vec[curr_func].getllvmName() + "(";

        for (int i = 0; i < num_of_args; i++) {
            if (i > 0) {
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
        CodeBuffer::instance().emit("call void @llvm.memset.p0i8.i64(i8* @locals, i8 0, i64 1600 , i1 false)");
        CodeBuffer::instance().emit("call void @llvm.memset.p0i8.i64(i8* @locals_set, i8 0, i64 400 , i1 false)");

        CodeBuffer::instance().emit("%args = alloca [" + arg_num_str + " x i32]");
        CodeBuffer::instance().emit("%args_set = alloca [" + arg_num_str + " x [256 x i1]*");


        for (int i = 0; i < num_of_args; i++) {
            std::string new_var_name = Expression::gimmeANewCuteVar();
            if (ordered_args[i].getVarType().getType() == Types_enum::SET_TYPE) {
                CodeBuffer::instance().emit(new_var_name + " = getelementptr [" + arg_num_str + " x [256 x i1]*], [" +
                                            arg_num_str + " x [256 x i1]*]* %args_set, [256 x i1]* 0, [256 x i1]* " +
                                            to_string(i));
                CodeBuffer::instance().emit("store [256 x i1]* %" + to_string(i) + ", [256 x i1]** " + new_var_name);
            } else if (ordered_args[i].getVarType() == Types_enum::BOOL_TYPE) {
                CodeBuffer::instance().emit(
                        new_var_name + " = getelementptr [" + arg_num_str + " x i32], [" + arg_num_str +
                        " x i32]* %args, i32 0, i32 " + to_string(i));
                std::string bool_name = Expression::gimmeANewCuteVar();
                CodeBuffer::instance().emit(bool_name + " = zext i1 %" + to_string(i) + "  to i32");
                CodeBuffer::instance().emit("store i32 %" + to_string(i) + ", i32* " + bool_name);
            } else {
                CodeBuffer::instance().emit(
                        new_var_name + " = getelementptr [" + arg_num_str + " x i32], [" + arg_num_str +
                        " x i32]* %args, i32 0, i32 " + to_string(i));
                CodeBuffer::instance().emit("store i32 %" + to_string(i) + ", i32* " + new_var_name);
            }
        }
    }


    static void afterFunc(const Types& type) {
        printRet(type);
        CodeBuffer::instance().emit("}");
    }

    static void printRet(const Types& type) {
        CodeBuffer::instance().emit("ret " + TypeTollvmStr(type.getType()) + " " + defaultVal(type.getType()));
    }


    static void returnExp (const Expression& exp){
        switch (exp.type.getType()) {
            case Types_enum::INT_TYPE:
            case Types_enum::BYTE_TYPE:
                CodeBuffer::instance().emit("ret " + TypeTollvmStr(exp.type.getType()) + " " + exp.var_name);
                break;
            case Types_enum::BOOL_TYPE:
            {
                std::string true_label = CodeBuffer::instance().genLabel();
                CodeBuffer::instance().emit("ret i1 1");
                std::string false_label = CodeBuffer::instance().genLabel();
                CodeBuffer::instance().emit("ret i1 0");
                CodeBuffer::instance().bpatch(exp.true_list, true_label);
                CodeBuffer::instance().bpatch(exp.false_list, false_label);
                break;
            }
            case Types_enum::SET_TYPE:
            {
                std::string ret_val = Expression::gimmeANewCuteVar();
                CodeBuffer::instance().emit(ret_val + " =  call i8* @malloc(i64 32)");
                Expression dest_set (Types_enum::SET_TYPE);
                CodeBuffer::instance().emit(dest_set.var_name + " = bitcast i8* " + ret_val + " to [256 x i1]*");

                Expression::handleSet(exp, dest_set, "copy");
                CodeBuffer::instance().emit("ret [256 x i1]* " + dest_set.var_name);
                break;
            }
            default:
                break;
        }
    }

    static string defaultVal(Types_enum type) {
        string val_str;
        switch (type) {
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
                val_str = "null";
                break;
            default:
                break;
        }
        return val_str;

    }

    static string TypeTollvmStr(Types_enum type) {
        string type_str;
        switch (type) {
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
                type_str = "[256 x i1]*";
                break;
            default:
                break;
        }
        return type_str;
    }

    Types checkFunc(const std::string &id, std::vector<Types> types_vec) {
        if (!isDefined(id)) {
            errorUndefFunc(yylineno, id);
            exit(1);
        }

        std::vector<Var> args = funcs_vec[funcs_map[id]].args;

        std::vector<std::string> args_types;
        for (auto &arg : args) {
            args_types.emplace_back(enumToString(arg.getVarType()));
        }

        if (args.size() != types_vec.size()) {
            errorPrototypeMismatch(yylineno, id, args_types);
            exit(1);
        }

        int back_index = types_vec.size() - 1;
        for (int i = 0; i < args.size(); i++) {
            if (args[i].getVarType() != types_vec[back_index]) {
                if (!(args[i].getVarType() == Types_enum::INT_TYPE &&
                      types_vec[back_index] == Types_enum::BYTE_TYPE)) {
                    errorPrototypeMismatch(yylineno, id, args_types);
                    exit(1);
                }
            }
            back_index--;
        }

        return funcs_vec[funcs_map[id]].getRetType();
    }

    bool isMain() {
        return main_func;
    }

    void removeFuncs() {
        for (auto &func : funcs_vec) {
            std::string ret_type = enumToString(func.getRetType());
            std::vector<std::string> args_types;
            for (auto &arg : func.args) {
                args_types.emplace_back(enumToString(arg.getVarType()));
            }
            output::printID(func.getID(), 0, output::makeFunctionType(ret_type, args_types));
        }
    }
};


#endif //HOMEWORK_3_FUNCSYMBOLSTABLE_H
