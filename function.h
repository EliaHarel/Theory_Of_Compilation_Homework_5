//
// Created by EliaHarel on 23/12/2020.
//

#ifndef HOMEWORK_3_FUNCTION_H
#define HOMEWORK_3_FUNCTION_H

#include <string>
#include "attributes.hpp"

class Function {
    std::string ID;
    int num_of_args;
    Types ret_type;

public:
    std::vector<Var> args;

    Function(const std::string& id, int num_of_args, const std::vector<Var>& args, Types ret_type) :
            ID(id), num_of_args(num_of_args), args(args), ret_type(ret_type){}

    int getNumOfArgs(){
        return num_of_args;
    }
    std::string getID(){
        return ID;
    }

    Types getRetType(){
        return ret_type;
    }

    string getllvmName(){
        return "@_" + ID;
    }
};

#endif //HOMEWORK_3_FUNCTION_H
