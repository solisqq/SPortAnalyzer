#include "aquiredatadialog.h"
#include "ui_aquiredatadialog.h"

AquireDataDialog::AquireDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AquireDataDialog)
{
    ui->setupUi(this);
}

AquireDataDialog::~AquireDataDialog()
{
    delete ui;
}

void AquireDataDialog::on_buttonBox_accepted()
{
    ui->nameEdit->text();
}
