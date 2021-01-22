#ifndef __ATTRIBUTES_H
#define __ATTRIBUTES_H

#include <string>
#include <set>
#include <iostream>
#include "var.h"
#include "hw3_output.hpp"
#include "expression.h"


extern int yylineno;
using namespace output;

class utype {
public:
    int num;
    std::string* str;
    Expression exp;
    Types type;
    Var var;
    std::vector<Var> varsVec;
    std::vector<Types> typesVec;

    utype() : num(-1), str(nullptr), exp(Expression()), type(Types()), var(Var()),
              varsVec(std::vector<Var>()),
              typesVec(std::vector<Types>()){};

    utype(int num) : num(num), str(nullptr), exp(Expression()), type(Types()),
                     var(Var()), varsVec(std::vector<Var>()),
                     typesVec(std::vector<Types>()){};

    utype(std::string rhs_str) : num(-1), str(new std::string(rhs_str)), exp(Expression()),
                                 type(Types()), var(Var()), varsVec(std::vector<Var>()),
                                 typesVec(std::vector<Types>()){};

    utype(Expression& rhs) : num(-1), str(nullptr), exp(rhs), type(Types()), var(Var()),
                            varsVec(std::vector<Var>()), typesVec(std::vector<Types>()){};

    utype(Types type) : num(-1), str(nullptr), exp(Expression()), type(type), var(Var()),
                        varsVec(std::vector<Var>()), typesVec(std::vector<Types>()){};

    utype(Types_enum type) : num(-1), str(nullptr), exp(Expression()), type(type), var(Var()),
                             varsVec(std::vector<Var>()), typesVec(std::vector<Types>()){};

    utype(const std::vector<Var>& varsVec) : num(-1), str(nullptr), exp(Expression()), type(Types()),
                                             var(Var()), varsVec(varsVec), typesVec(std::vector<Types>()){};

    utype(const std::vector<Types>& typesVec) : num(-1), str(nullptr), exp(Expression()), type(Types()),
                                                var(Var()), varsVec(std::vector<Var>()), typesVec(typesVec){};

    ~utype(){
        delete str;
    }

    utype(const utype& rhs) : num(-1), str(new std::string(*(rhs.str))), exp(rhs.exp), type(rhs.type),
                              var(rhs.var), varsVec(rhs.varsVec), typesVec(rhs.typesVec){};

    utype& operator=(const utype& rhs){
        if(this == &rhs){ return *this; }
        num = rhs.num;
        str = new std::string(*(rhs.str));
        exp = rhs.exp;
        type = rhs.type;
        var = rhs.var;
        return *this;
    }

    utype& operator=(int rhs_num){
        num = rhs_num;
        return *this;
    }

    utype& operator=(std::string& rhs_str){
        auto temp = str;
        str = new std::string(rhs_str);
        delete temp;
        return *this;
    }

    utype& operator=(Expression& rhs_exp){
        exp = rhs_exp;
        return *this;
    }

    utype& operator=(Types& rhs_type){
        type = rhs_type;
        return *this;
    }

    utype& operator=(Types_enum rhs_type){
        type = rhs_type;
        return *this;
    }

    static void useless(){
        auto x = "the end";
        std::cout << x << std::endl;
    }
};

#define YYSTYPE utype* // Tell Bison to use STYPE as the stack type


#endif //__ATTRIBUTES_H