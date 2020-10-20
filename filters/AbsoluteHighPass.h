#pragma once
#ifndef ABSOLUTEHIGHPASS_H
#define ABSOLUTEHIGHPASS_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"

template<class Type>
class AbsoluteHighPass : public Filter<Type> {
private:
    bool initialized=false;
    Type passDifference = 0;
public:
    AbsoluteHighPass(Type _passDifference): passDifference(_passDifference) {}
    virtual void update(Type newVal) {
        if(!initialized) {
            Filter<Type>::filtered = newVal;
            initialized = true;
            return;
        }
        if( ABSOLUTE_DIFFERENCE(Filter<Type>::filtered, newVal) < passDifference)
            return;
        Filter<Type>::filtered = newVal; 
    }
    Filter<Type>* clone() override {
        return new AbsoluteHighPass<Type>(newVal);
    }
};

#endif