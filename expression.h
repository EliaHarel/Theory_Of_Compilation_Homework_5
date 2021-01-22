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

class Expression {
    static int new_var_counter;

    bool isNum() const {
        return type == Types_enum::INT_TYPE || type == Types_enum::BYTE_TYPE;
    }

public:
    Types type;
    std::string var_name;

    Expression() : type(Types_enum::UNDEFINED_TYPE), var_name(gimmeANewCuteVar()) {};

    explicit Expression(const Types &t) : type(t), var_name(gimmeANewCuteVar()) {};

    explicit Expression(Types_enum t) : type(t), var_name(gimmeANewCuteVar()) {};

    Expression(Types_enum t, const string& str) : type(t), var_name(str) {};

    Expression(const Types& t, const string& str) : type(t), var_name(str) {};


    ~Expression() = default;

    Expression(const Expression &rhs) : type(rhs.type), var_name(rhs.var_name) {};

    Expression &operator=(const Expression &rhs) {
        if (this == &rhs) { return *this; }
        type = rhs.type;
        var_name = gimmeANewCuteVar();
        return *this;
    }

    Expression opNot() {
        if (type != Types_enum::BOOL_TYPE) {
            output::errorMismatch(yylineno);
            exit(1);
        }
        Expression new_var(Types_enum::BOOL_TYPE);
        CodeBuffer::instance().emit(new_var.var_name + " = sub i1 1, " + var_name);
        return new_var;
    }

    Expression opOr(const Expression &t) {
        if (type != Types_enum::BOOL_TYPE || t.type != Types_enum::BOOL_TYPE) {
            output::errorMismatch(yylineno);
            exit(1);
        }

        int left_cond = CodeBuffer::instance().emit("br i1 " + var_name + ", label @, label @");
        string false1_label = CodeBuffer::instance().genLabel();
        int right_cond = CodeBuffer::instance().emit("br i1 " + t.var_name + ", label @, label @");

        string false2_label = CodeBuffer::instance().genLabel();
        string val1 = gimmeANewCuteVar();
        CodeBuffer::instance().emit(val1 + " = add i1 0, 0");
        int false_to_exit = CodeBuffer::instance().emit("br label @");

        string true_label = CodeBuffer::instance().genLabel();
        string val2 = gimmeANewCuteVar();
        CodeBuffer::instance().emit(val2 + " = add i1 1, 0");
        int true_to_exit = CodeBuffer::instance().emit("br label @");

        string exit = CodeBuffer::instance().genLabel();
        Expression new_var(Types_enum::BOOL_TYPE);
        string phi_comm =
                new_var.var_name + " = phi i1 [ " + val1 + ", " + false2_label + " ], [ " + val2 + ", " + true_label +
                " ]";
        CodeBuffer::instance().emit(phi_comm);

        CodeBuffer::instance().bpatch(CodeBuffer::makelist({left_cond, FIRST}), true_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({right_cond, FIRST}), true_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({left_cond, SECOND}), false1_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({right_cond, SECOND}), false2_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({false_to_exit, FIRST}), exit);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({true_to_exit, FIRST}), exit);

        return new_var;
    }

    Expression opAnd(const Expression &t) {
        if (type != Types_enum::BOOL_TYPE || t.type != Types_enum::BOOL_TYPE) {
            output::errorMismatch(yylineno);
            exit(1);
        }
        int left_cond = CodeBuffer::instance().emit("br i1 " + var_name + ", label @, label @");
        string true1_label = CodeBuffer::instance().genLabel();
        int right_cond = CodeBuffer::instance().emit("br i1 " + var_name + ", label @, label @");

        string false_label = CodeBuffer::instance().genLabel();
        string val1 = gimmeANewCuteVar();
        CodeBuffer::instance().emit(val1 + " = add i1 0, 0");
        int false_to_exit = CodeBuffer::instance().emit("br label @");

        string true2_label = CodeBuffer::instance().genLabel();
        string val2 = gimmeANewCuteVar();
        CodeBuffer::instance().emit(val2 + " = add i1 1, 0");
        int true_to_exit = CodeBuffer::instance().emit("br label @");

        string exit = CodeBuffer::instance().genLabel();
        Expression new_var(Types_enum::BOOL_TYPE);
        string phi_comm =
                new_var.var_name + " = phi i1 [ " + val1 + ", " + false_label + " ], [ " + val2 + ", " + true2_label +
                " ]";
        CodeBuffer::instance().emit(phi_comm);

        CodeBuffer::instance().bpatch(CodeBuffer::makelist({left_cond, FIRST}), true1_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({right_cond, FIRST}), true2_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({left_cond, SECOND}), false_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({right_cond, SECOND}), false_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({false_to_exit, FIRST}), exit);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({true_to_exit, FIRST}), exit);

        return new_var;
    }

    Expression relop(const Expression &t) {
        if (!isNum() || !t.isNum()) {
            output::errorMismatch(yylineno);
            exit(1);
        }
        type = Types_enum::BOOL_TYPE;
        return *this;
    }

    Expression binopMulDiv(const Expression &t, std::string &op) const {
        auto temp = byteIntCheck(*this, t);
        Expression new_var(temp);
        std::string op_llvm;
        if (op == "*") {
            op_llvm = "mul";
        } else {
            string cond = gimmeANewCuteVar();
            CodeBuffer::instance().emit(cond + " = icmp eq i32 " + t.var_name + ", 0");
            int loc = CodeBuffer::instance().emit("br i1 " + cond + ", label @, label @");
            string true_label = CodeBuffer::instance().genLabel();
            //todo: save thr string in advance and add reference to it
            //todo: calling to functions!
            CodeBuffer::instance().emit("call i8* @print( i8* Error division by zero)");
            CodeBuffer::instance().emit("call void @exit(i32 1)");
            int true_to_exit = CodeBuffer::instance().emit("br label @");

            string false_label = CodeBuffer::instance().genLabel();
            CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc, FIRST}), true_label);
            CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc, SECOND}), false_label);
            CodeBuffer::instance().bpatch(CodeBuffer::makelist({true_to_exit, FIRST}), false_label);

            if (new_var.type == Types_enum::INT_TYPE) { //op == "/"
                op_llvm = "sdiv";
            } else { // op == "/" && new_var.type == Types_enum::BYTE_TYPE
                op_llvm = "udiv";
            }
        }
        print3ACArithmetic(new_var.var_name, var_name, op_llvm, t.var_name);
        if (temp == Types_enum::BYTE_TYPE) {
            new_var.var_name = byteOverflow(new_var.var_name);
        }

        return new_var;
    }


    Expression binopAddSub(const Expression &t, std::string &op) {
        std::string op_llvm;
        if (op == "+") { op_llvm = "add"; }
        else op_llvm = "sub"; //op == "-"


        if (t.type.getType() == Types_enum::SET_TYPE) {
            if (!isNum()) {
                output::errorMismatch(yylineno);
                exit(1);
            }

            Expression new_var(t.type);
            CodeBuffer::instance().emit(new_var.var_name + " = alloca [256 x i1]");
            handleSet(t, new_var, "copy");
            changeSet(new_var, *this, op);
            return new_var;
        } else if (type.getType() == Types_enum::SET_TYPE) {
            if (!t.isNum()) {
                output::errorMismatch(yylineno);
                exit(1);
            }

            Expression new_var(type);
            CodeBuffer::instance().emit(new_var.var_name + " = alloca [256 x i1]");
            handleSet(*this, new_var, "copy");
            changeSet(new_var, t, op);
            return new_var;
        } else {
            Types_enum temp = byteIntCheck(*this, t);
            Expression new_var(temp);
            print3ACArithmetic(new_var.var_name, var_name, op_llvm, t.var_name);
            if (temp == Types_enum::BYTE_TYPE) {
                new_var.var_name = byteOverflow(new_var.var_name);
            }
            return new_var;
        }
    }

    static string handleSet(const Expression &src, const Expression &dst, const string &func) {

        string init = CodeBuffer::instance().genLabel();
        string sum;
        if(func == "sum"){
            sum = gimmeANewCuteVar();
            CodeBuffer::instance().emit(sum + " = alloca i32");
            CodeBuffer::instance().emit("store i32 0, i32* " + sum);
        }
        int to_phi1 = CodeBuffer::instance().emit("br label @");

        string loop = CodeBuffer::instance().genLabel();
        string cond = gimmeANewCuteVar();
        string counter = gimmeANewCuteVar();
        CodeBuffer::instance().emit(cond + " = icmp eq i32 " + counter + ", 256");
        int loc = CodeBuffer::instance().emit("br i1 " + cond + ", label @, label @");

        string true_label = CodeBuffer::instance().genLabel();
        int to_after = CodeBuffer::instance().emit("br label @");

        string false_label = CodeBuffer::instance().genLabel();
        string src_var = gimmeANewCuteVar();
        std::string src_comm = "getelementptr [256 * i1], [256 * i1]* " + src.var_name + " i1 0, i1 " + counter;
        CodeBuffer::instance().emit(src_var + " = " + src_comm);

        if (func == "copy") {
            sring val = gimmeANewCuteVar();
            CodeBuffer::instance().emit(val + " = load i1, i1* " + src_var);
            string dst_var = gimmeANewCuteVar();
            std::string dst_comm = "getelementptr [256 * i1], [256 * i1]* " + dst.var_name + " i1 0, i1 " + counter;
            CodeBuffer::instance().emit(dst_var + " = " + src_comm);
            CodeBuffer::instance().emit("store i1 " + val + ", i1* " + dst_var);
        } else if (func == "init") {
            CodeBuffer::instance().emit("store i1 0 , i1* " + src_var);
        } else { // func == "sum"
            string temp_sum = gimmeANewCuteVar();
            CodeBuffer::instance().emit(temp_sum + " = load i32, i32* " + sum);
            sring val_from_set = gimmeANewCuteVar();
            CodeBuffer::instance().emit(val_from_set + " = load i1, i1* " + src_var);
            sring val_from_set_i32 = gimmeANewCuteVar();
            CodeBuffer::instance().emit(val_from_set_i32 + " = zext i1 " + val_from_set + " to i32");
            string add = gimmeANewCuteVar();
            print3ACArithmetic(add,val_from_set_i32, "add", temp_sum);
            CodeBuffer::instance().emit("store i32 " + add + ", i32* " + sum);
        }

        string index = gimmeANewCuteVar();
        print3ACArithmetic(index, counter, "add", 1);
        int to_phi2 = CodeBuffer::instance().emit("br label @");

        string phi = CodeBuffer::instance().genLabel();
        string counter = gimmeANewCuteVar();
        string phi_comm = counter + " = phi i32 [ 0, " + init + " ], [ " + index + ", " + false_label + " ]";

        int to_loop = CodeBuffer::instance().emit("br label @");
        string after = CodeBuffer::instance().genLabel();

        CodeBuffer::instance().bpatch(CodeBuffer::makelist({to_phi1, FIRST}), phi);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc, FIRST}), true_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc, SECOND}), false_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({to_after, FIRST}), after);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({to_phi2, FIRST}), phi);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({to_loop, FIRST}), loop);

        string sum_val;
        if(func=="sum"){
            sum_val = gimmeANewCuteVar();
            CodeBuffer::instance().emit(sum_val + " = load i32, i32* " + sum);
        }
        return sum_val
    }


    Expression in(const Expression &t) {
        if (!isNum() || t.type.getType() != Types_enum::SET_TYPE) {
            output::errorMismatch(yylineno);
            exit(1);
        }
        checkSetVal(t, *this, "in");
        std::string loc_in_mem = getLocInSet(t, *this);
        string val_in_mem = gimmeANewCuteVar();
        CodeBuffer::instance().emit(val_in_mem + " = load i1, i1* " + loc_in_mem);

        string cond = gimmeANewCuteVar();
        CodeBuffer::instance().emit(cond + " = icmp eq i1 " + val_in_mem + ", 1");
        int loc = CodeBuffer::instance().emit("br i1 " + cond + ", label @, label @");

        string false_label = CodeBuffer::instance().genLabel();
        string val1 = gimmeANewCuteVar();
        CodeBuffer::instance().emit(val1 + " = add i1 1, 0");

        int end_if_br_false = CodeBuffer::instance().emit("br label @");

        string true_label = CodeBuffer::instance().genLabel();
        string val2 = gimmeANewCuteVar();
        CodeBuffer::instance().emit(val2 + " = add i1 0, 0");

        int end_if_br_true = CodeBuffer::instance().emit("br label @");

        string end_if_label = CodeBuffer::instance().genLabel();
        Expression new_var(Types_enum::BOOL_TYPE);
        string phi_comm =
                new_var.var_name + " = phi i1 [ " + val1 + ", " + false_label + " ], [ " + val2 + ", " + true_label +
                " ]";
        CodeBuffer::instance().emit(phi_comm);


        CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc, SECOND}), false_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({loc, FIRST}), true_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({end_if_br_false, FIRST}), end_if_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({end_if_br_true, FIRST}), end_if_label);

        return new_var;
    }

    static void changeSet(const Expression &set, const Expression &num, const std::string &op) {
        checkSetVal(set, num, op);
        std::string loc_in_mem = getLocInSet(set, num);
        int val = (op == "add") ? 1 : 0;
        CodeBuffer::instance().emit("store i1 " + to_string(val) + ", i1* " + loc_in_mem);
    }

    static void checkSetVal(const Expression &set, const Expression &num, const std::string &op) {
        string cond1_name = gimmeANewCuteVar();
        //sge: interprets the operands as signed values and yields true if op1 is greater than or equal to op2.
        string cond1_code =
                cond1_name + " = icmp sge i32 " + num.var_name + ", " + to_string(set.type.getSetRange().first);
        CodeBuffer::instance().emit(cond1_code);
        int cond1_loc = CodeBuffer::instance().emit("br i1 " + cond1_name + ", label @, label @ ");

        string false_label = CodeBuffer::instance().genLabel();
        //todo: save thr string in advance and add reference to it
        //todo: calling to functions!
        if (op == "add") {
            CodeBuffer::instance().emit("call i8* @print( i8* Error out of set range. Op: +)");
        } else if (op == "sub") {
            CodeBuffer::instance().emit("call i8* @print( i8* Error out of set range. Op: -)");
        } else { // op == "in"
            CodeBuffer::instance().emit("call i8* @print( i8* Error out of set range. Op: in)");

        }
        CodeBuffer::instance().emit("call void @exit(i32 1)");


        string true1_label = CodeBuffer::instance().genLabel();
        string cond2_name = gimmeANewCuteVar();
        //sle: interprets the operands as signed values and yields true if op1 is less than or equal to op2..
        string cond2_code =
                cond2_name + " = icmp sle i32 " + num.var_name + ", " + to_string(set.type.getSetRange().second);
        CodeBuffer::instance().emit(cond2_code);
        int cond2_loc = CodeBuffer::instance().emit("br i1 " + cond2_name + ", label @, label @");
        string true2_label = CodeBuffer::instance().genLabel();

        CodeBuffer::instance().bpatch(CodeBuffer::makelist({cond1_loc, FIRST}), true1_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({cond2_loc, FIRST}), true2_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({cond1_loc, SECOND}), false_label);
        CodeBuffer::instance().bpatch(CodeBuffer::makelist({cond2_loc, SECOND}), false_label);

    }

    static string getLocInSet(const Expression &set, const Expression &num) {
        std::string loc_in_arr = gimmeANewCuteVar();
        std::string loc_in_mem = gimmeANewCuteVar();

        print3ACArithmetic(loc_in_arr, num.var_name, "sub", to_string(set.type.getSetRange().first));
        std::string get_element = "getelementptr [256 * i1], [256 * i1]* " + set.var_name + " i1 0, i1 " + loc_in_arr;
        CodeBuffer::instance().emit(loc_in_mem + " = " + get_element);
        return loc_in_mem;
    }

    static std::string byteOverflow(const std::string &val) {
        auto temp_var_1 = gimmeANewCuteVar();
        auto temp_var_2 = gimmeANewCuteVar();
        CodeBuffer::instance().emit(temp_var_1 + " = trunc i32 " + val + " to i8");
        CodeBuffer::instance().emit(temp_var_2 + " = zext i8 " + temp_var_1 + " to i32");
        return temp_var_2;
    }


    inline static void
    print3ACArithmetic(const std::string &lval, const std::string &left_val, std::string op,
                       const std::string &right_val) {
        CodeBuffer::instance().emit(lval + " = " + op + " i32 " + left_val + ", " + right_val);
    }

    static Types_enum byteIntCheck(const Expression &t1, const Expression &t2) {
        if (!t1.isNum() || !t2.isNum()) {
            output::errorMismatch(yylineno);
            exit(1);
        }
        if (t1.type == Types_enum::BYTE_TYPE && t2.type == Types_enum::BYTE_TYPE) {
            return Types_enum::BYTE_TYPE;
        } else {
            return Types_enum::INT_TYPE;
        }
    }

    Expression cast(const Types t) {
        if (t != Types_enum::INT_TYPE || type.getType() != Types_enum::SET_TYPE) {
            output::errorMismatch(yylineno);
            exit(1);
        }

        string reg = handleSet(*this, Expression(), "sum");
        Expression new_var(Types_enum::INT_TYPE, reg);

        return new_var;
    }

    static Expression call(const Types &type) { return Expression(type); }

    void typeCheck(const Types t) {
        if (t != type && !(type == Types_enum::BYTE_TYPE && t == Types_enum::INT_TYPE)) {
            output::errorMismatch(yylineno);
            exit(1);
        }
    }

    static Expression printNum(int num, Types_enum type) {
        if (type == Types_enum::BYTE_TYPE && num > 255) {
            output::errorByteTooLarge(yylineno, std::to_string(num));
            exit(1);
        }
        Expression new_var(type);
        CodeBuffer::instance().emit(new_var.var_name + " = add i32 " + to_string(num) + " , 0");
        return new_var;
    }

    static std::string gimmeANewCuteVar() {
        return "%newCuteVar_" + std::to_string(new_var_counter++);
    }

};

#endif //HOMEWORK_3_EXPRESSION_H
