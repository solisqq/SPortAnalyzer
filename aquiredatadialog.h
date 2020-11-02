#ifndef AQUIREDATADIALOG_H
#define AQUIREDATADIALOG_H

#include <QDialog>

namespace Ui {
class AquireDataDialog;
}

class AquireDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AquireDataDialog(QWidget *parent = nullptr);
    ~AquireDataDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AquireDataDialog *ui;
};

#endif // AQUIREDATADIALOG_H
