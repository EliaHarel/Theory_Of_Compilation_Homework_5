//
// Created by EliaHarel on 23/12/2020.
//

#ifndef HOMEWORK_3_SCOPE_H
#define HOMEWORK_3_SCOPE_H

#include "var.h"
#include <vector>

class Scope {
    int offset;
    int index;
    bool isInWhile;
    bool isInFunc;
    Types type;
    int num_of_args = 0;

public:
    std::vector<Var> vars;

    Scope(int offset, bool isWhile, bool inFunc, const Types& type = Types(Types_enum::UNDEFINED_TYPE)) :
            offset(offset), index(0), isInWhile(isWhile), isInFunc(inFunc), type(type){}

    ~Scope() = default;

    int addVar(const std::string& id, const Types& var_type, int scope){
        vars.emplace_back(id, var_type, scope, offset);
        offset++;
        int curr_index = index;
        index++;
        return curr_index;
    }

    int addFuncVar(const std::string& id, const Types& var_type, int scope){
        vars.emplace_back(id, var_type, scope, offset);
        offset--;
        num_of_args++;
        int curr_index = index;
        index++;
        return curr_index;
    }

    int getOffset() const{
        return offset;
    }

    void setOffset(){
        offset = 0;
    }

    void setWhile(bool isWhile){
        isInWhile = isWhile;
    }

    bool getWhile() const{
        return isInWhile;
    }

    void setFunc(bool inFunc){
        isInFunc = inFunc;
    }

    bool getInFunc(){
        return isInFunc;
    }

    Types getScopeType(){
        return type;
    }

    int getNumArgs(){ return num_of_args; };
};

#endif //HOMEWORK_3_SCOPE_H
