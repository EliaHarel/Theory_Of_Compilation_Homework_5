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

    Statement_c() = default;

    ~Statement_c() = default;

    Statement_c(const Statement_c& rhs) : next_list(rhs.next_list){};

    Statement_c& operator=(const Statement_c& rhs){
        next_list = rhs.next_list;
        return *this;
    }

    static Statement_c NMarker(){
        int buffer_location = CodeBuffer::instance().emit("br label @");
        Statement_c new_statement;
        new_statement.next_list = CodeBuffer::makelist({buffer_location, FIRST});
        return new_statement;
    }

    static void checkExp(const Expression& exp){
        if(exp.type != Types_enum::BOOL_TYPE){
            output::errorMismatch(yylineno);
            exit(1);
        }
    }


    static Statement_c ifBlock(const Expression& exp, const std::string& marker, const Statement_c& rhs){
        CodeBuffer::instance().bpatch(exp.true_list, marker);
        Statement_c new_statement;
        new_statement.next_list = CodeBuffer::merge(exp.false_list, rhs.next_list);
        return new_statement;
    }
};

#endif //HOMEWORK_3_STATEMENT_H
