#ifndef FILTERSETTERDIALOG_H
#define FILTERSETTERDIALOG_H

#include <QDialog>

#include <Filter/Filter.h>

namespace Ui {
class FilterSetterDialog;
}

class FilterSetterDialog : public QDialog
{
    Q_OBJECT
    Filter<float>* filter=nullptr;
public:
    explicit FilterSetterDialog(Filter<float>* filter, QWidget *parent = nullptr);
    ~FilterSetterDialog();

private slots:
    void on_FilterSetterDialog_finished(int result);

private:
    Ui::FilterSetterDialog *ui;

signals:
    void filterSetUp(Filter<float>*);
};

#endif // FILTERSETTERDIALOG_H
