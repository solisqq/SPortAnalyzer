#pragma once
#ifndef YAW_FILTER_H
#define YAW_FILTER_H

#include "../infac/Filter.h"

template<class Type>
class YawFilter : public Filter<Type> {
private:
    float dump;
public:
    YawFilter(float _dump): dump(_dump) {}
    virtual void update(Type newVal) {
        Filter<Type>::filtered += newVal/dump;
    }
};

#endif