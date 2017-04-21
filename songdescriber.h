#ifndef SONGDESCRIBER_H
#define SONGDESCRIBER_H

#include <QDialog>
#include "catalog.h"

namespace Ui {
class SongDescriber;
}

class SongDescriber : public QDialog
{
    Q_OBJECT

public:
    explicit SongDescriber(QWidget *parent = 0);
    ~SongDescriber();

    void updateInfo(const Song &song, const Catalog &catalog);

private:
    Ui::SongDescriber *ui;
};

#endif // SONGDESCRIBER_H
