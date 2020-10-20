#ifndef FFTWRAPPER_H
#define FFTWRAPPER_H

#include <serieswrapper.h>
#include <fft-real/FFTReal.h>

class FFTWrapper : public SeriesWrapper
{
public:
    FFTWrapper(SeriesWrapper &source, qreal frequency);
};

#endif // FFTWRAPPER_H
