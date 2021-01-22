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
