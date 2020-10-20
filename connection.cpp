#include "connection.h"
#include "ui_connection.h"
#include <QDebug>
Connection::Connection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connection)
{
    ui->setupUi(this);
    readSPTimer.setInterval(50);
    connect(&readSPTimer, &QTimer::timeout, this, &Connection::handleReadSerial);
}

Connection::~Connection()
{
    delete ui;
}

void Connection::showEvent(QShowEvent *event)
{
    if(isConnected()) {
        readSPTimer.start();
    }
    QDialog::showEvent(event);
}

void Connection::setVisible(bool visible)
{
    if(!visible) {
        readSPTimer.stop();
        ui->textBrowser->setText("");
    }
    else {
        if(isConnected()) {
            readSPTimer.start();
        }
    }
    QDialog::setVisible(visible);
}

QSerialPort &Connection::getPort()
{
    return *port;
}

void Connection::setConnection(QSerialPort &sport)
{
    port=&sport;

}

bool Connection::isConnected() {
    if(port!=nullptr) if(port->isOpen()) return true;
    return false;
}

void Connection::handleReadSerial()
{
    if(isConnected() && port->bytesAvailable()>0){
        ui->textBrowser->append(port->readAll());
    }
}

void Connection::on_pushButton_clicked()
{
    if(isConnected()) port->write(ui->lineEdit->text().toUtf8());
}
