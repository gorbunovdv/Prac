#include "albumdescriber.h"
#include "ui_albumdescriber.h"
#include "types.h"

AlbumDescriber::AlbumDescriber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlbumDescriber)
{
    ui->setupUi(this);
}

AlbumDescriber::~AlbumDescriber()
{
    delete ui;
}

namespace {
    std::string process(int time) {
        static char buf[100];
        sprintf(buf, "%02d:%02d:%02d", time / 3600, (time % 3600) / 60, time % 60);
        return buf;
    }
}

void AlbumDescriber::updateInfo(const Album &album, const Catalog &catalog) {
    ui->albumName->setText(QString(text(album->name).c_str()));
    ui->authorName->setText(QString(text(album->author->name).c_str()));
    ui->genre->setText(QString(text(album->genre->name).c_str()));
    ui->songsCount->setText(QString(std::to_string(std::count_if(all(catalog->getSongs()), [album](const Song &song) {
        return song->album == album;
    })).c_str()));
    ui->totalDuration->setText(QString(process(std::accumulate(all(catalog->getSongs()), 0, [album](int sum, const Song &song) {
        if (song->album != album) {
            return sum;
        }
        return sum + song->duration;
    })).c_str()));
}
