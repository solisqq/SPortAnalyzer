#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connection.h"
#include "motorsdialog.h"
#include "plottingdialog.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Connection serialPort;
    PlottingDialog plotting;
    MotorsDialog motorsDialog;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_serialPortBtn_clicked();
    void on_graphBtn_clicked();
    void parseSettings(const QStringList&);
    void handleChangeValue(const QString& valName, double val);

    void on_saveBtn_clicked();

    void on_motorsBtn_clicked();

    void on_graphBtnLoad_clicked();

    void on_aquireData_clicked();

    void on_graphBtn2Load_clicked();

private:
    Ui::MainWindow *ui;
    void clearLayout(QLayout *layoutt);
};
#endif // MAINWINDOW_H
