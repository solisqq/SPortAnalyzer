#pragma once
#ifndef DEAD_ZONE_FILTER_H
#define DEAD_ZONE_FILTER_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"

template<class Type>
class DeadZoneFilter : public Filter<Type>
{
private:
    Type crossPoint, maxV, minV;
public:
    DeadZoneFilter(Type _crossPoint, Type _maxV, Type _minV): crossPoint(_crossPoint), maxV(_maxV), minV(_minV) {Filter<Type>::filtered=0;}
    virtual void update(Type newVal) {
        if(newVal>maxV) 
            Filter<Type>::filtered = newVal-maxV;
        else if(newVal<minV) 
            Filter<Type>::filtered = newVal+minV;
        else
            Filter<Type>::filtered = crossPoint;
    }
    Filter<Type>* clone() override {
        return new DeadZoneFilter<Type>(crossPoint, maxV, minV);
    }
};

#endif