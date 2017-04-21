#include "radioprogram.h"


double RequestsProgram_::evaluateQuality(int timestamp, Song song) {
  double quality = 0;
  for (Query query : queries) {
    if (query->songMatches(song)) {
      quality += 1;
    }
  }
  for (Play play : statistics->getPlays()) {
    if (play->song->author == song->author) {
      quality -= 1. / (timestamp - play->timestamp);
    }
    if (play->song->album == song->album) {
      quality -= 1. / (timestamp - play->timestamp) * 5;
    }
    if (play->song == song) {
      quality -= 1. / (timestamp - play->timestamp) * 10;
    }
  }
  return quality;
}

double HitParadProgram_::evaluateQuality(int timestamp, Song song) {
  double quality = 1. / 7200 * statistics->getSongRequestsCount(song);
  for (Play play : statistics->getPlays()) {
    if (play->song->author == song->author) {
      quality += 1. / (timestamp - play->timestamp);
    }
    if (play->song->album == song->album) {
      quality -= 1. / (timestamp - play->timestamp) * 5;
    }
    if (play->song == song) {
      quality -= 1. / (timestamp - play->timestamp) * 10;
    }
  }
  return quality;
}

Song RadioProgram_::pickNextSong(Catalog catalog, int timestamp) {
  std::map<Song, double> quality = getQualities(catalog, timestamp);
  Song nextSong = std::max_element(quality.begin(), quality.end(),
      [](auto firstEntity, auto secondEntity) {
        return firstEntity.second < secondEntity.second;
      })->first;
  postprocessSong(nextSong, timestamp);
  return nextSong;
}

RadioProgram_::RadioProgram_(std::string name, Genre genre, int start, int duration,
    Statistics statistics) :
    name(name),
    genre(genre),
    start(start),
    duration(duration),
    statistics(statistics) {}

std::string RadioProgram_::getName() {
  return name;
}

std::map<Song, double> RequestsProgram_::getQualities(Catalog catalog, int timestamp) {
  std::map<Song, double> quality;
  for (Song song : catalog->getSongsByGenre(genre)) {
    quality[song] = evaluateQuality(timestamp, song);
  }
  return quality;
}

void RequestsProgram_::postprocessSong(Song song, int timestamp) {
  queries.resize(std::remove_if(queries.begin(), queries.end(), [song](Query query) {
    return query->songMatches(song);
  }) - queries.begin());
}

RequestsProgram_::RequestsProgram_(std::string name, Genre genre, int start, int duration,
    Statistics statistics) :
    RadioProgram_(name, genre, start, duration, statistics) {}

std::map<Song, double> HitParadProgram_::getQualities(Catalog catalog, int timestamp) {
  std::map<Song, double> quality;
  for (Song song : catalog->getSongsByGenre(genre)) {
    quality[song] = evaluateQuality(timestamp, song);
  }
  return quality;
}

HitParadProgram_::HitParadProgram_(std::string name, Genre genre, int start, int duration,
    Statistics statistics) :
    RadioProgram_(name, genre, start, duration, statistics) {}
