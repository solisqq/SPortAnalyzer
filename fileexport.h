#ifndef FILEEXPORT_H
#define FILEEXPORT_H
#include "serieswrapper.h"
#define PATH_TO_DATA "C:/Users/kamil/Documents/Programming/SPortAnalyzer/data/"
class FileExport
{
public:
    enum FileType {
        SERIES=0
    };
    static void Export(SeriesWrapper &wrapper, QString name);
    static SeriesWrapper *ImportSeries(QWidget &source, QString& name);
};

#endif // FILEEXPORT_H
