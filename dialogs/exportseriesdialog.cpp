#include "exportseriesdialog.h"
#include "ui_exportseriesdialog.h"
#include <fileexport.h>

ExportSeriesDialog::ExportSeriesDialog(QList<QPair<SeriesWrapper*, QCheckBox*> >& series, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportSeriesDialog)
{
    ui->setupUi(this);
    if(series.count()<=0) {
        this->close();
        return;
    }
    this->setAttribute(Qt::WA_DeleteOnClose);
    for(auto wrapper : series){
        ui->comboBox->addItem(wrapper.first->name(), QVariant::fromValue(static_cast<void*>(wrapper.first)));
    }
    ui->comboBox->setCurrentIndex(0);
}

ExportSeriesDialog::~ExportSeriesDialog()
{
    delete ui;
}

void ExportSeriesDialog::on_buttonBox_accepted()
{
    FileExport::Export(
                *static_cast<SeriesWrapper*>(ui->comboBox->currentData().value<void*>()),
                ui->lineEdit->text()+"_"+ui->comboBox->currentText()
                );

}
