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
    CodeBuffer::instance().emitGlobal("declare i32 @printf(i8*, ...)");
    CodeBuffer::instance().emitGlobal("declare void @exit(i32)");
    CodeBuffer::instance().emitGlobal(R"(@.int_specifier = internal constant [4 x i8] c"%d\0A\00")");
    CodeBuffer::instance().emitGlobal(R"(@.str_specifier = internal constant [4 x i8] c"%s\0A\00")");

    CodeBuffer::instance().emitGlobal("define void @printi(i32) {");
    CodeBuffer::instance().emitGlobal("call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0), i32 %0)");
    CodeBuffer::instance().emitGlobal("ret void");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("define void @print(i8*) {");
    CodeBuffer::instance().emitGlobal("call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0), i8* %0)");
    CodeBuffer::instance().emitGlobal("ret void");
    CodeBuffer::instance().emitGlobal("}");


    CodeBuffer::instance().emitGlobal(R"(@.str_zero = internal constant [24 x i8] c"Error division by zero\0A\00")");
    CodeBuffer::instance().emitGlobal(R"(@.str_plus = internal constant [31 x i8] c"Error out of set range. Op: +\0A\00")");
    CodeBuffer::instance().emitGlobal(R"(@.str_minus = internal constant [31 x i8] c"Error out of set range. Op: -\0A\00")");
    CodeBuffer::instance().emitGlobal(R"(@.str_in = internal constant [32 x i8] c"Error out of set range. Op: in\0A\00")");
    CodeBuffer::instance().emitGlobal("declare void @llvm.memset.p0i8.i64(i8* , i8, i64, i1)");
    CodeBuffer::instance().emitGlobal("declare i8* @memset(i8*, i32, i32)");

}







