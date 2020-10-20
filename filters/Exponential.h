#pragma once
#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H

#include "../infac/Filter.h"
#include "../structures/List.h"
#include "../algorithms/algorithms.h"
#include "../utilities/Output/Output.h"
#include <math.h>

template<class Type>
class Exponential : public Filter<Type> {
private:
    Type maxVal, minVal;
    Type powRangeMap;
    Type powMidVal, powMidValPowered;
    float power=1;
public:
    Exponential(Type _maxVal, Type _minVal, Type _minMap, Type _maxMap, float _power): maxVal(_maxVal), minVal(_minVal), power(_power) {
        powRangeMap = (_maxMap-_minMap)/2;
        calibrate();
    }
    virtual void update(Type newVal) {
        if(newVal> maxVal) {
            if(newVal < maxVal + maxVal*0.5) {
                maxVal = newVal;
                calibrate();
            }
        }
        else if(newVal< minVal) {
            if(newVal>minVal/2) {
                minVal = newVal;
                calibrate();
            }
        }
        Type backup = newVal-powMidVal-minVal;
        bool wasNegative = backup<0? true : false;
        Filter<Type>::filtered = (powf(abs(backup), power)*powRangeMap)/powMidValPowered;
        if(wasNegative) Filter<Type>::filtered = -Filter<Type>::filtered;
    }
private:
    void calibrate() {
        powMidVal = (maxVal-minVal)/2;
        powMidValPowered = powf(powMidVal,power);
    }
};

#endif