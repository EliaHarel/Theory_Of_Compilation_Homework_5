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
    CodeBuffer::instance().emitGlobal("@.str_specifier = internal constant [2 x i8] c\"%s\"");

    CodeBuffer::instance().emitGlobal("define void @printi(i32) {");
    CodeBuffer::instance().emitGlobal("call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0), i32 %0)");
    CodeBuffer::instance().emitGlobal("ret void");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("define void @print(i8*) {");
    CodeBuffer::instance().emitGlobal("call i32 (i8*, ...) @printf(i8* getelementptr ([2 x i8], [2 x i8]* @.str_specifier, i32 0, i32 0), i8* %0)");
    CodeBuffer::instance().emitGlobal("ret void");
    CodeBuffer::instance().emitGlobal("}");


    CodeBuffer::instance().emitGlobal(R"(@.str_zero = internal constant [24 x i8] c"Error division by zero\0A\00")");
    CodeBuffer::instance().emitGlobal(R"(@.str_plus = internal constant [31 x i8] c"Error out of set range. Op: +\0A\00")");
    CodeBuffer::instance().emitGlobal(R"(@.str_minus = internal constant [31 x i8] c"Error out of set range. Op: -\0A\00")");
    CodeBuffer::instance().emitGlobal(R"(@.str_in = internal constant [32 x i8] c"Error out of set range. Op: in\0A\00")");

    /*Our Set Op Functions*/

    CodeBuffer::instance().emitGlobal(R"(declare i256 @llvm.fshl.i256(i256, i256, i256))");
    CodeBuffer::instance().emitGlobal(R"(declare i256 @llvm.ctpop.i256(i256))");
    CodeBuffer::instance().emitGlobal(R"(define i256 @SetAdd(i256, i256) {)");
    CodeBuffer::instance().emitGlobal(R"(   %temp_num = call i256 @llvm.fshl.i256(i256 1, i256 1, i256 %1))");
    CodeBuffer::instance().emitGlobal(R"(   %set_res = or i256 %0, %temp_num)");
    CodeBuffer::instance().emitGlobal(R"(   ret i256 %set_res)");
    CodeBuffer::instance().emitGlobal(R"(})");
    CodeBuffer::instance().emitGlobal(R"(define i256 @SetSub(i256, i256) {)");
    CodeBuffer::instance().emitGlobal(R"(        %ones_val = sub i256 0, 2)");
    CodeBuffer::instance().emitGlobal(R"(        %temp_num = call i256 @llvm.fshl.i256(i256 %ones_val, i256 %ones_val, i256 %1))");
    CodeBuffer::instance().emitGlobal(R"(        %set_res = and i256 %0, %temp_num)");
    CodeBuffer::instance().emitGlobal(R"(        ret i256 %set_res)");
    CodeBuffer::instance().emitGlobal(R"(})");
    CodeBuffer::instance().emitGlobal(R"(define i1 @SetContains(i256, i256) {)");
    CodeBuffer::instance().emitGlobal(R"(   %temp_num = call i256 @llvm.fshl.i256(i256 1, i256 1, i256 %1))");
    CodeBuffer::instance().emitGlobal(R"(   %res = and i256 %0, %temp_num)");
    CodeBuffer::instance().emitGlobal(R"(   %cond = icmp ne i256 0, %res)");
    CodeBuffer::instance().emitGlobal(R"(   br i1 %cond, label %Return_True, label %Return_False)");
    CodeBuffer::instance().emitGlobal(R"(   Return_True:)");
    CodeBuffer::instance().emitGlobal(R"(      ret i1 true)");
    CodeBuffer::instance().emitGlobal(R"(   Return_False:)");
    CodeBuffer::instance().emitGlobal(R"(      ret i1 false)");
    CodeBuffer::instance().emitGlobal(R"(})");
    CodeBuffer::instance().emitGlobal(R"(    define i32 @SetCast(i256) {)");
    CodeBuffer::instance().emitGlobal(R"(        %res_256 = call i256 @llvm.ctpop.i256(i256 %0))");
    CodeBuffer::instance().emitGlobal(R"(        %res = trunc i256 %res_256 to i32)");
    CodeBuffer::instance().emitGlobal(R"(        ret i32 %res)");
    CodeBuffer::instance().emitGlobal(R"(})");


//    CodeBuffer::instance().emitGlobal("declare void @llvm.memset.p0i8.i64(i8* , i8, i64, i1)");
//    CodeBuffer::instance().emitGlobal("declare i8* @memset(i8*, i32, i32)");

}







