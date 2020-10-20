#pragma once
#ifndef BIQUAD_C_H
#define BIQUAD_C_H

#include "stock/BiquadCustom.h"
#include "Filter/Filter.h"
#include "floatviewsetter.h"
#include <QVBoxLayout>

template<class Type>
class BiquadBS : public Filter<Type> {
    BiquadCustom* biquad = nullptr;
    float centerFreq = 0, widthFreq = 0, rippleDb = 0, freq = 0;
    QWidget *toRet=nullptr;
public:
    BiquadBS(float _freq, float _centerFreq, float _widthFreq, float _rippleDb) :
        freq(_freq),
        centerFreq(_centerFreq),
        widthFreq(_widthFreq),
        rippleDb(_rippleDb)
    {
        toRet = new QWidget();
        toRet->setLayout(new QVBoxLayout());
        toRet->layout()->addWidget(new FloatViewSetter(&centerFreq, "centerFreq", toRet));
        toRet->layout()->addWidget(new FloatViewSetter(&widthFreq, "widthFreq", toRet));
        toRet->layout()->addWidget(new FloatViewSetter(&rippleDb, "rippleDb", toRet));
        toRet->layout()->addWidget(new FloatViewSetter(&freq, "freq", toRet));
    }
    void init() override {
        biquad = new BiquadCustom(bq_type_notch, centerFreq / freq, widthFreq/centerFreq, rippleDb);

    }

    virtual void update(Type newVal) {
        Filter<Type>::filtered = biquad->process(static_cast<double>(newVal));
    }

    Filter<Type>* clone() override {
        return new BiquadBS<Type>(freq, centerFreq, widthFreq, rippleDb);
    }
    QWidget *getWidget() override {
        return toRet;
    }
};

#endif
