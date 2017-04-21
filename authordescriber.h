#ifndef AUTHORDESCRIBER_H
#define AUTHORDESCRIBER_H

#include <QDialog>
#include "catalog.h"

namespace Ui {
class AuthorDescriber;
}

class AuthorDescriber : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorDescriber(QWidget *parent = 0);
    ~AuthorDescriber();

    void updateInfo(const Author &author, const Catalog &catalog);

private:
    Ui::AuthorDescriber *ui;
};

#endif // AUTHORDESCRIBER_H
