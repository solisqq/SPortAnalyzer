#pragma once
#ifndef LIMITS_FILTER_H
#define LIMITS_FILTER_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"

template<class Type>
class LimitsFilter : public Filter<Type> {
private:
    Type low=0;
    Type high=0;
public:
    LimitsFilter(Type minVal, Type maxVal): low(minVal), high(maxVal) {}
    virtual void update(Type newVal) {
        if(newVal>high) Filter<Type>::filtered = high;
        else if(newVal<low) Filter<Type>::filtered = low;
        else Filter<Type>::filtered = newVal;
    }
    Filter<Type>* clone() override {
        return new LimitsFilter<Type>(this->low,this->high);
    }
};

#endif