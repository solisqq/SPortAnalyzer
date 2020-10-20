#include "cmdbtn.h"
#include "ui_cmdbtn.h"

bool CMDBtn::getIsEnabled() const
{
    return isEnabled;
}

QString CMDBtn::getCommand() const
{
    return command;
}

CMDBtn::CMDBtn(const QString& cmd, QWidget *parent) :
    QWidget(parent),
    command(cmd),
    ui(new Ui::CMDBtn)
{
    ui->setupUi(this);
    ui->pushButton->setText(cmd.mid(1,cmd.length()-1));
    disableBtn();
}

void CMDBtn::disableBtn() {
    isEnabled=false;
    this->setStyleSheet("QPushButton {"
                        "border:2px solid rgb(30, 50, 80);"
                        "border-radius: 5px;"
                        "padding: 5px 10px;"
                        "background-color: rgb(54, 54, 54);"
                        "color: rgb(200, 200, 200);"
                        "font-weight: 500;"
                    "}");
}

void CMDBtn::enableBtn() {
    isEnabled=true;
    this->setStyleSheet("QPushButton {"
                        "border:2px solid rgb(74, 131, 255);"
                        "border-radius: 5px;"
                        "padding: 5px 10px;"
                        "background-color: rgb(54, 54, 54);"
                        "color: rgb(74, 131, 255);"
                        "font-weight: 500;"
                    "}");
}

CMDBtn::~CMDBtn()
{
    delete ui;
}

void CMDBtn::on_pushButton_clicked()
{
    if(isEnabled) disableBtn();
    else enableBtn();
    emit(commandSendRequested(command));
}
