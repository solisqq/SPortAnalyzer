#ifndef CATCHGRAPHVIEW_H
#define CATCHGRAPHVIEW_H
#include <QtCharts/QChartView>

class CatchGraphView: public QtCharts::QChartView
{
    qreal maxX = 0;
    qreal minX = 0;
    qreal maxY = 0;
    qreal minY = 0;
public:
    CatchGraphView(QWidget *parent=nullptr);
    //CatchGraphView(QtCharts::QChart& chart, QWidget *parent=nullptr);
};

#endif // CATCHGRAPHVIEW_H
