#ifndef FILEEXPORT_H
#define FILEEXPORT_H
#include "serieswrapper.h"
#define PATH_TO_DATA "C:/Users/Solis/Documents/SPortAnalyzer/data/"
class FileExport
{
public:
    enum FileType {
        SERIES=0
    };
    static void Export(SeriesWrapper &wrapper, QString name);
    static SeriesWrapper *ImportSeries(QWidget &source, QString& name);
    static SeriesWrapper *ImportSeries(QWidget &source, QString &name, qreal frequency, int column, bool toMsecs=true);
    static int CountLinesInFile(const QString &fileName);
    static qreal getClosest2Squared(qreal val);
};

#endif // FILEEXPORT_H
