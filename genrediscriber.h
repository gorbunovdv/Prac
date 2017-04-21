#ifndef GENREDISCRIBER_H
#define GENREDISCRIBER_H

#include <QDialog>
#include "structures.h"
#include "catalog.h"

namespace Ui {
class GenreDiscriber;
}

class GenreDiscriber : public QDialog
{
    Q_OBJECT

public:
    explicit GenreDiscriber(QWidget *parent = 0);
    ~GenreDiscriber();

    void updateInfo(const Genre &genre, const Catalog &catalog);

private:
    Ui::GenreDiscriber *ui;
};

#endif // GENREDISCRIBER_H
