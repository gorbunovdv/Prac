#ifndef STORAGEFORM_H
#define STORAGEFORM_H

#include <QWidget>

namespace Ui {
class StorageForm;
}

class StorageForm : public QWidget
{
    Q_OBJECT

public:
    explicit StorageForm(QWidget *parent = 0);
    ~StorageForm();

private:
    Ui::StorageForm *ui;
};

#endif // STORAGEFORM_H
