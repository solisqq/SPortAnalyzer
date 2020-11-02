#include "catchgrapheditor.h"
#include "filtersetterdialog.h"
#include "ui_catchgrapheditor.h"
#include <dialogs/exportseriesdialog.h>
#include <QDebug>
#include <filters/BiquadBS.h>
#include <filters/DynamicNotch.h>
#include <filters/fftwrapper.h>

using namespace QtCharts;

CatchGraphEditor::CatchGraphEditor(SeriesWrapper& initSeries, QWidget *parent) :
    QDialog(parent),
    init_series(initSeries),
    staticRangeX(std::numeric_limits<qreal>::max(), std::numeric_limits<qreal>::min()),
    staticRangeY(std::numeric_limits<qreal>::max(), std::numeric_limits<qreal>::min()),
    fft_object(256),
    chart(new QChart()),
    xaxis(new QValueAxis()),
    yaxis(new QValueAxis()),
    ui(new Ui::CatchGraphEditor)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    colorList<<Qt::GlobalColor::blue<<Qt::GlobalColor::green<<Qt::GlobalColor::cyan<<Qt::GlobalColor::gray<<
               Qt::GlobalColor::black<<Qt::GlobalColor::yellow<<Qt::GlobalColor::darkRed<<Qt::GlobalColor::magenta<<
               Qt::GlobalColor::darkBlue<<Qt::GlobalColor::darkCyan<<Qt::GlobalColor::darkGreen<<Qt::GlobalColor::darkYellow;

    chart->legend()->hide();
    chart->setTitle("Data");

    xaxis->setTickCount(16);
    yaxis->setTickCount(3);

    chart->addAxis(xaxis, Qt::AlignBottom);
    chart->addAxis(yaxis, Qt::AlignLeft);
    cview = new QChartView(this);
    //cview->setRenderHint(QPainter::Antialiasing);
    cview->setChart(chart);
    cview->setMinimumSize(1400,850);

    ui->centralWidget->layout()->addWidget(cview);
    addSeries(initSeries, "Orginal", true);

    ui->filtersComboBox->addItem("FFT");
    ui->filtersComboBox->addItem("NOTCH");
    ui->filtersComboBox->addItem("DYNNOTCH");

    ui->filtersComboBox->setCurrentIndex(0);
    connect(ui->refreshBtn, &QPushButton::clicked, this, qOverload<>(&CatchGraphEditor::updateStaticRanges));
}


void CatchGraphEditor::updateStaticRanges() {
    staticRangeX = QPointF(std::numeric_limits<qreal>::max(), std::numeric_limits<qreal>::min());
    staticRangeY = QPointF(std::numeric_limits<qreal>::max(), std::numeric_limits<qreal>::min());
    for(auto wrapper : wrappers) {
        if(wrapper.second->isChecked()) {
            staticRangeX = QPointF(qMin(wrapper.first->getMinimum().x(), staticRangeX.x()), qMax(wrapper.first->getMaximum().x(), staticRangeX.y()));
            staticRangeY = QPointF(qMin(wrapper.first->getMinimum().y(), staticRangeY.x()), qMax(wrapper.first->getMaximum().y(), staticRangeY.y()));
        }
    }

    setRangeValueFromSliders(true);
    setRangeValueFromSliders(false);
    //staticRangeX = QPointF(xaxis->min(),xaxis->max());
    //staticRangeY = QPointF(yaxis->min(),yaxis->max());
}
void CatchGraphEditor::updateStaticRanges(int fake) {
    Q_UNUSED(fake)
    updateStaticRanges();
}

void CatchGraphEditor::addSeries(SeriesWrapper& series, const QString& name, bool show) {
    auto cb = new QCheckBox(name, ui->seriesListWidget);
    ui->seriesListWidget->layout()->addWidget(cb);
    series.setName(name);
    series.setChart(*chart);
    series.setColour(colorList.at(qMin(colorList.count()-1,coloursCounter)));
    QPalette p = cb->palette();
    p.setColor(QPalette::Active, QPalette::WindowText, colorList.at(qMin(colorList.count()-1,coloursCounter)));
    cb->setPalette(p);

    wrappers.append(QPair<SeriesWrapper*, QCheckBox*>(&series, cb));
    if(show) {cb->setChecked(true); series.show();}
    connect(cb, &QCheckBox::stateChanged, &series, &SeriesWrapper::setState);
    connect(cb, &QCheckBox::stateChanged, this, qOverload<int>(&CatchGraphEditor::updateStaticRanges));
    coloursCounter++;
    if(coloursCounter>=colorList.count()) coloursCounter=0;
    updateStaticRanges();
}

void CatchGraphEditor::on_pushButton_clicked()
{
    for(auto pair : wrappers){
        if(pair.second->isChecked()) {
            auto backup = pair.first;
            auto backup2 = pair.second;
            backup2->setParent(nullptr);
            wrappers.removeOne(pair);
            delete backup;
            delete backup2;
        }
    }
}

CatchGraphEditor::~CatchGraphEditor()
{
    init_series.hide(chart);
    delete &init_series;
    delete ui;
}

void CatchGraphEditor::on_horizontalZoom_2_valueChanged(int value)
{
    Q_UNUSED(value)
    setRangeValueFromSliders(true);
}

void CatchGraphEditor::on_verticalMidd_valueChanged(int value)
{
    Q_UNUSED(value)
    setRangeValueFromSliders(true);
}

void CatchGraphEditor::on_horizontalMidd_valueChanged(int value)
{
    Q_UNUSED(value)
    setRangeValueFromSliders(false);
}

void CatchGraphEditor::on_horizontalZoom_valueChanged(int value)
{
    Q_UNUSED(value)
    setRangeValueFromSliders(false);
}

void CatchGraphEditor::setRangeValueFromSliders(bool vertical) {
    qreal maxVal, zoomPoint, midPoint;
    //staticRangeY 12, -7
    if(vertical) {
        maxVal = (staticRangeY.y() - staticRangeY.x());
        zoomPoint = ((maxVal/1000.0)*ui->horizontalZoom_2->value())/2;
        midPoint = (((maxVal)/1000.0)*ui->verticalMidd->value())+staticRangeY.x();
    } else {
        maxVal = (staticRangeX.y() - staticRangeX.x());
        zoomPoint = ((maxVal/1000.0)*ui->horizontalZoom->value())/2;
        midPoint = ((maxVal)/1000.0)*ui->horizontalMidd->value();
    }

    qreal min = midPoint-((maxVal/2.0)-zoomPoint);
    qreal max = midPoint+((maxVal/2.0)-zoomPoint);
    if(vertical) chart->axes().at(1)->setRange(min,max);
    else chart->axes().at(0)->setRange(min,max);
}

void CatchGraphEditor::on_saveBtn_clicked()
{

    ExportSeriesDialog* dialog = new ExportSeriesDialog(wrappers);
    dialog->show();
}

void CatchGraphEditor::on_loadBtn_clicked()
{
    QString name="";
    SeriesWrapper *wrapper = FileExport::ImportSeries(*this, name);
    addSeries(*wrapper,name);
}

void CatchGraphEditor::on_addFilterBtn_clicked()
{
    if(getShowedWrappersCount()!=1) return;
    if(ui->filtersComboBox->currentText()=="FFT") {
        for(auto pair : wrappers)
            if(pair.second->isChecked())
                addSeries(*(new FFTWrapper(*pair.first, 1000)), "FFT of"+pair.first->name());
    }
    else if(ui->filtersComboBox->currentText()=="NOTCH") {
        auto dialog = new FilterSetterDialog(new BiquadBS<float>(1000, 100, 1,0));
        connect(dialog, &FilterSetterDialog::filterSetUp, this, &CatchGraphEditor::addFilterSeries);
        dialog->show();
    } else if(ui->filtersComboBox->currentText()=="DYNNOTCH") {
        auto dialog = new FilterSetterDialog(new DynamicNotch<float>(9, 1000, 500, 0, 132));
        connect(dialog, &FilterSetterDialog::filterSetUp, this, &CatchGraphEditor::addFilterSeries);
        dialog->show();
    }
}

void CatchGraphEditor::addFilterSeries(Filter<float>* filter) {
    if(getShowedWrappersCount()!=1) return;
    for(auto pair : wrappers){
        if(pair.second->isChecked()){
            auto wrapped = new SeriesWrapper(filter, *pair.first);
            addSeries(*wrapped,ui->filtersComboBox->currentText());
        }
    }
}

int CatchGraphEditor::getShowedWrappersCount() {
    int counter=0;
    for(auto pair : wrappers)
        if(pair.second->isChecked()) counter++;
    return counter;
}


