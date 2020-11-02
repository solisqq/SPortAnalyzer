#ifndef BACKGROUNDSERIALREAD_H
#define BACKGROUNDSERIALREAD_H

#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QTimer>

class BackgroundSerialRead : public QThread
{
    Q_OBJECT
    QSerialPort& port;
    QByteArray received;
    QTimer readSPTimer;
    int buffer=1000;
public:
    explicit BackgroundSerialRead(QSerialPort& port, int buffer);
    void run() override;

signals:
    void dataAvailable(QByteArray array);

};

#endif // BACKGROUNDSERIALREAD_H
