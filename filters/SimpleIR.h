#pragma once
#ifndef SIMPLEIR_H
#define SIMPLEIR_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"

template<class Type>
class SimpleIR : public Filter<Type> {
private:
    float low=0.0;
    float high=0.0;
    bool initialized=false;
    float strength;
public:
    SimpleIR(float _strength):strength(_strength) {
        CalcStr(strength);
    }
    virtual void update(Type newVal) {
        if(!initialized) {
            Filter<Type>::filtered = newVal;
            initialized = true;
            return;
        }
        Filter<Type>::filtered = (newVal * low) + (Filter<Type>::filtered * high); 
    }
    void CalcStr(float strength) {
        low = 1.0 - strength;
        high = strength;
    }
    Filter<Type>* clone() override {
        return new SimpleIR<Type>(strength);
    }
};

#endif