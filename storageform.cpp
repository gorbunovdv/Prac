#include "storageform.h"
#include "ui_storageform.h"

StorageForm::StorageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StorageForm)
{
    ui->setupUi(this);
}

StorageForm::~StorageForm()
{
    delete ui;
}
