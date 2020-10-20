#ifndef MOTORSDIALOG_H
#define MOTORSDIALOG_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class MotorsDialog;
}

class MotorsDialog : public QDialog
{
    Q_OBJECT
    QSerialPort* port=nullptr;
public:
    explicit MotorsDialog(QWidget *parent = nullptr);
    ~MotorsDialog();

private slots:
    void on_flSlider_valueChanged(int value);
    void on_frSlider_valueChanged(int value);
    void on_blSlider_valueChanged(int value);
    void on_brSlider_valueChanged(int value);
    void on_allSlider_valueChanged(int value);

    void on_calibrateBtn_clicked();

public slots:
    void setConnection(QSerialPort& sport);

private:
    Ui::MotorsDialog *ui;
};

#endif // MOTORSDIALOG_H
