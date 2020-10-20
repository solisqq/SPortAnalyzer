#include "motorsdialog.h"
#include "ui_motorsdialog.h"
#include <QDebug>
MotorsDialog::MotorsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MotorsDialog)
{
    ui->setupUi(this);
}

MotorsDialog::~MotorsDialog()
{
    delete ui;
}

void MotorsDialog::on_flSlider_valueChanged(int value)
{
    if(port==nullptr || !port->isOpen()) return;
    port->write(QString("/controldo fl "+QString::number(value)).toUtf8());
}

void MotorsDialog::on_frSlider_valueChanged(int value)
{
    if(port==nullptr || !port->isOpen()) return;
    port->write(QString("/controldo fr "+QString::number(value)).toUtf8());
}

void MotorsDialog::on_blSlider_valueChanged(int value)
{
    if(port==nullptr || !port->isOpen()) return;
    port->write(QString("/controldo bl "+QString::number(value)).toUtf8());
}

void MotorsDialog::on_brSlider_valueChanged(int value)
{
    if(port==nullptr || !port->isOpen()) return;
    port->write(QString("/controldo br "+QString::number(value)).toUtf8());
}

void MotorsDialog::on_allSlider_valueChanged(int value)
{
    if(port==nullptr || !port->isOpen()) return;
    if(value<1250) {
        port->write(QString("/controldo stop").toUtf8());
        return;
    }
    port->write(QString("/controldo "+QString::number(value)).toUtf8());
}

void MotorsDialog::setConnection(QSerialPort &sport)
{
    port = &sport;
}

void MotorsDialog::on_calibrateBtn_clicked()
{
    if(port==nullptr || !port->isOpen()) return;
    port->write(QString("/controldo !calibrate").toUtf8());
}
