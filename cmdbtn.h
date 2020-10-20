#ifndef CMDBTN_H
#define CMDBTN_H

#include <QWidget>

namespace Ui {
class CMDBtn;
}

class CMDBtn : public QWidget
{
    Q_OBJECT
    QString command="";
    bool isEnabled = false;
public:
    explicit CMDBtn(const QString& cmd, QWidget *parent = nullptr);
    ~CMDBtn();

    bool getIsEnabled() const;
    QString getCommand() const;
    void disableBtn();
    void enableBtn();

private slots:
    void on_pushButton_clicked();
private:
    Ui::CMDBtn *ui;

signals:
    void commandSendRequested(const QString& cmd);
};

#endif // CMDBTN_H
