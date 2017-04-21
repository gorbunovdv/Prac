#include "requestsgenerator.h"


std::vector<Event> RequestsGenerator::generate(Catalog catalog) {
  std::vector<Event> queries;
  for (int i = 0; i < duration / (4 * 60) * 2; i++) {
    queries.push_back(generate_query(catalog));
  }
  return queries;
}

Event RequestsGenerator::generate_query(Catalog catalog) {
  int leftBound = timestamp, rightBound = timestamp + duration;
  int queryTimestamp = randInt(leftBound, rightBound);
  int type = randInt(0, 2);
  Query result;
  if (type == 0) {
    decltype(auto) authors = catalog->getAuthors();
    result = std::make_shared<AuthorQuery_>(authors[randInt(0, len(authors) - 1)]);
  }
  if (type == 1) {
    decltype(auto) albums = catalog->getAlbums();
    result = std::make_shared<AlbumQuery_>(albums[randInt(0, len(albums) - 1)]);
  }
  if (type == 2) {
    decltype(auto) songs = catalog->getSongs();
    result = std::make_shared<SongQuery_>(songs[randInt(0, len(songs) - 1)]);
  }
  return std::make_shared<QueryEvent_>(queryTimestamp, result);
}

int RequestsGenerator::randInt(int leftBound, int rightBound) {
  return std::uniform_int_distribution<int>(leftBound, rightBound)(mt);
}
