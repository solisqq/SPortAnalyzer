#pragma once
#ifndef INFINITE_ADD_H
#define INFINITE_ADD_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"

template<class Type>
class InfiniteAdd : public Filter<Type>
{
private:
    double mult=0;
public:
    InfiniteAdd(double _mult): mult(_mult) {Filter<Type>::filtered=0;}
    virtual void update(Type newVal) {Filter<Type>::filtered += newVal*mult;}
    Filter<Type>* clone() override {
        return new InfiniteAdd<Type>(mult);
    }
};

#endif