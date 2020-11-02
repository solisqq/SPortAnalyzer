#include "mainwindow.h"
#include "singlesetter.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "catchgrapheditor.h"
#include "fileexport.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , serialPort(this)
    , plotting(this)
    , motorsDialog(this)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->serialConnectionWidget, &SerialConnection::connected, &serialPort, &Connection::setConnection);
    connect(ui->serialConnectionWidget, &SerialConnection::connected, &plotting, &PlottingDialog::setConnection);
    connect(ui->serialConnectionWidget, &SerialConnection::connected, &motorsDialog, &MotorsDialog::setConnection);
    connect(ui->serialConnectionWidget, &SerialConnection::settingsReady, this, &MainWindow::parseSettings);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_serialPortBtn_clicked()
{
    if(serialPort.isHidden()) serialPort.show();
}

void MainWindow::on_graphBtn_clicked()
{
    if(plotting.isHidden()) plotting.show();
}

void MainWindow::parseSettings(const QStringList &settingsList)
{
    clearLayout(ui->settingsContentLayout);
    clearLayout(ui->settingsContentLayout2);
    QStringList firstList = settingsList.mid(0,settingsList.length()/2);
    QStringList secondList = settingsList.mid(settingsList.length()/2, settingsList.length()-1);

    for(auto setting : firstList) {
        QStringList vals = setting.split(" ");
        if(vals.length()>1) {
            bool valid=false;
            double val = vals.at(1).toDouble(&valid);
            if(valid){
               auto setter = new SingleSetter(vals.at(0), val, ui->settingsContentWidget);
               ui->settingsContentLayout->addWidget(setter);
               connect(setter, &SingleSetter::requestChangeValue, this, &MainWindow::handleChangeValue);
            }
        }
    }
    for(auto setting : secondList) {
        QStringList vals = setting.split(" ");
        if(vals.length()>1) {
            bool valid=false;
            double val = vals.at(1).toDouble(&valid);
            if(valid){
               auto setter = new SingleSetter(vals.at(0), val, ui->settingsContentWidget2);
               ui->settingsContentLayout2->addWidget(setter);
               connect(setter, &SingleSetter::requestChangeValue, this, &MainWindow::handleChangeValue);
            }
        }
    }
}

void MainWindow::handleChangeValue(const QString &valName, double val)
{
    ui->serialConnectionWidget->write(valName+" "+QString::number(val));
}


void MainWindow::clearLayout(QLayout *layoutt) {
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

void MainWindow::on_saveBtn_clicked()
{
    ui->serialConnectionWidget->write("/settingsdo save");
}

void MainWindow::on_motorsBtn_clicked()
{
    this->motorsDialog.show();
}

void MainWindow::on_graphBtnLoad_clicked()
{
    QString name = "";
    auto wrapper = FileExport::ImportSeries(*this, name, 1000, 0);
    if(wrapper!=nullptr) {
        auto dialog = new CatchGraphEditor(*wrapper, nullptr);
        dialog->show();
    } else qDebug()<<"Error while reading file.";
}

void MainWindow::on_aquireData_clicked()
{

}

void MainWindow::on_graphBtn2Load_clicked()
{
    QString name = "";
    auto wrapper = FileExport::ImportSeries(*this, name);
    if(wrapper!=nullptr) {
        auto dialog = new CatchGraphEditor(*wrapper, nullptr);
        dialog->show();
    } else qDebug()<<"Error while reading file.";
}
