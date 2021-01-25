//
// Created by EliaHarel on 24/12/2020.
//

#include "globalFuncs.h"
#include "hw3_output.hpp"
#include "bp.hpp"

std::string enumToString(Types type){
    switch (type.getType()){
        case Types_enum::INT_TYPE:
            return "INT";
        case Types_enum::BYTE_TYPE:
            return "BYTE";
        case Types_enum::BOOL_TYPE:
            return "BOOL";
        case Types_enum::STRING_TYPE:
            return "STRING";
        case Types_enum::SET_TYPE:
            return "SET";
        case Types_enum::VOID_TYPE:
            return "VOID";
        default:
            return "ERROR";
    }
}

Types setCheck(int lineno, int num1, int num2){
    int diff = num2 - num1;
    if(diff > 255 || diff <= 0){
        output::errorSetTooLarge(lineno, to_string(num1), to_string(num2));
        exit(1);
    }
    return Types(num1, num2);
}
//TODO:: print to global
/*
void casti256toarr(){
     CodeBuffer::instance().emitGlobal("define [256 x i1] @castToArr(i256 %0) {");

    CodeBuffer::instance().emitGlobal("}");
}

void castArrToi256(){

}
*/

void printGlobalFuncs(){

}






