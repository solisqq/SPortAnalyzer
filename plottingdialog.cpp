#include "catchgrapheditor.h"
#include "plottingdialog.h"
#include "ui_plottingdialog.h"

#include <QLineSeries>
#include <QDebug>
#include <QCheckBox>
PlottingDialog::PlottingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlottingDialog)
{
    ui->setupUi(this);
    //this->setAttribute(Qt::WA_DeleteOnClose);
    m_chart = new QtCharts::QChart;
    chartView = new QChartView(m_chart);
    //chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(800,600);
    m_series = new QLineSeries();
    m_series->useOpenGL();
    m_chart->addSeries(m_series);
    axisX = new QValueAxis;
    axisX->setRange(0,4);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("f (Hz)");
    axisY = new QValueAxis;
    axisY->setRange(-1000,1000);
    axisY->setTitleText("|P1(f)|");
    m_chart->setAxisX(axisX,m_series);
    m_chart->setAxisY(axisY,m_series);
    //m_chart->addAxis(axisX, Qt::AlignBottom);
    //m_chart->addAxis(axisY, Qt::AlignLeft);
    m_chart->legend()->hide();
    m_chart->setTitle("Data");
    ui->chartLayout->addWidget(chartView);
    readSPTimer.setInterval(100);
    //connect(&readSPTimer, &QTimer::timeout, this, &PlottingDialog::handleReadSerial);

    cmdbtns<< new CMDBtn("/stear", ui->commandsWidget)<<
              new CMDBtn("/gyro", ui->commandsWidget)<<
              new CMDBtn("/accel", ui->commandsWidget)<<
              new CMDBtn("/imu", ui->commandsWidget)<<
              new CMDBtn("/pid", ui->commandsWidget)<<
              new CMDBtn("/control", ui->commandsWidget)<<
              new CMDBtn("/rx", ui->commandsWidget);

    for(auto cmdbtn : cmdbtns){
        ui->commandsLayout->addWidget(cmdbtn);
        connect(cmdbtn, &CMDBtn::commandSendRequested, this, &PlottingDialog::serialWrite);
    }
    timeStamp=1/freq;
    ui->XRangeEdit->setText(QString::number(XRange));
}

PlottingDialog::~PlottingDialog()
{
    delete ui;
}

void PlottingDialog::showEvent(QShowEvent *event)
{
    if(isConnected()) {
        startT();
    }
    QDialog::showEvent(event);
}

void PlottingDialog::addToGraph(const QVector<QPointF>& toAdd)
{
    QVector<QPointF> points = m_series->pointsVector();

    for(auto item : toAdd) {
        if(points.count()>range) points.pop_front();
        points.push_back(item);
    }
    QPointF minMaxY(9999999,-9999999);
    for(auto point : points) {
        if(minMaxY.y()<point.y()) minMaxY.setY(point.y());
        else if(minMaxY.x()>point.y()) minMaxY.setX(point.y());
    }
    if(yRangeLimit>0) axisY->setRange(-yRangeLimit,yRangeLimit);
    else axisY->setRange(minMaxY.x(),minMaxY.y());

    m_series->replace(points);
    axisX->setRange(points.last().x()-XRange, points.last().x()+0.2);
}

void PlottingDialog::setVisible(bool visible)
{
    if(!visible) {
        readSPTimer.stop();
        forceStopPlotting();
    }
    else if(isConnected()) startT();
    QDialog::setVisible(visible);
}

void PlottingDialog::setConnection(QSerialPort &sport, BackgroundSerialRead &reader)
{
    port=&sport;
    connect(&reader, &BackgroundSerialRead::dataAvailable, this, &PlottingDialog::handleReadSerialBG);
}

void PlottingDialog::forceStopPlotting() {
    for(auto cmdbtn : cmdbtns){
        if(cmdbtn->getIsEnabled()) {
            if(isConnected() && port->bytesAvailable()>0){
                //port->write(cmdbtn->getCommand().toUtf8());
                cmdbtn->disableBtn();
                break;
            }
        }
    }
}

void PlottingDialog::changeValuesCount(int count)
{
    if(count==valuesCount) return;
    ui->selectItemCombo->clear();
    valuesCount=count;
    for(int i=0; i<count; i++) {
        ui->selectItemCombo->addItem(QString::number(i));
    }
}
void PlottingDialog::clearLayout(QLayout *layoutt) {
    if (layoutt != nullptr )
    {
        QLayoutItem* item;
        while ( ( item = layoutt->takeAt( 0 ) ) != nullptr )
        {
            delete item->widget();
            delete item;
        }
    }
}

void PlottingDialog::stopPlotting()
{
    readSPTimer.stop();
    m_series->clear();
    chartView->hide();
}
void PlottingDialog::startPlotting()
{
    m_series->clear();
    readSPTimer.start();
    chartView->show();
}
void PlottingDialog::startT() {
    readSPTimer.start();
    totalTimeStamp = 0;
}

bool PlottingDialog::isConnected() {
    if(port!=nullptr) if(port->isOpen()) return true;
    return false;
}

void PlottingDialog::handleReadSerial()
{
    if(isConnected() && port->bytesAvailable()>0){
        //ui->textBrowser->append(port->readAll());
        prevLeftData+=port->readAll();
        QStringList lines = prevLeftData.split("\n");
        if(!lines.isEmpty()) {
            QVector<QPointF> vals;
            prevLeftData = lines.last();
            for(int i=0; i<lines.count()-2; i++) {
                QStringList values = lines.at(i).split(",");
                if(values.count()>1) {
                    changeValuesCount(values.count());
                    if(xoffset==0) xoffset = values.at(0).toULong();
                    totalTimeStamp+=timeStamp;
                    vals.append(QPointF(totalTimeStamp, values.at(toShowValuesID).toDouble()));
                    if(fftOn) {
                        fftCounter++;
                        if(fftCounter>=fftCount) {
                            series->add(values.at(toShowValuesID).toDouble());
                            fftOn=false;
                            fftCounter=0;
                            auto editor = new CatchGraphEditor(*series);
                            editor->show();
                        } else {
                            series->add(values.at(toShowValuesID).toDouble());
                        }
                    }
                }
            }
            if(vals.count()>0) {
                addToGraph(vals);
            }
        }
    }
}

void PlottingDialog::handleReadSerialBG(QByteArray newData)
{
    //if(isConnected() && port->bytesAvailable()>0){
    //ui->textBrowser->append(port->readAll());
    prevLeftData+=newData;
    QStringList lines = prevLeftData.split("\n");
    if(!lines.isEmpty()) {
        QVector<QPointF> vals;
        prevLeftData = lines.last();
        for(int i=0; i<lines.count()-2; i++) {
            QStringList values = lines.at(i).split(",");
            if(values.count()>1) {
                changeValuesCount(values.count());
                if(xoffset==0) xoffset = values.at(0).toULong();
                totalTimeStamp+=timeStamp;
                vals.append(QPointF(totalTimeStamp, values.at(toShowValuesID).toDouble()));
                if(fftOn) {
                    fftCounter++;
                    if(fftCounter>=fftCount) {
                        series->add(values.at(toShowValuesID).toDouble());
                        fftOn=false;
                        fftCounter=0;
                        auto editor = new CatchGraphEditor(*series);
                        editor->show();
                    } else {
                        series->add(values.at(toShowValuesID).toDouble());
                    }
                }
            }
        }
        if(vals.count()>0) {
            addToGraph(vals);
        }
    }
    //}

}

void PlottingDialog::on_XRangeEdit_editingFinished()
{
    bool valid = false;
    double val = ui->XRangeEdit->text().toDouble(&valid);
    if(valid) {
        XRange = val;
        range = static_cast<int>(XRange*freq);
    }
}

void PlottingDialog::serialWrite(const QString& data) {
    if(isConnected()) {
        port->write(data.toUtf8());
    }
}

void PlottingDialog::on_fftBtn_clicked()
{
    int val = ui->fftSamplesCountCB->currentText().toInt();
    fftCount = val;
    fftOn = true;
    fftCounter = 0;
    fftValues = new double[val];
    fftdialog = new FFTDialog(freq,val,this);
    series = new SeriesWrapper();
    //auto dialog = new FFTDialog(950, val, this);
}

void PlottingDialog::on_yRangeEdit_editingFinished()
{
    bool valid = false;
    double val = ui->yRangeEdit->text().toDouble(&valid);
    if(!valid) {
        ui->yRangeEdit->setText(QString::number(yRangeLimit));
        return;
    }
    yRangeLimit = val;
}

void PlottingDialog::on_selectItemCombo_currentIndexChanged(int index)
{
    toShowValuesID=index;
}

void PlottingDialog::on_pushButton_clicked()
{
    if(ui->pushButton->text()=="STOP") {
        ui->pushButton->setText("START");
        stopPlotting();
    }
    else {
        ui->pushButton->setText("STOP");
        startPlotting();
    }
}
