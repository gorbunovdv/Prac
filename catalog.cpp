#include "catalog.h"

Catalog_::Catalog_(std::string fileName) {
  std::string albumsFileName = fileName + "/albums.txt";
  std::string songsFileName = fileName + "/songs.txt";
  std::string genresFileName = fileName + "/genres.txt";
  std::string authorsFileName = fileName + "/authors.txt";
  auto genreEntities = this->readEntities<GenreEntity>(genresFileName);
  auto authorEntities = this->readEntities<AuthorEntity>(authorsFileName);
  auto albumEntities = this->readEntities<AlbumEntity>(albumsFileName);
  auto songEntities = this->readEntities<SongEntity>(songsFileName);
  this->prepareGenres(genreEntities);
  this->prepareAuthors(authorEntities);
  this->prepareAlbums(albumEntities);
  this->prepareSongs(songEntities);
  this->postprocessSongs();
}

const std::vector<Genre>& Catalog_::getGenres() {
    return genres;
}

template<typename Entity>
std::vector<Entity> Catalog_::readEntities(std::string fileName) {
  std::vector<Entity> result;
  Entity entity;
  std::ifstream stream(fileName);
  while (stream >> entity) {
    result.push_back(entity);
  }
  return result;
}

void Catalog_::prepareGenres(std::vector<GenreEntity> entities) {
  for (GenreEntity entity : entities) {
    auto genre = std::make_shared<Genre_>();
    genre->name = entity.name;
    genres.push_back(genre);
  }
}

void Catalog_::prepareAuthors(std::vector<AuthorEntity> entities) {
  for (AuthorEntity entity : entities) {
    auto author = std::make_shared<Author_>();
    author->name = entity.name;
    authors.push_back(author);
  }
}

void Catalog_::prepareAlbums(std::vector<AlbumEntity> entities) {
  for (AlbumEntity entity : entities) {
    auto album = std::make_shared<Album_>();
    album->name = entity.name;
    album->author = this->findAuthor(entity.author);
    album->genre = this->findGenre(entity.genre);
    album->author->albums.push_back(album);
    albums.push_back(album);
  }
}

void Catalog_::prepareSongs(std::vector<SongEntity> entities) {
  for (SongEntity entity : entities) {
    auto song = std::make_shared<Song_>();
    song->name = entity.name;
    song->author = this->findAuthor(entity.author);
    song->album = this->findAlbum(entity.album, entity.author);
    song->author = song->album->author;
    song->duration = entity.duration;
    song->author->songs.push_back(song);
    song->album->songs.push_back(song);
    song->genre = song->album->genre;
    songs.push_back(song);
  }
}

void Catalog_::postprocessSongs() {
  for (Song song : songs) {
    songsByGenre[song->genre].push_back(song);
  }
}

std::istream& operator>>(std::istream& stream, Catalog_::SongEntity& entity) {
  return stream >> entity.name >> entity.album >> entity.author >> entity.duration;
}

std::istream& operator>>(std::istream& stream, Catalog_::AlbumEntity& entity) {
  return stream >> entity.name >> entity.author >> entity.genre;
}

std::istream& operator>>(std::istream& stream, Catalog_::AuthorEntity& entity) {
  return stream >> entity.name;
}

std::istream& operator>>(std::istream& stream, Catalog_::GenreEntity& entity) {
  return stream >> entity.name;
}

Album Catalog_::findAlbum(std::string name, std::string author) {
  return *find_if(albums.begin(), albums.end(), [name, author](auto album) {
    return album->name == name && album->author->name == author;
  });
}

Genre Catalog_::findGenre(std::string name) {
  return *find_if(genres.begin(), genres.end(), [name](auto genre) {
    return genre->name == name;
  });
}

Author Catalog_::findAuthor(std::string name) {
  return *find_if(authors.begin(), authors.end(), [name](auto author) {
    return author->name == name;
  });
}

Song Catalog_::findSong(std::string name, std::string album, std::string author) {
    return *find_if(songs.begin(), songs.end(), [name, album, author](auto song) {
      return song->name == name && song->author->name == author && song->album->name == album;
    });
}

const std::vector<Song>& Catalog_::getSongsByGenre(Genre genre) {
  return songsByGenre[genre];
}

const std::vector<Album>& Catalog_::getAlbums() {
  return albums;
}

const std::vector<Author>& Catalog_::getAuthors() {
  return authors;
}

const std::vector<Song>& Catalog_::getSongs() {
  return songs;
}
