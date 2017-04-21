#include "songdescriber.h"
#include "ui_songdescriber.h"
#include "types.h"

SongDescriber::SongDescriber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SongDescriber)
{
    ui->setupUi(this);
}

SongDescriber::~SongDescriber()
{
    delete ui;
}

namespace {
std::string process(int time) {
    static char buf[100];
    sprintf(buf, "%02d:%02d", time / 60, time % 60);
    return buf;
}
}

void SongDescriber::updateInfo(const Song &song, const Catalog &catalog) {
    ui->songName->setText(QString(text(song->name).c_str()));
    ui->albumName->setText(QString(text(song->album->name).c_str()));
    ui->authorName->setText(QString(text(song->author->name).c_str()));
    ui->duration->setText(QString(process(song->duration).c_str()));
}
