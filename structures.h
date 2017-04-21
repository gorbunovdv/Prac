#ifndef STRUCTURES
#define STRUCTURES

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

struct Author_;
struct Song_;
struct Album_;
struct Genre_;
struct Play_;
struct Query_;
struct Event_;

using Author = std::shared_ptr<Author_>;
using Song = std::shared_ptr<Song_>;
using Album = std::shared_ptr<Album_>;
using Genre = std::shared_ptr<Genre_>;
using Play = std::shared_ptr<Play_>;
using Query = std::shared_ptr<Query_>;
using Event = std::shared_ptr<Event_>;

struct Author_ {
    std::string name;
    std::vector<Song> songs;
    std::vector<Album> albums;

    void describe(std::ostream& stream);

    std::string processedName();
};

struct Genre_ {
    std::string name;

    void describe(std::ostream& stream);

    std::string processedName();
};

struct Album_ {
    Author author;
    std::string name;
    Genre genre;
    std::vector<Song> songs;

    void describe(std::ostream& stream);

    std::string processedName();
};

struct Song_ {
    Author author;
    Album album;
    std::string name;
    int duration;
    Genre genre;

    void describe(std::ostream& stream);

    std::string processedName();

    std::string processedDescription();
};

struct Play_ {
    Play_(Song song, int timestamp);

    Song song;
    int timestamp;
};

struct Query_ {
public:
    virtual bool songMatches(Song song) = 0;
    virtual void describe(std::ostream& stream) = 0;

    template<typename Catalog>
    std::vector<Song> findPossibleSongs(Catalog catalog);
};

struct SongQuery_ : public Query_ {
public:
    SongQuery_(Song song);

    bool songMatches(Song song);

    void describe(std::ostream& stream);

private:
    Song song;
};

struct AlbumQuery_ : public Query_ {
public:
    AlbumQuery_(Album album);

    bool songMatches(Song song);

    void describe(std::ostream& stream);

private:
    Album album;
};

struct AuthorQuery_ : public Query_ {
public:
    AuthorQuery_(Author author);

    bool songMatches(Song song);

    void describe(std::ostream& stream);

private:
    Author author;
};

#endif // STRUCTURES

