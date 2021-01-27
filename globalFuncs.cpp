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

    CodeBuffer::instance().emitGlobal(R"(define i256 @SetAdd256(i256, i256) {)");
    CodeBuffer::instance().emitGlobal(R"(   call i256 @llvm.fshl.i256(i256 1, i256 0, i256 %1))");
    CodeBuffer::instance().emitGlobal(R"(   %temp_num = call i256 @llvm.fshl.i256(i256 1, i256 0, i256 %1))");
    CodeBuffer::instance().emitGlobal(R"(   %set_res = or i256 %0, %temp_num)");
    CodeBuffer::instance().emitGlobal(R"(   ret i256 %set_res)");
    CodeBuffer::instance().emitGlobal(R"(})");
    CodeBuffer::instance().emitGlobal(R"(define i256 @SetSub256(i256, i256) {)");
    CodeBuffer::instance().emitGlobal(R"(        %ones_val = sub i256 0, 2)");
    CodeBuffer::instance().emitGlobal(R"(        %temp_num = call i256 @llvm.fshl.i256(i256 %ones_val, i256 %ones_val, i256 %1))");
    CodeBuffer::instance().emitGlobal(R"(        %set_res = and i256 %0, %temp_num)");
    CodeBuffer::instance().emitGlobal(R"(        ret i256 %set_res)");
    CodeBuffer::instance().emitGlobal(R"(})");
    CodeBuffer::instance().emitGlobal(R"(define i1 @SetContains256(i256, i256) {)");
    CodeBuffer::instance().emitGlobal(R"(   %temp_num = call i256 @llvm.fshl.i256(i256 1, i256 0, i256 %1))");
    CodeBuffer::instance().emitGlobal(R"(   %res = and i256 %0, %temp_num)");
    CodeBuffer::instance().emitGlobal(R"(   %cond = icmp ne i256 0, %res)");
    CodeBuffer::instance().emitGlobal(R"(   br i1 %cond, label %Return_True, label %Return_False)");
    CodeBuffer::instance().emitGlobal(R"(   Return_True:)");
    CodeBuffer::instance().emitGlobal(R"(      ret i1 1)");
    CodeBuffer::instance().emitGlobal(R"(   Return_False:)");
    CodeBuffer::instance().emitGlobal(R"(      ret i1 0)");
    CodeBuffer::instance().emitGlobal(R"(})");
    CodeBuffer::instance().emitGlobal(R"(    define i32 @SetCast256(i256) {)");
    CodeBuffer::instance().emitGlobal(R"(        %res_256 = call i256 @llvm.ctpop.i256(i256 %0))");
    CodeBuffer::instance().emitGlobal(R"(        %res = trunc i256 %res_256 to i32)");
    CodeBuffer::instance().emitGlobal(R"(        ret i32 %res)");
    CodeBuffer::instance().emitGlobal(R"(})");

//    CodeBuffer::instance().emitGlobal("declare void @llvm.memset.p0i8.i64(i8* , i8, i64, i1)");
//    CodeBuffer::instance().emitGlobal("declare i8* @memset(i8*, i32, i32)");

    CodeBuffer::instance().emitGlobal("declare i310 @llvm.fshr.i310(i310, i310, i310)");
    CodeBuffer::instance().emitGlobal("declare i310 @llvm.fshl.i310(i310, i310, i310)");

    CodeBuffer::instance().emitGlobal("    define i32 @getMinBound(i310){");
    CodeBuffer::instance().emitGlobal("        %shifted = call i310 @llvm.fshr.i310(i310 0, i310 %0, i310 288)");
    CodeBuffer::instance().emitGlobal("        %trunced = trunc i310 %shifted to i32");
    CodeBuffer::instance().emitGlobal("        ret i32 %trunced");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("    define i32 @getMaxBound(i310){");
    CodeBuffer::instance().emitGlobal("        %shifted = call i310 @llvm.fshr.i310(i310 0, i310 %0, i310 256)");
    CodeBuffer::instance().emitGlobal("        %trunced = trunc i310 %shifted to i32");
    CodeBuffer::instance().emitGlobal("        ret i32 %trunced");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("    define i256 @getSet(i310){");
    CodeBuffer::instance().emitGlobal("        %set310 = trunc i310 %0 to i256");
    CodeBuffer::instance().emitGlobal("        ret i256 %set310");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("    define i310 @buildSet(i256, i32, i32){");
    CodeBuffer::instance().emitGlobal("        %set310 = zext i256 %0 to i310");
    CodeBuffer::instance().emitGlobal("        %zext_low = zext i32 %1 to i310");
    CodeBuffer::instance().emitGlobal("        %shifted_low = call i310 @llvm.fshl.i310(i310 %zext_low, i310 0, i310 288)");
    CodeBuffer::instance().emitGlobal("        %zext_high = zext i32 %2 to i310");
    CodeBuffer::instance().emitGlobal("        %shifted_high = call i310 @llvm.fshl.i310(i310 %zext_high, i310 0, i310 256)");
    CodeBuffer::instance().emitGlobal("        %temp_sum = add i310 %shifted_low, %shifted_high");
    CodeBuffer::instance().emitGlobal("        %full_set = add i310 %temp_sum, %set310");
    CodeBuffer::instance().emitGlobal("        ret i310 %full_set");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("define i310 @updateSet(i310, i256){");
    CodeBuffer::instance().emitGlobal("        %low = call i32 @getMinBound(i310 %0)");
    CodeBuffer::instance().emitGlobal("        %high = call i32 @getMaxBound(i310 %0)");
    CodeBuffer::instance().emitGlobal("        %new_full_set = call i310 @buildSet(i256 %1, i32 %low, i32 %high)");
    CodeBuffer::instance().emitGlobal("        ret i310 %new_full_set");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("    define i32 @SetCast(i310){");
    CodeBuffer::instance().emitGlobal("        %cut_set = call i256 @getSet(i310 %0)");
    CodeBuffer::instance().emitGlobal("        %size = call i32 @SetCast256(i256 %cut_set)");
    CodeBuffer::instance().emitGlobal("        ret i32 %size");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("define i1 @checkSetBounderies(i310, i32){");
    CodeBuffer::instance().emitGlobal("%low = call i32 @getMinBound(i310 %0)");
    CodeBuffer::instance().emitGlobal("%high = call i32 @getMaxBound(i310 %0)");
    CodeBuffer::instance().emitGlobal("%left_cond = icmp sge i32 %1, %low");
    CodeBuffer::instance().emitGlobal("%rigth_cond = icmp sle i32 %1, %high");
    CodeBuffer::instance().emitGlobal("br i1 %left_cond, label %First_True, label %False");
    CodeBuffer::instance().emitGlobal("        First_True:");
    CodeBuffer::instance().emitGlobal("br i1 %rigth_cond, label %Second_True, label %False");
    CodeBuffer::instance().emitGlobal("        Second_True:");
    CodeBuffer::instance().emitGlobal("ret i1 1");
    CodeBuffer::instance().emitGlobal("False:");
    CodeBuffer::instance().emitGlobal("ret i1 0");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("define i256 @CalcNum(i310, i32){");
    CodeBuffer::instance().emitGlobal("%low = call i32 @getMinBound(i310 %0)");
    CodeBuffer::instance().emitGlobal("%calculated_num = sub i32 %1, %low");
    CodeBuffer::instance().emitGlobal("%zext_num = zext i32 %calculated_num to i256");
    CodeBuffer::instance().emitGlobal("ret i256 %zext_num");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("define i310 @SetAdd (i310, i32){");
    CodeBuffer::instance().emitGlobal("%cond = call i1 @checkSetBounderies(i310 %0, i32 %1)");
    CodeBuffer::instance().emitGlobal("br i1 %cond , label %True, label %False");
    CodeBuffer::instance().emitGlobal("        True:");
    CodeBuffer::instance().emitGlobal("%cut_set = call i256 @getSet(i310 %0)");
    CodeBuffer::instance().emitGlobal("%zext_num = call i256 @CalcNum(i310 %0, i32 %1)");
    CodeBuffer::instance().emitGlobal("%new_set = call i256 @SetAdd256(i256 %cut_set, i256 %zext_num)");
    CodeBuffer::instance().emitGlobal("%new_full_set = call i310 @updateSet(i310 %0, i256 %new_set)");
    CodeBuffer::instance().emitGlobal("ret i310 %new_full_set");
    CodeBuffer::instance().emitGlobal("        False:");
    CodeBuffer::instance().emitGlobal("call void @print( i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str_plus, i32 0, i32 0))");
    CodeBuffer::instance().emitGlobal("call void @exit(i32 1)");
    CodeBuffer::instance().emitGlobal("ret i310 0");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("define i310 @SetSub(i310, i32){");
    CodeBuffer::instance().emitGlobal("%cond = call i1 @checkSetBounderies(i310 %0, i32 %1)");
    CodeBuffer::instance().emitGlobal("br i1 %cond , label %True, label %False");
    CodeBuffer::instance().emitGlobal("        True:");
    CodeBuffer::instance().emitGlobal("%cut_set = call i256 @getSet(i310 %0)");
    CodeBuffer::instance().emitGlobal("%zext_num = call i256 @CalcNum(i310 %0, i32 %1)");
    CodeBuffer::instance().emitGlobal("%new_set = call i256 @SetSub256(i256 %cut_set, i256 %zext_num)");
    CodeBuffer::instance().emitGlobal("%new_full_set = call i310 @updateSet(i310 %0, i256 %new_set)");
    CodeBuffer::instance().emitGlobal("ret i310 %new_full_set");
    CodeBuffer::instance().emitGlobal("        False:");
    CodeBuffer::instance().emitGlobal("call void @print( i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str_minus, i32 0, i32 0))");
    CodeBuffer::instance().emitGlobal("call void @exit(i32 1)");
    CodeBuffer::instance().emitGlobal("ret i310 0");
    CodeBuffer::instance().emitGlobal("}");

    CodeBuffer::instance().emitGlobal("define i1 @SetContains(i310, i32){");
    CodeBuffer::instance().emitGlobal("%cond = call i1 @checkSetBounderies(i310 %0, i32 %1)");
    CodeBuffer::instance().emitGlobal("br i1 %cond , label %True, label %False");
    CodeBuffer::instance().emitGlobal("        True:");
    CodeBuffer::instance().emitGlobal("%cut_set = call i256 @getSet(i310 %0)");
    CodeBuffer::instance().emitGlobal("%zext_num = call i256 @CalcNum(i310 %0, i32 %1)");
    CodeBuffer::instance().emitGlobal("%contains = call i1 @SetContains256(i256 %cut_set, i256 %zext_num)");
    CodeBuffer::instance().emitGlobal("ret i1 %contains");
    CodeBuffer::instance().emitGlobal("        False:");
    CodeBuffer::instance().emitGlobal("call void @print( i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str_in, i32 0, i32 0))");
    CodeBuffer::instance().emitGlobal("call void @exit(i32 1)");
    CodeBuffer::instance().emitGlobal("ret i1 0");
    CodeBuffer::instance().emitGlobal("}");
}






