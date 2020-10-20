#pragma once
#ifndef CLOSESTO_H
#define CLOSESTO_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"

template<class Type>
class ClosesTo : public Filter<Type> {
private:
    float low=0.0;
    float high=0.0;
    List<Type> values;
    int count;
    Type maxVal;
public:
    ClosesTo(int strength, Type max) {
        maxVal = max;
        count = strength;
        values = List<Type>();
    }
    virtual void update(Type newVal) {
        if(values.count()<count) {
            Filter<Type>::filtered = newVal;
            values.pushBack(newVal);
            return;
        }
        values.popFront();
        values.pushBack(newVal);

        typename List<Type>::Node *current = values.front;
        typename List<Type>::Node *min = values.front;
        Type currMin = maxVal;
        while(current!=nullptr) {
            Type temporary = abs(current->val-Filter<Type>::filtered);
            if( temporary < currMin) {
                min = current;
                currMin = temporary;
            }
            current = current->next;
        }
        Filter<Type>::filtered = min->val;
    }
    Filter<Type>* clone() override {
        return new ClosesTo<Type>(count,maxVal);
    }
};

#endif