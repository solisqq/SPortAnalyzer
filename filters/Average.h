#pragma once
#ifndef AVERAGE_H
#define AVERAGE_H

#include "../infac/Filter.h"
#include "../structures/List.h"
#include "../algorithms/algorithms.h"

template<class Type>
class Average : public Filter<Type> {
private:
    List<Type> values;
    int count;
public:
    Average(int strength) {
        count = strength;
        values = List<Type>();
    }
    virtual void update(Type newVal) {
        if(values.Count<count) {
            Filter<Type>::filtered = newVal;
            values.pushBack(newVal);
            return;
        }
        values.FIFO(newVal);
    }
    Type getAvg() {
        if(values.Count==count) 
            Filter<Type>::filtered = Algorithms<Type>::calcAvg(values);
        return Filter<Type>::filtered;
    }
};

#endif