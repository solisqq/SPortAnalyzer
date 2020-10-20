#pragma once
#ifndef EXPHIGHPASS_H
#define EXPHIGHPASS_H

#include "../infac/Filter.h"
#include "../algorithms/algorithms.h"

template<class Type>
class ExpHighPass : public Filter<Type> {
private:
    float low=0.0;
    float high=0.0;
    bool initialized=false;
    Type passDifference = 0;
    Type damp=1;
public:
    ExpHighPass(Type threshold, Type _damp): passDifference(threshold), damp(_damp) {}
    virtual void update(Type newVal) {
        if(!initialized) {
            Filter<Type>::filtered = newVal;
            initialized = true;
            return;
        }
        Type absDiff = ABSOLUTE_DIFFERENCE(Filter<Type>::filtered, newVal);
        if(absDiff < passDifference) 
            Filter<Type>::filtered += absDiff/damp;
        
        Filter<Type>::filtered = newVal; 
    }
};

#endif