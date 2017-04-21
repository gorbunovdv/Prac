#ifndef CATALOG_H
#define CATALOG_H

#include <fstream>
#include <algorithm>
#include <map>
#include <iostream>
#include <cassert>
#include <memory>

class Catalog_;

using Catalog = std::shared_ptr<Catalog_>;

#include "structures.h"

class Catalog_
{
public:
    Catalog_(std::string fileName);

    const std::vector<Song>& getSongs();

    const std::vector<Author>& getAuthors();

    const std::vector<Album>& getAlbums();

    const std::vector<Genre>& getGenres();

    const std::vector<Song>& getSongsByGenre(Genre genre);

    Author findAuthor(std::string name);

    Genre findGenre(std::string name);

    Album findAlbum(std::string name, std::string author);

    Song findSong(std::string name, std::string album, std::string author);

    struct GenreEntity {
      std::string name;

      friend std::istream& operator >> (std::istream &stream, GenreEntity &entity);
    };

    struct AuthorEntity {
      std::string name;

      friend std::istream& operator >> (std::istream &stream, AuthorEntity &entity);
    };

    struct AlbumEntity {
      std::string name;
      std::string author;
      std::string genre;

      friend std::istream& operator >> (std::istream &stream, AlbumEntity &entity);
    };

    struct SongEntity {
      std::string name;
      std::string album;
      std::string author;
      int duration;

      friend std::istream& operator >> (std::istream &stream, SongEntity &entity);
    };

private:
    void postprocessSongs();

    template<typename Entity>
    std::vector<Entity> readEntities(std::string fileName);

    void prepareGenres(std::vector<GenreEntity> entities);

    void prepareAuthors(std::vector<AuthorEntity> entities);

    void prepareAlbums(std::vector<AlbumEntity> entities);

    void prepareSongs(std::vector<SongEntity> entities);

    std::vector<Author> authors;
    std::vector<Song> songs;
    std::vector<Genre> genres;
    std::vector<Album> albums;
    std::map<Genre, std::vector<Song>> songsByGenre;
};

#endif // CATALOG_H
