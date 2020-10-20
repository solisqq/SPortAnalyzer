#include "singlesetter.h"
#include "ui_singlesetter.h"

SingleSetter::SingleSetter(const QString referencePath, double val, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleSetter)
{
    ui->setupUi(this);
    setValue(val);
    setName(referencePath);
}

void SingleSetter::setValue(double val) {
    value=val;
    ui->dataEdit->setText(QString::number(val));
}

void SingleSetter::setName(const QString& path) {
    ui->nameLabel->setText(path);
}

SingleSetter::~SingleSetter()
{
    delete ui;
}

void SingleSetter::on_dataEdit_editingFinished()
{
    bool valid=false;
    double val = ui->dataEdit->text().toDouble(&valid);
    if(valid) {
        emit(requestChangeValue(ui->nameLabel->text(), val));
        setValue(val);
    }
    else setValue(value);
}
