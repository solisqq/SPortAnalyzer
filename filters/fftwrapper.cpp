#include "fftwrapper.h"
#include <QDebug>

FFTWrapper::FFTWrapper(SeriesWrapper &source, qreal frequency)
{
    int count = source.points().count();
    qreal period=1.0/frequency;
    qDebug()<<count;
    qreal length = (static_cast<double>(count)*period)*1000;
    auto fft = new ffft::FFTReal<double>(count);
    double* data = new double[count];

    int j=0;
    for(auto point : source.points()) {
        data[j] = static_cast<double>(point.y());
        j++;
    }

    double* Y = new double[count];
    fft->do_fft(Y, data);
    //for(int i=0; i<count; i++) {
        //qDebug()<<Y[i];
   // }
    QVector<double> P2, P1;
    P2.reserve(count);
    P1.reserve(static_cast<int>(length)/2+1);

    for(int i=0; i<count; i++) {
        P2.append(qAbs(Y[i]/length));
        if(i>static_cast<int>(length/2)) {
            P1.append(2*P2[i]);
        }
    }

    QVector<double> freqDomain;
    freqDomain.reserve(static_cast<int>(length/2));
    for(int i=0; i<length/2; i++) {
        freqDomain.append((frequency*i)/length);
    }

    //double max=0.05;
    for(int i=0; i</*static_cast<int>(length/2)*/P1.count(); i++) {
        this->add(freqDomain[i], P1[i]);
        //if(P1[i]>max && P1[i]<50) max=static_cast<int>(P1[i]);
        //qDebug()<<freqDomain[i]<<P1[i];
    }
}
