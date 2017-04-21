#ifndef RADIOPROGRAM_H
#define RADIOPROGRAM_H

#include <memory>
#include <map>

class RadioProgram_;
class RequestsProgram_;
class HitParadProgram_;

using RadioProgram = std::shared_ptr<RadioProgram_>;
using RequestsProgram = std::shared_ptr<RequestsProgram_>;
using HitParadProgram = std::shared_ptr<HitParadProgram_>;

#include "structures.h"
#include "statistics.h"
#include "catalog.h"

const std::string REQUESTS_PROGRAM = "REQUESTS_PROGRAM";
const std::string HITPARAD_PROGRAM = "HITPARAD_PROGRAM";

class RadioProgram_ {
public:
    RadioProgram_(std::string name, Genre genre, int start, int duration, Statistics statistics);

    Song pickNextSong(Catalog catalog, int timestamp);

    std::string getName();

protected:
    virtual std::map<Song, double> getQualities(Catalog catalog, int timestamp) = 0;
    virtual void postprocessSong(Song song, int timestamp) = 0;

    std::string name;
    Genre genre;
    int start;
    int duration;
    Statistics statistics;
};

class RequestsProgram_ : public RadioProgram_ {
public:
    RequestsProgram_(std::string name, Genre genre, int start, int duration, Statistics statistics);

    void makeQuery(int timestamp, Query query) {
        queries.push_back(query);
    }

private:
    std::map<Song, double> getQualities(Catalog catalog, int timestamp);

    double evaluateQuality(int timestamp, Song song);

    void postprocessSong(Song song, int timestamp);

    std::vector<Query> queries;
};

class HitParadProgram_ : public RadioProgram_ {
public:
    HitParadProgram_(std::string name, Genre genre, int start, int duration, Statistics statistics);

private:
    std::map<Song, double> getQualities(Catalog catalog, int timestamp);

    void postprocessSong(Song song, int timestamp) { }

    double evaluateQuality(int timestamp, Song song);

    void postprocessSong() { }
};

#endif // RADIOPROGRAM_H
