#include "floatviewsetter.h"
#include "ui_floatviewsetter.h"

FloatViewSetter::FloatViewSetter(float* _value, const QString& name, QWidget *parent) :
    QWidget(parent),
    value(_value),
    ui(new Ui::FloatViewSetter)
{
    ui->setupUi(this);
    ui->name->setText(name);
    ui->edit->setText(QString::number(*value));
}

FloatViewSetter::~FloatViewSetter()
{
    delete ui;
}

void FloatViewSetter::on_edit_editingFinished()
{
    bool valid=false;
    float val = ui->edit->text().toFloat(&valid);
    if(!valid) {
        ui->edit->setText(QString::number(*value));
        return;
    }
    *value = val;
}
