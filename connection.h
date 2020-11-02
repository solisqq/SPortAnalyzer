#ifndef CONNECTION_H
#define CONNECTION_H

#include "backgroundserialread.h"

#include <QDialog>
#include <QWidget>
#include <QSerialPort>
#include <QTimer>
#include <QShowEvent>
#include <QThread>
namespace Ui {
class Connection;
}

class Connection : public QDialog
{
    Q_OBJECT
    QSerialPort* port=nullptr;
    QTimer readSPTimer;
    QByteArray buffer;
    QThread workerThread;
public:
    explicit Connection(QWidget *parent = nullptr);
    ~Connection();
    void showEvent(QShowEvent *) override;
    void setVisible(bool visible) override;
    QSerialPort& getPort();
    bool isConnected();
private:
    Ui::Connection *ui;

public slots:
    void setConnection(QSerialPort& sport, BackgroundSerialRead& reader);
    void handleReadSerial();
    void handleReadSerialBG(QByteArray arr);
private slots:
    void on_pushButton_clicked();
};

#endif // CONNECTION_H
