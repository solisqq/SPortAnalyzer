#ifndef SERIALCONNECTION_H
#define SERIALCONNECTION_H

#include "backgroundserialread.h"

#include <QWidget>
#include <QSerialPort>
namespace Ui {
class SerialConnection;
}

class SerialConnection : public QWidget
{
    Q_OBJECT
    QSerialPort port;
public:
    explicit SerialConnection(QWidget *parent = nullptr);
    ~SerialConnection();
    void write(const QString &val);
    BackgroundSerialRead *readBG=nullptr;
private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void readSettings();
    void on_pushButton_clicked();

private:
    Ui::SerialConnection *ui;
    void getSettings();
signals:
    void connected(QSerialPort& port, BackgroundSerialRead& sr);
    void settingsReady(const QStringList& settings);
};

#endif // SERIALCONNECTION_H
