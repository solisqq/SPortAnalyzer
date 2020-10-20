#pragma once
#ifndef COMPLEMENTARY_H
#define COMPLEMENTARY_H

#include "../infac/Filter.h"
#include "../infac/FilterableValue.h"
#include "../infac/Pair.h"

template<class Type>
class Complementary : public Filter<Type> {
private:
    float str = 1.0;
    float revStr = 0;
public:
    Complementary(float firstStrength): str(firstStrength), revStr(1.0-firstStrength) {}
    virtual void update(Type newVal) {
        Pair<float,float> pair = static_cast<Pair<float,float>>(newVal);
        Filter<Type>::filtered = (pair.first * str) + (pair.second*revStr);
    }
};

#endif