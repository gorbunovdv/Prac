#include "genrediscriber.h"
#include "ui_genrediscriber.h"
#include "types.h"

GenreDiscriber::GenreDiscriber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenreDiscriber)
{
    ui->setupUi(this);
}

GenreDiscriber::~GenreDiscriber()
{
    delete ui;
}

void GenreDiscriber::updateInfo(const Genre &genre, const Catalog &catalog) {
    ui->genreName->setText(QString(genre->name.c_str()));
    ui->authorsCount->setText(QString(std::to_string(std::count_if(all(catalog->getAuthors()), [genre, catalog] (const Author &author) {
        return find_if(all(catalog->getAlbums()), [genre, author] (const Album &album) {
            return album->author == author && album->genre == genre;
        }) != catalog->getAlbums().end();
    })).c_str()));
    ui->albumsCount->setText(QString(std::to_string(std::count_if(all(catalog->getAlbums()), [genre] (const Album &album) {
        return album->genre == genre;
    })).c_str()));
    ui->songsCount->setText(QString(std::to_string(std::count_if(all(catalog->getSongs()), [genre] (const Song &song) {
        return song->genre == genre;
    })).c_str()));
}
