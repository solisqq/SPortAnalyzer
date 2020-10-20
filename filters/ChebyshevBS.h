#pragma once
#ifndef CHEBYSHEV_BS_H
#define CHEBYSHEV_BS_H
#define CHEBYSHEV_BS_ORDER 3

#include "stock/Iir.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"

template<class Type>
class ChebyshevBS: public Filter<Type> {
    Iir::ChebyshevI::BandStopBase cheby;
    float centerFreq=0, widthFreq=0, rippleDb=0, freq=0;
public:
    ChebyshevBS(float _freq, float _centerFreq, float _widthFreq, float _rippleDb):
        freq(_freq),
        centerFreq(_centerFreq),
        widthFreq(_widthFreq),
        rippleDb(_rippleDb)
    {
        cheby.setup(CHEBYSHEV_BS_ORDER, freq, centerFreq, widthFreq, rippleDb);
    }

    virtual void update(Type newVal) {
        Filter<Type>::filtered = cheby.filter(static_cast<double>(newVal));
    }
    Filter<Type>* clone() override {
        return new ChebyshevBS<Type>(freq, centerFreq, widthFreq, rippleDb);
    }
};

#endif