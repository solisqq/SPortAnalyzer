#pragma once
#ifndef DynamicNotch_H
#define DynamicNotch_H

#include "stock/BiquadCustom.h"
#include "Filter/Filter.h"
#include "floatviewsetter.h"
#include <QVBoxLayout>
#include <fft-real/FFTReal.h>
#include <QDebug>

template<class Type>
class DynamicNotch: public Filter<Type> {
    BiquadCustom* biquad = nullptr;
    float samplesSquared2 = 1, widthFreq = 0, rippleDb = 0, freq = 0, defaultCenter=0;
    QWidget *toRet=nullptr;
    ffft::FFTReal<float>* fft=nullptr;
    float* items;
    int counter=0;
public:
    DynamicNotch(float _samplesSquared2, float _freq, float _widthFreq, float _rippleDb, float _defaultCenter) :
        freq(_freq),
        samplesSquared2(pow(2,_samplesSquared2)),
        widthFreq(_widthFreq),
        rippleDb(_rippleDb),
        defaultCenter(_defaultCenter)
    {
        toRet = new QWidget();
        toRet->setLayout(new QVBoxLayout());
        toRet->layout()->addWidget(new FloatViewSetter(&samplesSquared2, "samplesSquared2", toRet));
        toRet->layout()->addWidget(new FloatViewSetter(&defaultCenter, "defaultCenter", toRet));
        toRet->layout()->addWidget(new FloatViewSetter(&widthFreq, "widthFreq", toRet));
        toRet->layout()->addWidget(new FloatViewSetter(&rippleDb, "rippleDb", toRet));
        toRet->layout()->addWidget(new FloatViewSetter(&freq, "freq", toRet));
        items = new float[1024];
    }
    void init() override {
        reinit();
    }

    virtual void update(Type newVal) {

        Filter<Type>::filtered = biquad->process(static_cast<double>(newVal));
        items[counter] = newVal;
        if(counter==1023) {
            float Y[1024];
            fft->do_fft(Y, items);
            float maxIndex = 512;
            float maxValue = -1;
            for(int i=512; i<1024; i++) {
                float current = qAbs(Y[i]/1024);
                if(maxValue<current) {
                    maxValue = current;
                    maxIndex = i-512;
                }
            }
            defaultCenter = (freq*maxIndex)/1024;
            qDebug()<<defaultCenter;
            reinit();
            counter=0;
        } else counter++;
    }

    Filter<Type>* clone() override {
        return new DynamicNotch<Type>(1024, freq, widthFreq, rippleDb, defaultCenter);
    }
    void reinit() {
        if(fft!=nullptr) delete fft;
        fft = new ffft::FFTReal<float>(1024);
        biquad = new BiquadCustom(bq_type_notch, defaultCenter/freq, widthFreq/defaultCenter, rippleDb);
    }
    void calcFreq() {

    }
    QWidget *getWidget() override {
        return toRet;
    }
};

#endif
