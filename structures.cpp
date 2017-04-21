//
// Created by dgorbunov on 09.04.17.
//

#include "structures.h"

void Author_::describe(std::ostream& stream) {
  stream << name;
}

std::string Author_::processedName() {
  std::string result = name;
  for (char &c : result) {
    if (c == '_') {
      c = ' ';
    }
  }
  return result;
}

void Genre_::describe(std::ostream& stream) {
  stream << name;
}

std::string Genre_::processedName() {
  std::string result = name;
  for (char &c : result) {
    if (c == '_') {
      c = ' ';
    }
  }
  return result;
}

void Album_::describe(std::ostream& stream) {
  stream << name << std::string(" (");
  author->describe(stream);
  stream << std::string(")");
}

std::string Album_::processedName() {
  std::string result = name;
  for (char &c : result) {
    if (c == '_') {
      c = ' ';
    }
  }
  return result;
}

void Song_::describe(std::ostream& stream) {
  author->describe(stream);
  stream << std::string(" - ") << name << std::string(" (album ");
  album->describe(stream);
  stream << std::string(")");
}

std::string Song_::processedName() {
  std::string result = name;
  for (char &c : result) {
    if (c == '_') {
      c = ' ';
    }
  }
  return result;
}

std::string Song_::processedDescription() {
  std::string result = name;
  for (char &c : result) {
    if (c == '_') {
      c = ' ';
    }
  }
  return result + " (" + std::to_string(duration / 60) + ":" + std::to_string(duration % 60) + ")";
}

Play_::Play_(Song song, int timestamp) : song(song), timestamp(timestamp) { }


template<typename Catalog>
std::vector<Song> Query_::findPossibleSongs(Catalog catalog) {
  std::vector<Song> result = catalog->getSongs();
  result.resize(std::remove_if(result.begin(), result.end(), [this](Song song) {
    return !songMatches(song);
  }) - result.begin());
  return result;
}

SongQuery_::SongQuery_(Song song) : song(song) {}

bool SongQuery_::songMatches(Song song) {
  return song == this->song;
}

void SongQuery_::describe(std::ostream& stream) {
  stream << std::string("song ");
  song->describe(stream);
}

AlbumQuery_::AlbumQuery_(Album album) : album(album) {}

bool AlbumQuery_::songMatches(Song song) {
  return song->album == this->album;
}

void AlbumQuery_::describe(std::ostream& stream) {
  stream << std::string("album ");
  album->describe(stream);
}

AuthorQuery_::AuthorQuery_(Author author) : author(author) {}

bool AuthorQuery_::songMatches(Song song) {
  return song->author == this->author;
}

void AuthorQuery_::describe(std::ostream& stream) {
  stream << std::string("author ");
  author->describe(stream);
}
