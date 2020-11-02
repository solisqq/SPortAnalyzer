#include "backgroundserialread.h"
#include <QDebug>
BackgroundSerialRead::BackgroundSerialRead(QSerialPort& port, int buffer):
    QThread(),
    port(port),
    buffer(buffer)
{
    //readSPTimer.setInterval(interval);
    //connect(&readSPTimer, &QTimer::timeout, this, &BackgroundSerialRead::readInBG);
}

void BackgroundSerialRead::run()
{
    while(port.isOpen()) {
        port.waitForReadyRead(200);
        if(port.bytesAvailable()>0){
            received.append(port.readAll());
        }
        if(received.count()>buffer) {
            emit(dataAvailable(received));
            //qDebug()<<received;
            received = QByteArray();
        }
    }

}


