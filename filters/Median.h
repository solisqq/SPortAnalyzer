#pragma once
#ifndef MEDIAN_H
#define MEDIAN_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettingsInterface.h"

template<class Type>
class Median : public Filter<Type> {
private:
    float low=0.0;
    float high=0.0;
    List<Type> values;
    int count;
public:
    Median(int strength, int initiateVal = 0) {
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
        if(values.count()<4) {
            Filter<Type>::filtered = medianSmall();
            return;
        }
        Type *tab = new Type[count];
        typename List<Type>::Node *current = values.top();
        for(int i=0; i<count; i++) {
            if(current==nullptr) tab[i]=0;
            else {
                tab[i] = current->val;
                current = current->next;
            }
        }
        
        UTILS::quickSort(tab,0,count-1);
        int middle = count/2;
        if(count%2==0){ 
            Filter<Type>::filtered = (tab[middle-1]+tab[middle])/2.0;
        }
        else {
            Filter<Type>::filtered = tab[middle];
        }
        delete tab;
    }
    Type medianSmall() {
        if(count==0) return 0;
        if(count==1) return values.front->val;
        if(count==2) return values.front->val; 
        if(count==3) {
            Type vals[3]; 
            vals[0] = values.front->val;
            vals[1] = values.front->next->val;
            vals[2] = values.front->next->next->val;
            if(vals[0]<vals[1] && vals[0] > vals[2]) return vals[0];
            if(vals[1]<vals[2] && vals[1] > vals[0]) return vals[1];
            else return vals[2];
        }
    }
    Filter<Type>* clone() override {
        return new Median<Type>(count,0);
    }
};

#endif