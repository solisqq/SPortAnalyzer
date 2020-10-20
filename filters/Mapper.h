#pragma once
#ifndef MAPPER_H
#define MAPPER_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"

template<class Type>
class Mapper : public Filter<Type> {
private:
    Type maxVal, minVal;
    Type minMap, maxMap;
    Type rangeVal, rangeMap, offset=0;
public:
    Mapper(Type _maxVal, Type _minVal, Type _minMap, Type _maxMap): maxVal(_maxVal), minVal(_minVal), minMap(_minMap), maxMap(_maxMap) {
        rangeMap = _maxMap - _minMap;
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
        Filter<Type>::filtered = (((newVal-minVal)*rangeMap)/rangeVal)+minMap;
    }
    Filter<Type>* clone() override {
        return new Mapper<Type>(maxVal, minVal, minMap, maxMap);
    }
private:
    void calibrate() {
        rangeVal = maxVal-minVal;
    }
};

#endif