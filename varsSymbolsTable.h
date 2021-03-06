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
    FuncSymbolsTable *funcs_table;

public:

    VarsSymbolsTable() : curr_scope(-1), scopes(std::vector<Scope>()),
                         var_maps(std::map<std::string, std::pair<int, int>>()), funcs_table(nullptr) {
    }

    void setFuncsTable(void *funcs_table_t) {
        funcs_table = (FuncSymbolsTable *) funcs_table_t;
    }
//    static VarsSymbolsTable& getSymbolVar();

    void addFirstScope() {
        addScope();

        std::vector<Var> arg1 = {Var(Types_enum::STRING_TYPE)};
        std::vector<Var> arg2 = {Var(Types_enum::INT_TYPE)};
        funcs_table->addFunc("print", arg1, Types_enum::VOID_TYPE, this);
        funcs_table->addFunc("printi", arg2, Types_enum::VOID_TYPE, this);
    }

    void addScope() {
        int offset = 0;
        bool isInWhile = false;
        bool isInFunc = false;
        Types type = Types_enum::UNDEFINED_TYPE;
        if (curr_scope != -1) {
            offset = scopes[curr_scope].getOffset();
            isInWhile = scopes[curr_scope].getWhile();
            isInFunc = scopes[curr_scope].getInFunc();
            type = scopes[curr_scope].getScopeType();

        }
        scopes.emplace_back(offset, isInWhile, isInFunc, type);
        curr_scope++;
    }

    void addVar(std::string &id, const Types &type, bool func = false) {
        if (!isValidName(id)) {
            errorDef(yylineno, id);
            exit(1);
        }

        int index;
        if (func) {
            index = scopes[curr_scope].addFuncVar(id, type, curr_scope);
        } else {
            index = scopes[curr_scope].addVar(id, type, curr_scope);

            int offset = scopes[curr_scope].vars[index].getOffset();
            std::string ptr = Expression::gimmeANewCuteVar();

            // TODO Maybe malloc here, if not, remember to malloc before passing a set as an argument to a function
            // Conjecture: one cannot interfere with a caller function's stack when in the callee function.
            if (type.getType() == Types_enum::SET_TYPE) {
                std::string new_set = Expression::gimmeANewCuteVar();
                std::string low = Expression::gimmeANewCuteVar();
                std::string  high = Expression::gimmeANewCuteVar();
                CodeBuffer::instance().emit(low + " = add i32 0, " + to_string(type.getSetRange().first));
                CodeBuffer::instance().emit(high + " = add i32 0, " + to_string(type.getSetRange().second));
                CodeBuffer::instance().emit(new_set + " = call i310 @buildSet(i256 0, i32 " + low + ", i32 " + high + ")");

                CodeBuffer::instance().emit(
                        ptr + " = getelementptr inbounds [50 x i310], [50 x i310]* %locals_set, i310 0, i310 " + to_string(offset));
                CodeBuffer::instance().emit("store i310 " +new_set + ", i310* " + ptr);

/*
                CodeBuffer::instance().emit(
                        ptr + " = getelementptr inbounds [50 x i256], [50 x i256]* %locals_set, i256 0, i256 " + to_string(offset));
                CodeBuffer::instance().emit("store i256 0, i256* " + ptr);
*/

                /*Expression new_set(Types_enum::SET_TYPE);
                CodeBuffer::instance().emit(new_set.var_name + " = alloca [256 x i1]");
                Expression::handleSet(new_set, Expression(), "init");
                CodeBuffer::instance().emit(
                        ptr + " = getelementptr inbounds [50 x [256 x i1]*] , [50 x [256 x i1]*]* %locals_set, i1 0, i1 " +
                        to_string(offset));
                CodeBuffer::instance().emit("store [256 x i1]* " + new_set.var_name + ", [256 x i1]** " + ptr);*/
            } else {
                CodeBuffer::instance().emit(
                        ptr + " = getelementptr inbounds [50 x i32], [50 x i32]* %locals, i32 0, i32 " + to_string(offset));
                CodeBuffer::instance().emit("store i32 0, i32* " + ptr);
            }
        }
        var_maps[id] = {curr_scope, index};


/*
        switch (type.getType()){
            case Types_enum::INT_TYPE :
                CodeBuffer::instance().emit(var_name + " =  add i32 0, 0");
                break;
            case Types_enum::BYTE_TYPE :
                CodeBuffer::instance().emit(var_name + " = add i32 0, 0");
                break;
            case Types_enum::BOOL_TYPE :
                CodeBuffer::instance().emit(var_name + " = add i1 0, 0");
                break;
            case Types_enum::SET_TYPE :
                CodeBuffer::instance().emit(var_name + " =  alloca [256 x i1]");

                // TODO: need to initialize
                break;
            default:
                break;
        }
*/
    }

    void addVarWithExp(std::string &id, const Types &type, const Expression &exp) {
        if (!isValidName(id)) {
            errorDef(yylineno, id);
            exit(1);
        }

        int index = scopes[curr_scope].addVar(id, type, curr_scope);
        var_maps[id] = {curr_scope, index};
        assign(index, type, exp, curr_scope);
    }

    void typeCheckAndAssign(const std::string &id, const Expression &exp) {
        Types type = getVarSymbolTableType(id);
        if (exp.type.getType() != type.getType() &&
            !(type == Types_enum::INT_TYPE && exp.type == Types_enum::BYTE_TYPE)) {
            errorMismatch(yylineno);
            exit(1);
        }
        int var_scope_index = var_maps[id].first;
        int index = var_maps[id].second;
        assign(index, type, exp, var_scope_index);
    }

    // TODO : Negative index for function arguments, goto arguments stack instead of the regular stack (also for sets).
    void assign(int index, const Types &type, const Expression &exp, int var_scope_index) {

        std::string ptr = Expression::gimmeANewCuteVar();
        switch (type.getType()) {
            case Types_enum::INT_TYPE :
            case Types_enum::BYTE_TYPE :
                printGetPtr(ptr, index, var_scope_index);
                CodeBuffer::instance().emit("store i32 " + exp.var_name + ", i32* " + ptr);
                break;
            case Types_enum::BOOL_TYPE : {
                int location = CodeBuffer::instance().emit("br label @");
                std::string true_label = CodeBuffer::instance().genLabel();
                printGetPtr(ptr, index, var_scope_index);
                CodeBuffer::instance().emit("store i32 1, i32* " + ptr);
                int loc1 = CodeBuffer::instance().emit("br label @");
                std::string false_label = CodeBuffer::instance().genLabel();
                ptr = Expression::gimmeANewCuteVar();
                printGetPtr(ptr, index, var_scope_index);
                CodeBuffer::instance().emit("store i32 0, i32* " + ptr);
                int loc2 = CodeBuffer::instance().emit("br label @");
                std::string end_label = CodeBuffer::instance().genLabel();

                CodeBuffer::instance().bpatch(exp.true_list, true_label);
                CodeBuffer::instance().bpatch(exp.false_list, false_label);
                CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc1, FIRST}), end_label);
                CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc2, FIRST}), end_label);
                CodeBuffer::instance().bpatch(CodeBuffer::makelist({location, FIRST}), true_label);

                break;
            }
            case Types_enum::SET_TYPE :{
                printGetPtrForSet(ptr, index, var_scope_index);
                CodeBuffer::instance().emit("store i310 " + exp.var_name + ", i310* " + ptr);

                //CodeBuffer::instance().emit("store i256 " + exp.var_name + ", i256* " + ptr);
                scopes[var_scope_index].vars[index].setType(exp.type);

/*
                CodeBuffer::instance().emit("store [256 x i1]* " + exp.var_name + ", [256 x i1]** " + ptr);
*/
                break;

            }

            default:
                break;
        }
    }

    void printGetPtr(const std::string &ptr, int index, int var_scope_index) {
        int offset = scopes[var_scope_index].vars[index].getOffset();
        int num_of_args = scopes[1].getNumArgs();
        if (offset >= 0) {
            CodeBuffer::instance().emit(
                    ptr + " = getelementptr inbounds [50 x i32] , [50 x i32]* %locals, i32 0, i32 " +
                    to_string(offset));
        } else {
            offset = abs(offset);
            CodeBuffer::instance().emit(
                    ptr + " = getelementptr inbounds [" + to_string(num_of_args) + " x i32] , [" +
                    to_string(num_of_args) + " x i32]* %args, i32 0, i32 " + to_string(offset - 1));

        }
    }

    void printGetPtrForSet(const std::string &ptr, int index, int var_scope_index) {
        int offset = scopes[var_scope_index].vars[index].getOffset();
        int num_of_args = scopes[1].getNumArgs();
        if (offset >= 0) {
            CodeBuffer::instance().emit(ptr +
                                        " = getelementptr inbounds [50 x i310] , [50 x i310]* %locals_set, i310 0, i310 " +
                                        to_string(offset));
        } else {
            offset = abs(offset);
            CodeBuffer::instance().emit(ptr + " = getelementptr inbounds [" + to_string(num_of_args) +
                                        " x i310] , [" + to_string(num_of_args) +
                                        " x i310]* %args_set, i310 0, i310 " +
                                        to_string(offset - 1));
        }
        /* if(offset >= 0){
             CodeBuffer::instance().emit(ptr +
                                         " = getelementptr [50 x [256 x i1]*] , [50 x [256 x i1]*]* %locals_set, i32 0, i32 " +
                                         to_string(offset));
         }else{
             CodeBuffer::instance().emit(ptr + " = getelementptr [" + to_string(num_of_args) +
                                         " x [256 x i1]*] , [" + to_string(num_of_args) +
                                         " x [256 x i1]*]* %args_set, i32 0, i32 " +
                                         to_string(offset-1));
         }*/
    }

    void addScopeFromFunc(const std::string &id, std::vector<Var> &args, const Types &ret_type) {
        //assuming first scope
        int offset = -1;
        scopes.emplace_back(offset, false, true, ret_type);
        curr_scope++;

        // moving backwards, to check what to return in case of a duplication
        /*        for(auto iter = args.rbegin(); iter != args.rend(); iter++){
            addVar(iter.getId(), iter.getVarType(), true);
        }*/
        for (int i = args.size() - 1; i >= 0; --i) {
            std::string temp_id = args[i].getId();
            Types temp_type = args[i].getVarType();

            addVar(temp_id, temp_type, true);
        }

        scopes[curr_scope].setOffset();
    }

    void deleteScope(bool last = false) {
        if (last && !funcs_table->isMain()) {
            errorMainMissing();
            exit(1);
        }

//        output::endScope();

        for (auto &iter : scopes[curr_scope].vars) {
//            output::printID(iter.getId(), iter.getOffset(), enumToString(iter.getVarType()));
            var_maps.erase(iter.getId());
        }
        scopes.pop_back();
        curr_scope--;

        if (last) {
            funcs_table->removeFuncs();
//            delete FuncSymbolsTable::funcs_table;
//            delete vars_table;
        }
    }

    bool isDefined(const std::string &id) {
        return var_maps.find(id) != var_maps.end();
    }

    bool isValidName(const std::string &id) {
        if (isDefined(id)) {
            return false;
        }
        return !funcs_table->isDefined(id);
    }

    Types getVarSymbolTableType(const std::string &id) {
        if (!isDefined(id)) {
            errorUndef(yylineno, id);
            exit(1);
        }
        int scope = var_maps[id].first;
        int index = var_maps[id].second;

        return scopes[scope].vars[index].getVarType();
    }

    Var getVarSymbolTable(const std::string &id) {
        if (!isDefined(id)) {
            errorUndef(yylineno, id);
            exit(1);
        }
        int scope = var_maps[id].first;
        int index = var_maps[id].second;

        return scopes[scope].vars[index];
    }

    Expression getExp(const std::string &id) {
        Types id_type = getVarSymbolTableType(id);
        Expression new_var(id_type);
        int index = var_maps[id].second;
        int var_scope_index = var_maps[id].first;
        std::string ptr = Expression::gimmeANewCuteVar();

        switch (id_type.getType()) {
            case Types_enum::INT_TYPE:
            case Types_enum::BYTE_TYPE:
                printGetPtr(ptr, index, var_scope_index);
                CodeBuffer::instance().emit(new_var.var_name + " = load i32, i32* " + ptr);
                break;
            case Types_enum::BOOL_TYPE: {
                printGetPtr(ptr, index, var_scope_index);
                std::string val = Expression::gimmeANewCuteVar();
                std::string bool_val = Expression::gimmeANewCuteVar();
                CodeBuffer::instance().emit(val + " = load i32, i32* " + ptr);
                CodeBuffer::instance().emit(bool_val + " = trunc i32 " + val + " to i1");
                int loc = CodeBuffer::instance().emit("br i1 " + bool_val + ", label @, label @");
                new_var.true_list = CodeBuffer::makelist({loc, FIRST});
                new_var.false_list = CodeBuffer::makelist({loc, SECOND});
                break;
            }
            case Types_enum::SET_TYPE: {
                printGetPtrForSet(ptr, index, var_scope_index);
                CodeBuffer::instance().emit(new_var.var_name + " = load i310, i310* " + ptr);
                //CodeBuffer::instance().emit(new_var.var_name + " = load i256, i256* " + ptr);

/*
                CodeBuffer::instance().emit(new_var.var_name + " = load [256 x i1]*, [256 x i1]** " + ptr);
*/
                break;

            }
            default:
                break;
        }

        return new_var;
    }

    void checkWhile(const std::string &state) {
        if (!scopes[curr_scope].getWhile()) {
            if (state.compare("break") == 0) {
                errorUnexpectedBreak(yylineno);
            } else { // state == "continue"
                errorUnexpectedContinue(yylineno);
            }
            exit(1);
        }
    }

    void setWhile() {
        scopes[curr_scope].setWhile(true);
    }

    void checkRetType(Types type) {
        Types ret_type = scopes[curr_scope].getScopeType();
        if (type != ret_type) {
            if (!(type == Types_enum::BYTE_TYPE && ret_type == Types_enum::INT_TYPE)) {
                errorMismatch(yylineno);
                exit(1);
            }
        }
    }

};

#endif //HOMEWORK_3_VARSSYMBOLSTABLE_H
