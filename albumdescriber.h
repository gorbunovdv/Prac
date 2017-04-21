#ifndef ALBUMDESCRIBER_H
#define ALBUMDESCRIBER_H

#include <QDialog>
#include "catalog.h"

namespace Ui {
class AlbumDescriber;
}

class AlbumDescriber : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumDescriber(QWidget *parent = 0);
    ~AlbumDescriber();

    void updateInfo(const Album &album, const Catalog &catalog);

private:
    Ui::AlbumDescriber *ui;
};

#endif // ALBUMDESCRIBER_H
