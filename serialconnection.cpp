#include "serialconnection.h"
#include "ui_serialconnection.h"

#include <QSerialPortInfo>
#include <QTimer>
#include <Commands.h>

SerialConnection::SerialConnection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialConnection)
{
    ui->setupUi(this);
    port.setBaudRate(500000);
    port.setDataBits(QSerialPort::Data8);
    port.setParity(QSerialPort::NoParity);
    port.setStopBits(QSerialPort::OneStop);
    ui->checkBox->setDisabled(true);
    for(auto portInfo : QSerialPortInfo::availablePorts()) {
        ui->comboBox->addItem(portInfo.portName());
    }
    ui->comboBox->setCurrentIndex(-1);
    ui->pushButton->hide();
}

SerialConnection::~SerialConnection()
{
    delete ui;
}

void SerialConnection::getSettings() {
    port.write(Commands::Settings::show.toUtf8());
    QTimer::singleShot(1000, this, &SerialConnection::readSettings);
}

void SerialConnection::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(port.isOpen()) port.close();
    port.setPortName(arg1);
    if(port.open(QIODevice::ReadWrite)){
        ui->checkBox->setChecked(true);
        getSettings();
        emit(connected(port));
        ui->pushButton->show();
    } else {
        ui->checkBox->setChecked(false);
        ui->pushButton->hide();
    }
}

void SerialConnection::readSettings()
{
    emit(settingsReady(QString::fromUtf8(port.readAll()).split("\n")));
}

void SerialConnection::write(const QString& val) {
    if(port.isOpen()) port.write(val.toUtf8());
}

void SerialConnection::on_pushButton_clicked()
{
    getSettings();
}
