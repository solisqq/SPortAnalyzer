#pragma once
#ifndef MOVAVERAGE_H
#define MOVAVERAGE_H

#include "../infac/Filter.h"
#include "../structures/List.h"
#include "../algorithms/algorithms.h"

template<class Type>
class MovAverage : public Filter<Type> {
private:
    List<Type> values;
    int count;
public:
    MovAverage(int strength) {
        count = strength;
        values = List<Type>();
    }
    virtual void update(Type newVal) {
        if(values.Count<count) {
            Filter<Type>::filtered = newVal;
            values.pushBack(newVal);
            return;
        }
        values.pushBack(newVal);
        values.popFront();
        Filter<Type>::filtered = Algorithms<Type>::calcAvg(values);
    }
};

#endif