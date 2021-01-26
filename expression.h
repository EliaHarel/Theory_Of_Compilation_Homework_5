//
// Created by EliaHarel on 23/12/2020.
//

#ifndef HOMEWORK_3_EXPRESSION_H
#define HOMEWORK_3_EXPRESSION_H

#include <string>
#include <iostream>
#include "enums.h"
#include "hw3_output.hpp"
#include "bp.hpp"


extern int yylineno;

typedef std::string Label;

class Expression {
    static int new_var_counter;

    bool isNum() const{ return type == Types_enum::INT_TYPE || type == Types_enum::BYTE_TYPE; }

public:
    vector<pair<int, BranchLabelIndex>> true_list = vector<pair<int, BranchLabelIndex>>();
    vector<pair<int, BranchLabelIndex>> false_list = vector<pair<int, BranchLabelIndex>>();
    Types type;
    std::string var_name;
    int str_length = 0;

    Expression() : type(Types_enum::UNDEFINED_TYPE), var_name(gimmeANewCuteVar()){};

    Expression(const Expression& rhs) : type(rhs.type), var_name(rhs.var_name), str_length(rhs.str_length),
                                        true_list(rhs.true_list), false_list(rhs.false_list){};

    explicit Expression(const Types& t) : type(t), var_name(gimmeANewCuteVar()){};

    explicit Expression(Types_enum t) : type(t), var_name(gimmeANewCuteVar()){};

    Expression(Types_enum t, const std::string& str) : type(t), var_name(str){};

    Expression(const Types& t, const std::string& str) : type(t), var_name(str){};

    ~Expression() = default;


    Expression& operator=(const Expression& rhs){
        if(this == &rhs){ return *this; }
        type = rhs.type;
        true_list = rhs.true_list;
        false_list = rhs.false_list;
        var_name = gimmeANewCuteVar();
        str_length = rhs.str_length;
        return *this;
    }

    Expression opNot(){
        if(type != Types_enum::BOOL_TYPE){
            output::errorMismatch(yylineno);
            exit(1);
        }
        Expression new_var(*this);
        new_var.false_list = this->true_list;
        new_var.true_list = this->false_list;
        return new_var;
    }

    Expression opOr(const Expression& t, const std::string& next_instr){
        if(type != Types_enum::BOOL_TYPE || t.type != Types_enum::BOOL_TYPE){
            output::errorMismatch(yylineno);
            exit(1);
        }
        CodeBuffer::instance().bpatch(this->false_list, next_instr);
        Expression new_var(Types_enum::BOOL_TYPE);
        new_var.true_list = CodeBuffer::merge(this->true_list, t.true_list);
        new_var.false_list = t.false_list;
        return new_var;
    }

    Expression opAnd(const Expression& t, const std::string& next_instr) const{
        if(type != Types_enum::BOOL_TYPE || t.type != Types_enum::BOOL_TYPE){
            output::errorMismatch(yylineno);
            exit(1);
        }

        CodeBuffer::instance().bpatch(this->true_list, next_instr);
        Expression new_var(Types_enum::BOOL_TYPE);
        new_var.true_list = t.true_list;
        new_var.false_list = CodeBuffer::merge(this->false_list, t.false_list);
        return new_var;
    }

    Expression relop(const Expression& t, const std::string& op){
        if(!isNum() || !t.isNum()){
            output::errorMismatch(yylineno);
            exit(1);
        }
        auto cond = gimmeANewCuteVar();
        CodeBuffer::instance().emit(
                cond + " = icmp " + auxRelop(op) + " i32 " + var_name + ", " + t.var_name);
        int buffer_location = CodeBuffer::instance().emit("br i1 " + cond + ", label @, label @");
        Expression new_var(Types_enum::BOOL_TYPE);
        new_var.true_list = CodeBuffer::makelist({buffer_location, FIRST});
        new_var.false_list = CodeBuffer::makelist({buffer_location, SECOND});
        return new_var;
    }

    static std::string auxRelop(const std::string& op){
        std::string str;
        if(op == "=="){
            str = "eq";
        }else if(op == "!="){
            str = "ne";
        }else if(op == "<="){
            str = "ule";
        }else if(op == ">="){
            str = "uge";
        }else if(op == "<"){
            str = "ult";
        }else{// op == ">"
            str = "ugt";
        }
        return str;
    }

    Expression binopMulDiv(const Expression t, std::string& op) const{
        auto temp = byteIntCheck(*this, t);
        Expression new_var(temp);
        std::string op_llvm;
        if(op == "*"){
            op_llvm = "mul";
        }else{
            std::string cond = gimmeANewCuteVar();
            CodeBuffer::instance().emit(cond + " = icmp eq i32 " + t.var_name + ", 0");
            int loc = CodeBuffer::instance().emit("br i1 " + cond + ", label @, label @");
            std::string true_label = CodeBuffer::instance().genLabel();
            CodeBuffer::instance().emit(
                    "call void @print( i8* getelementptr ([23 x i8], [23 x i8]* @.str_zero, i32 0, i32 0))");
            CodeBuffer::instance().emit("call void @exit(i32 1)");
            int true_to_exit = CodeBuffer::instance().emit("br label @");

            std::string false_label = CodeBuffer::instance().genLabel();
            CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc, FIRST}), true_label);
            CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc, SECOND}), false_label);
            CodeBuffer::instance().bpatch(CodeBuffer::makelist({true_to_exit, FIRST}), false_label);

            if(new_var.type == Types_enum::INT_TYPE){ //op == "/"
                op_llvm = "sdiv";
            }else{ // op == "/" && new_var.type == Types_enum::BYTE_TYPE
                op_llvm = "udiv";
            }
        }
        print3ACArithmetic(new_var.var_name, var_name, op_llvm, t.var_name);
        if(temp == Types_enum::BYTE_TYPE){
            new_var.var_name = byteOverflow(new_var.var_name);
        }

        return new_var;
    }

    Expression binopAddSub(const Expression t, std::string& op){
        std::string op_llvm;
        if(op == "+"){ op_llvm = "add"; }
        else op_llvm = "sub"; //op == "-"


        if(t.type.getType() == Types_enum::SET_TYPE){
            if(!isNum()){
                output::errorMismatch(yylineno);
                exit(1);
            }

            Expression new_var(t.type);
            CodeBuffer::instance().emit(new_var.var_name + " = alloca [256 x i1]");

            handleSet(t, new_var, "copy");
            changeSet(new_var, *this, op);
            return new_var;
        }else if(type.getType() == Types_enum::SET_TYPE){
            if(!t.isNum()){
                output::errorMismatch(yylineno);
                exit(1);
            }

            Expression new_var(type);
            CodeBuffer::instance().emit(new_var.var_name + " = alloca [256 x i1]");
            handleSet(*this, new_var, "copy");
            changeSet(new_var, t, op);
            return new_var;
        }else{
            Types_enum temp = byteIntCheck(*this, t);
            Expression new_var(temp);
            print3ACArithmetic(new_var.var_name, var_name, op_llvm, t.var_name);
            if(temp == Types_enum::BYTE_TYPE){
                new_var.var_name = byteOverflow(new_var.var_name);
            }
            return new_var;
        }
    }

    static Expression boolExp(bool b){

        int buffer_location = CodeBuffer::instance().emit("br label @");
        Expression new_var(Types_enum::BOOL_TYPE);
        if(b){
            new_var.true_list = CodeBuffer::makelist({buffer_location, FIRST});
        }else{
            new_var.false_list = CodeBuffer::makelist({buffer_location, FIRST});
        }
        return new_var;
    }

    static std::string handleSet(const Expression& src, const Expression& dst, const std::string& func){
        int label_location = CodeBuffer::instance().emit("br label @");
        std::string init_label = CodeBuffer::instance().genLabel();
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({label_location, FIRST}), init_label);
        std::string sum;
        if(func == "sum")   {
            sum = gimmeANewCuteVar();
            CodeBuffer::instance().emit(sum + " = alloca i32");
            CodeBuffer::instance().emit("store i32 0, i32* " + sum);
        }
        int to_phi1 = CodeBuffer::instance().emit("br label @");

        std::string loop = CodeBuffer::instance().genLabel();
        std::string cond = gimmeANewCuteVar();
        std::string counter = gimmeANewCuteVar();
        CodeBuffer::instance().emit(cond + " = icmp eq i32 " + counter + ", 256");
        int loc = CodeBuffer::instance().emit("br i1 " + cond + ", label @, label @");

        std::string true_label = CodeBuffer::instance().genLabel();
        int to_after = CodeBuffer::instance().emit("br label @");

        std::string false_label = CodeBuffer::instance().genLabel();
        std::string src_var = gimmeANewCuteVar();
        std::string src_comm =
                "getelementptr [256 x i1], [256 x i1]* " + src.var_name + ", i1 0, i32 " + counter;
        CodeBuffer::instance().emit(src_var + " = " + src_comm);

        //TODO: if this doesn't work - memcpy, memset
        if(func == "copy"){
            std::string val = gimmeANewCuteVar();
            CodeBuffer::instance().emit(val + " = load i1, i1* " + src_var);
            std::string dst_var = gimmeANewCuteVar();
            std::string dst_comm =
                    "getelementptr [256 x i1], [256 x i1]* " + dst.var_name + ", i1 0, i32 " + counter;
            CodeBuffer::instance().emit(dst_var + " = " + src_comm);
            CodeBuffer::instance().emit("store i1 " + val + ", i1* " + dst_var);
        }else if(func == "init"){
            CodeBuffer::instance().emit("store i1 0 , i1* " + src_var);
        }else{ // func == "sum"
            std::string temp_sum = gimmeANewCuteVar();
            CodeBuffer::instance().emit(temp_sum + " = load i32, i32* " + sum);
            std::string val_from_set = gimmeANewCuteVar();
            CodeBuffer::instance().emit(val_from_set + " = load i1, i1* " + src_var);
            std::string val_from_set_i32 = gimmeANewCuteVar();
            CodeBuffer::instance().emit(val_from_set_i32 + " = zext i1 " + val_from_set + " to i32");
            CodeBuffer::instance().emit("call void @printi(i32 "+val_from_set_i32+")");
            std::string add = gimmeANewCuteVar();
            print3ACArithmetic(add, val_from_set_i32, "add", temp_sum);
            CodeBuffer::instance().emit("store i32 " + add + ", i32* " + sum);
        }

        std::string index = gimmeANewCuteVar();
        print3ACArithmetic(index, counter, "add", "1");
        int to_phi2 = CodeBuffer::instance().emit("br label @");

        std::string phi = CodeBuffer::instance().genLabel();
        std::string phi_comm =
                counter + " = phi i32 [ 0, %" + init_label + " ], [ " + index + ", %" + false_label + " ]";


        CodeBuffer::instance().emit(phi_comm);
        int to_loop = CodeBuffer::instance().emit("br label @");
        std::string after = CodeBuffer::instance().genLabel();

        CodeBuffer::instance().bpatch(CodeBuffer::makelist({to_phi1, FIRST}), phi);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc, FIRST}), true_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc, SECOND}), false_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({to_after, FIRST}), after);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({to_phi2, FIRST}), phi);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({to_loop, FIRST}), loop);

        std::string sum_val;
        if(func == "sum"){
            sum_val = gimmeANewCuteVar();
            CodeBuffer::instance().emit(sum_val + " = load i32, i32* " + sum);
        }
        return sum_val;
    }

    Expression in(const Expression& t){
        if(!isNum() || t.type.getType() != Types_enum::SET_TYPE){
            output::errorMismatch(yylineno);
            exit(1);
        }
        checkSetVal(t, *this, "in");
        std::string loc_in_mem = getLocInSet(t, *this);
        std::string val_in_mem = gimmeANewCuteVar();
        CodeBuffer::instance().emit(val_in_mem + " = load i1, i1* " + loc_in_mem);

        std::string cond = gimmeANewCuteVar();
        CodeBuffer::instance().emit(cond + " = icmp eq i1 " + val_in_mem + ", 1");
        int loc = CodeBuffer::instance().emit("br i1 " + cond + ", label @, label @");

        Expression new_var(Types_enum::BOOL_TYPE);
        new_var.true_list = CodeBuffer::makelist({loc, FIRST});
        new_var.false_list = CodeBuffer::makelist({loc, SECOND});

        return new_var;
    }

    static void changeSet(const Expression& set, const Expression& num, const std::string& op){
        checkSetVal(set, num, op);
        std::string loc_in_mem = getLocInSet(set, num);
        int val = (op == "add") ? 1 : 0;
        CodeBuffer::instance().emit("store i1 " + to_string(val) + ", i1* " + loc_in_mem);
    }

    static void checkSetVal(const Expression& set, const Expression& num, const std::string& op){
        std::string cond1_name = gimmeANewCuteVar();
        //sge: interprets the operands as signed values and yields true if op1 is greater than or equal to op2.
        std::string cond1_code =
                cond1_name + " = icmp sge i32 " + num.var_name + ", " +
                to_string(set.type.getSetRange().first);
        CodeBuffer::instance().emit(cond1_code);
        int cond1_loc = CodeBuffer::instance().emit("br i1 " + cond1_name + ", label @, label @ ");

        std::string false_label = CodeBuffer::instance().genLabel();
        //todo: save thr  std::string in advance and add reference to it
        //todo: calling to functions!
        if(op == "add"){
            CodeBuffer::instance().emit(
                    "call void @print( i8* getelementptr ([31 x i8], [31 x i8]* @.str_plus, i32 0, i32 0))");
        }else if(op == "sub"){
            CodeBuffer::instance().emit(
                    "call void @print( i8* getelementptr ([31 x i8], [31 x i8]* @.str_minus, i32 0, i32 0))");
        }else{ // op == "in"
            CodeBuffer::instance().emit(
                    "call void @print( i8* getelementptr ([32 x i8], [32 x i8]* @.str_in, i32 0, i32 0))");

        }
        CodeBuffer::instance().emit("call void @exit(i32 1)");

        int irrelevant = CodeBuffer::instance().emit("br label @");

        std::string true1_label = CodeBuffer::instance().genLabel();
        std::string cond2_name = gimmeANewCuteVar();
        //sle: interprets the operands as signed values and yields true if op1 is less than or equal to op2..
        std::string cond2_code =
                cond2_name + " = icmp sle i32 " + num.var_name + ", " +
                to_string(set.type.getSetRange().second);
        CodeBuffer::instance().emit(cond2_code);
        int cond2_loc = CodeBuffer::instance().emit("br i1 " + cond2_name + ", label @, label @");
        std::string true2_label = CodeBuffer::instance().genLabel();

        CodeBuffer::instance().bpatch(CodeBuffer::makelist({cond1_loc, FIRST}), true1_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({cond2_loc, FIRST}), true2_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({cond1_loc, SECOND}), false_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({cond2_loc, SECOND}), false_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({irrelevant, FIRST}), true1_label);

    }

    static std::string getLocInSet(const Expression& set, const Expression& num){
        std::string loc_in_arr = gimmeANewCuteVar();
        std::string loc_in_mem = gimmeANewCuteVar();

        print3ACArithmetic(loc_in_arr, num.var_name, "sub", to_string(set.type.getSetRange().first));
        std::string get_element =
                "getelementptr [256 x i1], [256 x i1]* " + set.var_name + ", i1 0, i32 " + loc_in_arr;
        CodeBuffer::instance().emit(loc_in_mem + " = " + get_element);
        return loc_in_mem;
    }

    static std::string byteOverflow(const std::string& val){
        auto temp_var_1 = gimmeANewCuteVar();
        auto temp_var_2 = gimmeANewCuteVar();
        CodeBuffer::instance().emit(temp_var_1 + " = trunc i32 " + val + " to i8");
        CodeBuffer::instance().emit(temp_var_2 + " = zext i8 " + temp_var_1 + " to i32");
        return temp_var_2;
    }


    inline static void
    print3ACArithmetic(const std::string& lval, const std::string& left_val, std::string op,
                       const std::string& right_val){
        CodeBuffer::instance().emit(lval + " = " + op + " i32 " + left_val + ", " + right_val);
    }

    static Types_enum byteIntCheck(const Expression& t1, const Expression& t2){
        if(!t1.isNum() || !t2.isNum()){
            output::errorMismatch(yylineno);
            exit(1);
        }
        if(t1.type == Types_enum::BYTE_TYPE && t2.type == Types_enum::BYTE_TYPE){
            return Types_enum::BYTE_TYPE;
        }else{
            return Types_enum::INT_TYPE;
        }
    }

    Expression cast(const Types t){
        if(t != Types_enum::INT_TYPE || type.getType() != Types_enum::SET_TYPE){
            output::errorMismatch(yylineno);
            exit(1);
        }

        std::string reg = handleSet(*this, Expression(), "sum");
        Expression new_var(Types_enum::INT_TYPE, reg);

        return new_var;
    }

//    static Expression call(const Types& type){ return Expression(type); }

    void typeCheck(const Types& t){
        if(t.getType() != type.getType() && !(type == Types_enum::BYTE_TYPE && t == Types_enum::INT_TYPE)){
            output::errorMismatch(yylineno);
            exit(1);
        }
    }

    static Expression printNum(int num, Types_enum type){
        if(type == Types_enum::BYTE_TYPE && num > 255){
            output::errorByteTooLarge(yylineno, std::to_string(num));
            exit(1);
        }
        Expression new_var(type);
        CodeBuffer::instance().emit(new_var.var_name + " = add i32 " + to_string(num) + " , 0");
        return new_var;
    }

    Expression call(){
        Expression new_var(type);
        switch (type.getType()){
            case Types_enum::INT_TYPE:
            case Types_enum::BYTE_TYPE:
                CodeBuffer::instance().emit(new_var.var_name + " = add i32 0, " + var_name);
                break;
            case Types_enum::BOOL_TYPE:{
                int loc = CodeBuffer::instance().emit("br i1 " + var_name + ", label @, label @");
                new_var.true_list = CodeBuffer::makelist({loc, FIRST});
                new_var.false_list = CodeBuffer::makelist({loc, SECOND});
                break;
            }
            case Types_enum::SET_TYPE:
                CodeBuffer::instance().emit(new_var.var_name + " alloca [256 x i1]");
                CodeBuffer::instance().emit("store i256 " + var_name + " [256 x i1]*" + new_var.var_name);
                break;
            default:
                break;
        }
        return new_var;
    }

    static std::string gimmeANewCuteVar(){
        return "%newCuteVar_" + std::to_string(new_var_counter++);
    }

    static Expression handlingString(std::string str){
        Expression new_var(Types_enum::STRING_TYPE);
        new_var.var_name[0] = '@';
        new_var.str_length = str.size() + 2;

        CodeBuffer::instance().emitGlobal(
                new_var.var_name + " = internal constant [" + to_string(str.length() + 2) + " x i8] c\"" +
                str + "\\0A\\00\"");
        return new_var;
    }

};

#endif //HOMEWORK_3_EXPRESSION_H
