#ifndef CATCHGRAPHEDITOR_H
#define CATCHGRAPHEDITOR_H

#include <QDialog>
#include "fft-real/FFTReal.h"
#include <QtCharts/qlineseries.h>
#include <QtCharts/qchart.h>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
#include <serieswrapper.h>
#include <QCheckBox>
#include <fileexport.h>
#include <QtGlobal>

namespace Ui {
class CatchGraphEditor;
}

class CatchGraphEditor : public QDialog
{
    Q_OBJECT
    SeriesWrapper& init_series;
    QPointF staticRangeX;
    QPointF staticRangeY;
    QList<QPair<SeriesWrapper*, QCheckBox*> > wrappers;
    ffft::FFTReal<float> fft_object;
    QtCharts::QChart* chart=nullptr;
    QtCharts::QValueAxis* xaxis=nullptr;
    QtCharts::QValueAxis* yaxis=nullptr;
    QtCharts::QChartView *cview=nullptr;

    int coloursCounter = 0;
    QVector<QColor> colorList;
public:
    explicit CatchGraphEditor(SeriesWrapper& initSeries, QWidget *parent = nullptr);
    ~CatchGraphEditor();
    void addSeries(SeriesWrapper &series, const QString &name, bool show=true);
    int getShowedWrappersCount();
private slots:
    void on_horizontalZoom_2_valueChanged(int value);
    void on_verticalMidd_valueChanged(int value);
    void on_horizontalMidd_valueChanged(int value);
    void on_horizontalZoom_valueChanged(int value);
    void on_saveBtn_clicked();

    void on_loadBtn_clicked();

    void on_addFilterBtn_clicked();
    void updateStaticRanges();
    void updateStaticRanges(int fake);
    void addFilterSeries(Filter<float> *filter);
    void on_pushButton_clicked();

private:
    Ui::CatchGraphEditor *ui;

    void setRangeValueFromSliders(bool vertical=false);
};

#endif // CATCHGRAPHEDITOR_H
