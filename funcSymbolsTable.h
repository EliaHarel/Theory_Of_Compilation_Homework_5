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

        if(id.compare("main") == 0 && ret_type == Types_enum::VOID_TYPE && args.size() == 0){
            main_func = true;
        }

        std::vector<Var> ordered_args;
        for(auto& iter : args){
            ordered_args.insert(ordered_args.begin(), iter);
        }

        funcs_vec.emplace_back(id, ordered_args.size(), ordered_args, ret_type);
        curr_func++;
        funcs_map[id] = curr_func;

        //print func
        string func_dec = "define " + TypeTollvmStr(ret_type.getType()) + " " + funcs_vec[curr_func].getllvmName() + "(";
        for(int i=0; i< ordered_args.size(); i++){
            if(i>0){
                func_dec += ", ";
            }
            func_dec+= TypeTollvmStr(ordered_args[i].getVarType().getType());
        }
        func_dec += ") {";
        CodeBuffer::instance().emit(func_dec);
        CodeBuffer::instance().emit("%locals = alloca [50 x i32]");
    }

    void afterFunc(Types type){
        printRet(type);
        CodeBuffer::instance().emit("}");
    }

    static void printRet(Types type){
        string func_end;
        if(type.getType() == Types_enum::SET_TYPE){
            string ret_set = Expression::gimmeANewCuteVar();
            CodeBuffer::instance().emit(ret_set + " = alloca [256 x i1]");
            Expression new_var(type, ret_set);
            Expression::handleSet(new_var, Expression(), "init");
            func_end = "ret [256 x i1]* " + ret_set;
        }else{
            func_end = "ret " + TypeTollvmStr(type.getType()) + " " + defaultVal(type.getType());
        }
        CodeBuffer::instance().emit(func_end);
    }

    static string defaultVal (Types_enum type){
        string val_str;
        switch(type){
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
            default:
                break;
        }
        return type_str;

    }

    static string TypeTollvmStr (Types_enum type){
        string type_str;
        switch(type){
            case Types_enum::INT_TYPE :
                type_str = "i32";
                break;
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

    Types checkFunc(const std::string& id, std::vector<Types> types_vec){
        if(!isDefined(id)){
            errorUndefFunc(yylineno, id);
            exit(1);
        }

        std::vector<Var> args = funcs_vec[funcs_map[id]].args;

        std::vector<std::string> args_types;
        for(auto& arg : args){
            args_types.emplace_back(enumToString(arg.getVarType()));
        }

        if(args.size() != types_vec.size()){
            errorPrototypeMismatch(yylineno, id, args_types);
            exit(1);
        }

        int back_index = types_vec.size() - 1;
        for(int i = 0; i < args.size(); i++){
            if(args[i].getVarType() != types_vec[back_index]){
                if(!(args[i].getVarType() == Types_enum::INT_TYPE &&
                     types_vec[back_index] == Types_enum::BYTE_TYPE)){
                    errorPrototypeMismatch(yylineno, id, args_types);
                    exit(1);
                }
            }
            back_index--;
        }

        return funcs_vec[funcs_map[id]].getRetType();
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
            output::printID(func.getID(), 0, output::makeFunctionType(ret_type, args_types));
        }
    }
};


#endif //HOMEWORK_3_FUNCSYMBOLSTABLE_H
