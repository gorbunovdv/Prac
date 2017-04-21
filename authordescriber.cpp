#include "authordescriber.h"
#include "ui_authordescriber.h"
#include "types.h"
#include <set>

AuthorDescriber::AuthorDescriber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorDescriber)
{
    ui->setupUi(this);
}

AuthorDescriber::~AuthorDescriber()
{
    delete ui;
}

namespace {
std::string process(int total) {
    static char buf[100];
    sprintf(buf, "%02d:%02d:%02d", total / 3600, (total % 3600) / 60, total % 60);
    return std::string(buf);
}
}

std::string getGenres(const Author &author, const Catalog &catalog) {
    std::set<Genre> genres;
    for (Song song : catalog->getSongs()) {
        if (song->author == author) {
            genres.insert(song->genre);
        }
    }
    std::string result;
    for (Genre genre : genres) {
        if (len(result) > 0) {
            result += ", ";
        }
        result += text(genre->name);
    }
    return result;
}

void AuthorDescriber::updateInfo(const Author &author, const Catalog &catalog) {
    ui->authorName->setText(QString(text(author->name).c_str()));
    ui->albumCount->setText(QString(std::to_string(count_if(all(catalog->getAlbums()), [author] (const Album &album){
        return album->author == author;
    })).c_str()));
    ui->songsCount->setText(QString(std::to_string(count_if(all(catalog->getSongs()), [author] (const Song &song) {
        return song->author == author;
    })).c_str()));
    ui->totalDuration->setText(QString(process(std::accumulate(all(catalog->getSongs()), 0, [author] (int sum, const Song &song) {
        if (song->author != author) {
            return sum;
        }
        return sum + song->duration;
    })).c_str()));
    ui->genres->setText(QString(getGenres(author, catalog).c_str()));
}
