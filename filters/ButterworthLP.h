#pragma once
#ifndef BUTTERWORTH_LP_H
#define BUTTERWORTH_LP_H
#define Butterworth_ORDER 1

#include "stock/Iir.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"

template<class Type>
class ButterworthLP: public Filter<Type> {
	Iir::Butterworth::LowPass<Butterworth_ORDER> bworth;
    float frequency=0, cutOff=0;
public:
	ButterworthLP(float freq, float cutoff):frequency(freq), cutOff(cutoff) {
		bworth.setup(Butterworth_ORDER, freq, cutoff);
    }

    virtual void update(Type newVal) {
        Filter<Type>::filtered = bworth.filter(static_cast<double>(newVal));
    }
    Filter<Type>* clone() override {
        return new ButterworthLP<Type>(frequency,cutOff);
    }
};

#endif