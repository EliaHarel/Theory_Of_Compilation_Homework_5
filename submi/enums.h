//
// Created by EliaHarel on 23/12/2020.
//

#ifndef HOMEWORK_3_ENUMS_H
#define HOMEWORK_3_ENUMS_H

#include <string>
#include <cassert>

enum class Types_enum {
    INT_TYPE = 1,
    BYTE_TYPE = 2,
    BOOL_TYPE = 3,
    STRING_TYPE = 4,
    SET_TYPE = 5,
    VOID_TYPE = 6,
    UNDEFINED_TYPE = 7
};

class Types {
    Types_enum ty = Types_enum::UNDEFINED_TYPE;
    int start_index = -1;
    int end_index = -1;
public:
    Types(int start, int end) : ty(Types_enum::SET_TYPE), start_index(start), end_index(end){};

    Types() : ty(Types_enum::UNDEFINED_TYPE), start_index(-1), end_index(-1){};

    ~Types() = default;

    Types(Types_enum src) : ty(src){};

    Types(const Types& src){
        start_index = src.start_index;
        end_index = src.end_index;
        ty = src.ty;
    };

    Types& operator=(Types_enum var){
        start_index = -1;
        end_index = -1;
        ty = var;
        return *this;
    };

    Types& operator=(Types var){
        start_index = var.start_index;
        end_index = var.end_index;
        ty = var.ty;
        return *this;
    };

    bool operator==(Types_enum var) const{
        assert (var != Types_enum::SET_TYPE);
        return ty == var;
    }

    bool operator==(Types& var) const{
//        return ty == var.ty && start_index == var.start_index && end_index == var.end_index;
        return ty == var.ty;
    }

    bool operator!=(Types_enum var) const{ return !(*this == var); }

    bool operator!=(Types& var) const{ return !(*this == var); }

    Types_enum getType() const{
        return ty;
    }

    std::pair<int, int> getSetRange() const{
        return {start_index, end_index};
    }


};


#endif //HOMEWORK_3_ENUMS_H
