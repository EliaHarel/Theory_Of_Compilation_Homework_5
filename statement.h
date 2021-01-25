//
// Created by EliaHarel on 23/12/2020.
//

#ifndef HOMEWORK_3_STATEMENT_H
#define HOMEWORK_3_STATEMENT_H

#include <vector>
#include "bp.hpp"

class Statement_c {
public:
    std::vector<pair<int, BranchLabelIndex>> next_list = std::vector<pair<int, BranchLabelIndex>>();
    std::vector<pair<int, BranchLabelIndex>> break_list = std::vector<pair<int, BranchLabelIndex>>();
    std::vector<pair<int, BranchLabelIndex>> continue_list = std::vector<pair<int, BranchLabelIndex>>();
    Statement_c() = default;

    ~Statement_c() = default;

    Statement_c(const Statement_c &rhs) : next_list(rhs.next_list), break_list(rhs.break_list), continue_list(rhs.continue_list) {};

    Statement_c &operator=(const Statement_c &rhs) {
        next_list = rhs.next_list;
        continue_list = rhs.continue_list;
        break_list = rhs.break_list;
        return *this;
    }

    static Statement_c NMarker() {
        int buffer_location = CodeBuffer::instance().emit("br label @");
        Statement_c new_statement;
        new_statement.next_list = CodeBuffer::makelist({buffer_location, FIRST});
        return new_statement;
    }

    static void checkExp(const Expression &exp) {
        if (exp.type != Types_enum::BOOL_TYPE) {
            output::errorMismatch(yylineno);
            exit(1);
        }
    }

    static Statement_c ifBlock(const Expression &exp, const std::string &marker, const Statement_c &rhs) {
        CodeBuffer::instance().bpatch(exp.true_list, marker);
        Statement_c new_statement;
        new_statement.next_list = CodeBuffer::merge(exp.false_list, rhs.next_list);

        new_statement.break_list = rhs.break_list;
        new_statement.continue_list = rhs.continue_list;
        return new_statement;
    }

    static Statement_c ifElseBlock(const Expression &exp, const std::string &marker1, const Statement_c &stm1,
                                   const Statement_c &n, const std::string &marker2, const Statement_c &stm2) {
        CodeBuffer::instance().bpatch(exp.true_list, marker1);
        CodeBuffer::instance().bpatch(exp.false_list, marker2);
        Statement_c new_statement;
        auto temp_list = CodeBuffer::merge(stm1.next_list, n.next_list);
        new_statement.next_list = CodeBuffer::merge(temp_list, stm2.next_list);

        new_statement.break_list = CodeBuffer::merge(stm1.break_list, stm2.break_list);
        new_statement.continue_list = CodeBuffer::merge(stm1.continue_list, stm2.continue_list);

        return new_statement;
    }

    static Statement_c whileBlock (const std::string& marker1, const Expression& exp, const std::string& marker2,
                                   const Statement_c& stm){
        CodeBuffer::instance().bpatch(stm.next_list, marker1);
        CodeBuffer::instance().bpatch(exp.true_list, marker2);
        CodeBuffer::instance().bpatch(stm.continue_list, marker1);

        Statement_c new_statement;

        new_statement.next_list = CodeBuffer::merge(exp.false_list, stm.break_list);
        CodeBuffer::instance().emit("br label %" + marker1);
        return new_statement;
    }

    static Statement_c combineStatements (const Statement_c& stm1, const std::string& marker, const Statement_c& stm2){
        CodeBuffer::instance().bpatch(stm1.next_list, marker);
        Statement_c new_statement;
        new_statement.next_list = stm2.next_list;
        return new_statement;
    }

    static Statement_c breakComm(){
        int loc = CodeBuffer::instance().emit("br label @");
        Statement_c new_statement;
        new_statement.break_list.emplace_back(pair<int, BranchLabelIndex>(loc, FIRST));
        return new_statement;
    }

    static Statement_c continueComm(){
        int loc = CodeBuffer::instance().emit("br label @");
        Statement_c new_statement;
        new_statement.continue_list.emplace_back(pair<int, BranchLabelIndex>(loc, FIRST));
        return new_statement;
    }

};

#endif //HOMEWORK_3_STATEMENT_H
