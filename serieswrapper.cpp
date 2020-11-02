#include "serieswrapper.h"
#include <QtGlobal>
#include <QDebug>

QPointF SeriesWrapper::getMinimum() const
{
    return minimum;
}

QPointF SeriesWrapper::getMaximum() const
{
    return maximum;
}

void SeriesWrapper::add(qreal x, qreal y)
{
    this->append(x,y);
    minimum.setX(qMin(x,minimum.x()));
    maximum.setX(qMax(x,maximum.x()));
    maximum.setY(qMax(y,maximum.y()));
    minimum.setY(qMin(y,minimum.y()));
}

void SeriesWrapper::add(qreal y)
{
    qreal x = getCurrentX()+1;
    this->append(x,y);
    maximum.setX(qMax(x,maximum.x()));
    maximum.setY(qMax(y,maximum.y()));
    minimum.setY(qMin(y,minimum.y()));
}

SeriesWrapper::SeriesWrapper():
    QSplineSeries(nullptr),
    minimum(0, std::numeric_limits<qreal>::max()),
    maximum(std::numeric_limits<qreal>::min(), std::numeric_limits<qreal>::min())
{
    this->useOpenGL();
}

SeriesWrapper::SeriesWrapper(double *vals, int size):
    QSplineSeries(nullptr),
    minimum(0, std::numeric_limits<qreal>::max()),
    maximum(size-1, std::numeric_limits<qreal>::min())
{
    this->useOpenGL();
    for(int i=0; i<size; i++){
        qreal val = static_cast<qreal>(vals[i]);
        this->append(static_cast<qreal>(i), val);
        if(val>maximum.y())
            maximum.setY(val);
        if(val<minimum.y())
            minimum.setY(val);
    }
}

SeriesWrapper::SeriesWrapper(std::function<float(float)> &func, QList<float> args):
    QSplineSeries(nullptr),
    minimum(std::numeric_limits<qreal>::max(),std::numeric_limits<qreal>::max()),
    maximum(std::numeric_limits<qreal>::min(), std::numeric_limits<qreal>::min()){
    this->useOpenGL();
    for(auto arg : args){
        qreal val = static_cast<qreal>(func(arg));
        this->append(static_cast<qreal>(arg), val);

        maximum.setY(qMax(val, maximum.y()));
        minimum.setY(qMin(val, minimum.y()));
        maximum.setX(qMax(static_cast<qreal>(arg), maximum.x()));
        minimum.setX(qMin(static_cast<qreal>(arg), minimum.x()));
    }
}

SeriesWrapper::SeriesWrapper(std::function<float(float)> &func, SeriesWrapper& orginalWrapper):
    QSplineSeries(nullptr),
    minimum(std::numeric_limits<qreal>::max(),std::numeric_limits<qreal>::max()),
    maximum(std::numeric_limits<qreal>::min(), std::numeric_limits<qreal>::min()){
    this->useOpenGL();
    for(auto orgPoint : orginalWrapper.points()){
        qreal val = static_cast<qreal>(func(static_cast<float>(orgPoint.y())));
        this->append(static_cast<qreal>(orgPoint.x()), val);

        maximum.setY(qMax(val, maximum.y()));
        minimum.setY(qMin(val, maximum.y()));
        maximum.setX(qMax(static_cast<qreal>(orgPoint.x()), maximum.x()));
        minimum.setX(qMin(static_cast<qreal>(orgPoint.x()), minimum.x()));
    }
}

SeriesWrapper::SeriesWrapper(Filter<float> *filter, SeriesWrapper &wrapper):
    QSplineSeries(nullptr),
    minimum(std::numeric_limits<qreal>::max(),std::numeric_limits<qreal>::max()),
    maximum(std::numeric_limits<qreal>::min(), std::numeric_limits<qreal>::min())
{
    this->useOpenGL();
    for(auto orgPoint : wrapper.points()){
        filter->update(static_cast<float>(orgPoint.y()));
        qreal val = static_cast<qreal>(filter->getVal());
        this->append(static_cast<qreal>(orgPoint.x()), val);

        maximum.setY(qMax(val, maximum.y()));
        minimum.setY(qMin(val, maximum.y()));
        maximum.setX(qMax(static_cast<qreal>(orgPoint.x()), maximum.x()));
        minimum.setX(qMin(static_cast<qreal>(orgPoint.x()), minimum.x()));
    }
}

SeriesWrapper::SeriesWrapper(std::function<float(float)> &func, int to, int from):
    QtCharts::QSplineSeries(nullptr),
    minimum(from, std::numeric_limits<qreal>::max()),
    maximum(to, std::numeric_limits<qreal>::min())
{
    this->useOpenGL();
    for(int i=from ; i<to; i++){
        qreal val = static_cast<qreal>(func(i));
        this->append(static_cast<qreal>(i), val);
        if(val>maximum.y())
            maximum.setY(val);
        if(val<minimum.y())
            minimum.setY(val);
    }

}

void SeriesWrapper::show(QtCharts::QChart *chart)
{
    chart->addSeries(this);
    if(chart->axes().count()>1) {
        this->attachAxis(chart->axes()[0]);
        this->attachAxis(chart->axes()[1]);
    }
    /*if(!fit || chart->axes().count()<2) return QPair<QPointF, QPointF>(minimum,maximum);
    chart->axes()[0]->setRange(minimum.x(), maximum.x());
    chart->axes()[1]->setRange(minimum.y(), maximum.y());
    return QPair<QPointF, QPointF>(minimum,maximum);*/
}

void SeriesWrapper::hide(QtCharts::QChart *chart) {
    chart->removeSeries(this);
    if(chart->axes().count()>1) {
        this->detachAxis(chart->axes()[0]);
        this->detachAxis(chart->axes()[1]);
    }
}

void SeriesWrapper::setChart(QtCharts::QChart &chart)
{
    mainChart = &chart;
}

void SeriesWrapper::setColour(const QColor &color)
{
    QPen pen(color);
    pen.setWidth(1);
    this->setPen(pen);
}
void SeriesWrapper::recalcLimits() {
    minimum = QPointF(std::numeric_limits<qreal>::max(),std::numeric_limits<qreal>::max());
    maximum = QPointF(std::numeric_limits<qreal>::min(), std::numeric_limits<qreal>::min());
    for(int i=0; i<this->count(); i++){
        if(points()[i].y()>maximum.y())
            maximum.setY(points()[i].y());
        else if(points()[i].y()<minimum.y())
            minimum.setY(points()[i].y());

        if(points()[i].x()>maximum.x())
            maximum.setX(points()[i].x());
        else if(points()[i].x()<minimum.x())
            minimum.setX(points()[i].x());
    }
}
void SeriesWrapper::resizeToFitFFT()
{
    int j, i=this->count();
    for(j=2; j<i; j = j*2) {}
    if(j>i) j=j/2;
    while(i>j) {this->remove(j);i--;}
    recalcLimits();
}

void SeriesWrapper::show()
{
    if(!mainChart) return;
    show(mainChart);
}

void SeriesWrapper::hide()
{
    if(!mainChart) return;
    hide(mainChart);
}

void SeriesWrapper::setState(int state)
{
    if(state==0) hide();
    else show();
}

qreal SeriesWrapper::getCurrentX()
{
    if(this->count()==0) return 0;
    return QSplineSeries::at(QSplineSeries::count()-1).x();
}

