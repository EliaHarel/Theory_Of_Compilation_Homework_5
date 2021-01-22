//
// Created by EliaHarel on 23/12/2020.
//

#ifndef HOMEWORK_3_STATEMENT_H
#define HOMEWORK_3_STATEMENT_H
#include "attributes.hpp"

class Statement {
public:
    static void checkExp(const Expression& exp){
        if(exp.type != Types_enum::BOOL_TYPE){
            errorMismatch(yylineno);
            exit(1);
        }
    }
};

#endif //HOMEWORK_3_STATEMENT_H
