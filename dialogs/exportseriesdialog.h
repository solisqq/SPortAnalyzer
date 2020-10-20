#ifndef EXPORTSERIESDIALOG_H
#define EXPORTSERIESDIALOG_H

#include <QDialog>
#include <serieswrapper.h>

namespace Ui {
class ExportSeriesDialog;
}

class ExportSeriesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportSeriesDialog(QList<QPair<SeriesWrapper*, QCheckBox*> >& series, QWidget *parent = nullptr);
    ~ExportSeriesDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ExportSeriesDialog *ui;
};

#endif // EXPORTSERIESDIALOG_H
