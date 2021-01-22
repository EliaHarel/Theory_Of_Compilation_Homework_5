//
// Created by EliaHarel on 23/12/2020.
//

#ifndef HOMEWORK_3_VARSSYMBOLSTABLE_H
#define HOMEWORK_3_VARSSYMBOLSTABLE_H

#include <map>
#include "scope.h"
#include "attributes.hpp"
#include "funcSymbolsTable.h"
#include "globalFuncs.h"

class VarsSymbolsTable {
    int curr_scope;
    std::vector<Scope> scopes;
    std::map<std::string, std::pair<int, int>> var_maps;
    FuncSymbolsTable* funcs_table;

public:

    VarsSymbolsTable() : curr_scope(-1), scopes(std::vector<Scope>()),
                         var_maps(std::map<std::string, std::pair<int, int>>()), funcs_table(nullptr){
    }

    void setFuncsTable(void* funcs_table_t){
        funcs_table = (FuncSymbolsTable*) funcs_table_t;
    }
//    static VarsSymbolsTable& getSymbolVar();

    void addFirstScope(){
        addScope();

        std::vector<Var> arg1 = {Var(Types_enum::STRING_TYPE)};
        std::vector<Var> arg2 = {Var(Types_enum::INT_TYPE)};
        funcs_table->addFunc("print", arg1, Types_enum::VOID_TYPE, this);
        funcs_table->addFunc("printi", arg2, Types_enum::VOID_TYPE, this);
    }

    void addScope(){
        int offset = 0;
        bool isInWhile = false;
        bool isInFunc = false;
        Types type = Types_enum::UNDEFINED_TYPE;
        if(curr_scope != -1){
            offset = scopes[curr_scope].getOffset();
            isInWhile = scopes[curr_scope].getWhile();
            isInFunc = scopes[curr_scope].getInFunc();
            type = scopes[curr_scope].getScopeType();

        }
        scopes.emplace_back(offset, isInWhile, isInFunc, type);
        curr_scope++;
    }

    void addVar(std::string& id, Types type, bool func = false){
        if(!isValidName(id)){
            errorDef(yylineno, id);
            exit(1);
        }

        int index;
        if(func){
            index = scopes[curr_scope].addFuncVar(id, type, curr_scope);
        }else{
            index = scopes[curr_scope].addVar(id, type, curr_scope);
        }
        var_maps[id] = {curr_scope, index};

        string var_name = scopes[curr_scope].vars[index].getVarName();
        switch(type.getType()){
            case Types_enum:: INT_TYPE :
                CodeBuffer::instance().emit(var_name = " add i32 0, 0");
                break;
            case Types_enum:: BYTE_TYPE :
                CodeBuffer::instance().emit(var_name = " add i32 0, 0");
                break;
            case Types_enum:: BOOL_TYPE :
                CodeBuffer::instance().emit(var_name = " add i1 0, 0");
                break;
            case Types_enum:: SET_TYPE :
                CodeBuffer::instance().emit(var_name +" =  alloca [256 x i1]");

                // TODO: need to initialize
                break;
            default:
                break;
        }
    }

    void addVarWithExp(std::string& id, Types type, const Expression& exp){
        if(!isValidName(id)){
            errorDef(yylineno, id);
            exit(1);
        }

        int index = scopes[curr_scope].addVar(id, type, curr_scope);
        var_maps[id] = {curr_scope, index};

        string var_name = scopes[curr_scope].vars[index].getVarName();

        switch(type.getType()){
            case Types_enum:: INT_TYPE :
                CodeBuffer::instance().emit(var_name = " add i32 " + exp.var_name + ", 0");
                break;
            case Types_enum:: BYTE_TYPE :
                CodeBuffer::instance().emit(var_name = " add i32 " + exp.var_name + ", 0");
                break;
            case Types_enum:: BOOL_TYPE :
                CodeBuffer::instance().emit(var_name = " add i1 " + exp.var_name + ", 0");
                break;
            case Types_enum:: SET_TYPE :
                CodeBuffer::instance().emit(var_name = " getelementptr [256 * i1], [256 * i1]* " + exp.var_name +  "i1 0, i1 0 ");
                break;
            default:
                break;
        }
    }


    void addScopeFromFunc(const std::string& id, std::vector<Var>& args, const Types& ret_type){
        //assuming first scope
        int offset = -1;
        scopes.emplace_back(offset, false, true, ret_type);
        curr_scope++;

        // moving backwards, to check what to return in case of a duplication
        /*        for(auto iter = args.rbegin(); iter != args.rend(); iter++){
            addVar(iter.getId(), iter.getVarType(), true);
        }*/
        for(int i = args.size() - 1; i >= 0; --i){
            std::string temp_id = args[i].getId();
            Types temp_type = args[i].getVarType();

            addVar(temp_id, temp_type, true);
        }

        scopes[curr_scope].setOffset();
    }

    void deleteScope(bool last = false){
        if(last && !funcs_table->isMain()){
            errorMainMissing();
            exit(1);
        }

        output::endScope();

        for(auto& iter : scopes[curr_scope].vars){
            output::printID(iter.getId(), iter.getOffset(), enumToString(iter.getVarType()));
            var_maps.erase(iter.getId());
        }
        scopes.pop_back();
        curr_scope--;

        if(last){
            funcs_table->removeFuncs();
//            delete FuncSymbolsTable::funcs_table;
//            delete vars_table;
        }
    }

    bool isDefined(const std::string& id){
        return var_maps.find(id) != var_maps.end();
    }

    bool isValidName(const std::string& id){
        if(isDefined(id)){
            return false;
        }
        return !funcs_table->isDefined(id);
    }

    Types getVarSymbolTableType(const std::string& id){
        if(!isDefined(id)){
            errorUndef(yylineno, id);
            exit(1);
        }
        int scope = var_maps[id].first;
        int index = var_maps[id].second;

        return scopes[scope].vars[index].getVarType();
    }

    Var getVarSymbolTable(const std::string& id){
        if(!isDefined(id)){
            errorUndef(yylineno, id);
            exit(1);
        }
        int scope = var_maps[id].first;
        int index = var_maps[id].second;

        return scopes[scope].vars[index];
    }

    Expression getExp(const std::string& id){
        Types type = getVarSymbolTableType(id);
        return Expression(type);
    }

    void typeCheckAndAssign(const std::string& id, const Expression& exp){
        Types type = getVarSymbolTableType(id);
        if(exp.type != type && !(type == Types_enum::INT_TYPE && exp.type == Types_enum::BYTE_TYPE)){
            errorMismatch(yylineno);
            exit(1);
        }

        Var var = getVarSymbolTable(id);
        var.setVarName();
        switch(type.getType()){
            case Types_enum:: INT_TYPE :
                CodeBuffer::instance().emit(var.getVarName() = " add i32 " + exp.var_name + ", 0");
                break;
            case Types_enum:: BYTE_TYPE :
                CodeBuffer::instance().emit(var.getVarName() = " add i32 " + exp.var_name + ", 0 ");
                break;
            case Types_enum:: BOOL_TYPE :
                CodeBuffer::instance().emit(var.getVarName() = " add i1 " + exp.var_name + ", 0 ");
                break;
            case Types_enum:: SET_TYPE :
                CodeBuffer::instance().emit(var.getVarName() = " getelementptr [256 * i1], [256 * i1]* " + exp.var_name +  "i1 0, i1 0 ");
                break;
            default:
                break;
        }


    }

    void checkWhile(const std::string& state){
        if(!scopes[curr_scope].getWhile()){
            if(state.compare("break") == 0){
                errorUnexpectedBreak(yylineno);
            }else{ // state == "continue"
                errorUnexpectedContinue(yylineno);
            }
            exit(1);
        }
    }

    void setWhile(){
        scopes[curr_scope].setWhile(true);
    }

    void checkRetType(Types type){
        Types ret_type = scopes[curr_scope].getScopeType();
        if(type != ret_type){
            if(!(type == Types_enum::BYTE_TYPE && ret_type == Types_enum::INT_TYPE)){
                errorMismatch(yylineno);
                exit(1);
            }
        }
    }

};

#endif //HOMEWORK_3_VARSSYMBOLSTABLE_H
