#include "fileexport.h"

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
