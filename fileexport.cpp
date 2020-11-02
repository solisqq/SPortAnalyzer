#include "fileexport.h"
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>

void FileExport::Export(SeriesWrapper &wrapper, QString name)
{
    QFile data(PATH_TO_DATA+name+".series");
    int i=0;
    while(data.exists()) {
        i++;
        data.setFileName(PATH_TO_DATA+name+QString::number(i)+".series");
    }
    if(data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        for(auto point : wrapper.points()) {
            out << QString::number(point.x())<<","<<QString::number(point.y())<<"\n";
        }
    }
}

SeriesWrapper* FileExport::ImportSeries(QWidget& source, QString& name) {
    SeriesWrapper* wrapper=nullptr;
    auto fileName = QFileDialog::getOpenFileName(&source, "Open series", PATH_TO_DATA, "Series data (*.series)");
    QFile data(fileName);
    if(data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        QString line;
        while(in.readLineInto(&line)) {
            QStringList posStr = line.split(",");
            if(posStr.count()==2) {
                bool valid = false;
                qreal x = posStr[0].toDouble(&valid); if(!valid) break;
                qreal y = posStr[1].toDouble(&valid); if(!valid) break;
                if(wrapper==nullptr) wrapper = new SeriesWrapper();
                wrapper->add(x,y);
            }
        }
    }
    QFileInfo fileInfo(data);
    name = fileInfo.fileName();
    return wrapper;
}

SeriesWrapper* FileExport::ImportSeries(QWidget& source, QString& name, qreal frequency, int column, bool toMsecs) {
    SeriesWrapper* wrapper=nullptr;
    auto fileName = QFileDialog::getOpenFileName(&source, "Open series", PATH_TO_DATA, "Series data (*.series)");
    int linesCount = CountLinesInFile(fileName);
    if(linesCount<64) return nullptr;
    int readCount = getClosest2Squared(linesCount);
    QFile data(fileName);
    if(data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        QString line;
        for(int i=0; i<readCount; i++){
            in.readLineInto(&line);
            QStringList posStr = line.split(",");
            bool valid = false;
            qreal x=0;
            if(toMsecs) x = static_cast<qreal>(i);
            else x = static_cast<qreal>(i)/frequency;

            if(posStr.count()<column) return nullptr;
            qreal y = posStr[column].toDouble(&valid); if(!valid) return nullptr;
            if(wrapper==nullptr) wrapper = new SeriesWrapper();
            wrapper->add(x,y);
        }
        data.close();
    }
    QFileInfo fileInfo(data);
    name = fileInfo.fileName();
    return wrapper;
}

int FileExport::CountLinesInFile(const QString &fileName)
{
    QFile data(fileName);
    int i=0;
    if(data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        QString line;
        while(in.readLineInto(&line)) {
            i++;
        }
        data.close();
    }

    return i;
}

qreal FileExport::getClosest2Squared(qreal val)
{
    int j, i=val;
    for(j=2; j<i; j = j*2) {}
    if(j>i) j=j/2;
    return j;
}
