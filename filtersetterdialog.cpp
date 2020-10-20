#include "filtersetterdialog.h"
#include "ui_filtersetterdialog.h"

FilterSetterDialog::FilterSetterDialog(Filter<float>* filter, QWidget *parent) :
    QDialog(parent),
    filter(filter),
    ui(new Ui::FilterSetterDialog)
{
    ui->setupUi(this);
    ui->contentWidget->layout()->addWidget(filter->getWidget());
    filter->getWidget()->setParent(ui->contentWidget);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

FilterSetterDialog::~FilterSetterDialog()
{
    delete ui;
}

void FilterSetterDialog::on_FilterSetterDialog_finished(int result)
{
    Q_UNUSED(result)
    filter->init();
    emit(filterSetUp(filter));
}
