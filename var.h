//
// Created by EliaHarel on 23/12/2020.
//

#ifndef HOMEWORK_3_VAR_H
#define HOMEWORK_3_VAR_H

#include <string>
#include "enums.h"

class Var {
    static int new_var_counter;
    std::string ID;
    std::string var_name;
    Types type;
    int scope = -1;
    int offset = -1;

public:
    Var() : type(Types()), ID(), scope(-1), offset(-1), var_name(gimmeANewCuteVar()){};

    Var(const Types& type) : type(type), var_name(gimmeANewCuteVar()){};

    Var(const std::string& id, const Types& type) : ID(id), type(type), var_name(gimmeANewCuteVar()){};

    Var(const std::string& id, const Types& type, int offset) : ID(id), type(type), offset(offset), var_name(gimmeANewCuteVar()){}

    Var(const std::string& id, const Types& type, int scope, int offset) : ID(id), type(type), scope(scope),
                                                                           offset(offset), var_name(gimmeANewCuteVar()){}

    ~Var() = default;

    Var(const Var& rhs) = default;

    Var& operator=(const Var& rhs){
        if(this == &rhs){ return *this; }
        ID = rhs.ID;
        type = rhs.type;
        scope = rhs.scope;
        offset = rhs.offset;
        return *this;
    }


    std::string getId() const{
        return ID;
    }

    Types getVarType(){
        return type;
    }

    int getOffset() const{
        return offset;
    }

    void setVarName(){
        var_name = gimmeANewCuteVar();
    }

    std::string getVarName(){
        return var_name;
    }

    static std::string gimmeANewCuteVar(){
        return "%newCuteVar2_" + std::to_string(new_var_counter++);
    }

};

#endif //HOMEWORK_3_VAR_H
