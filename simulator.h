#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <memory>
#include <set>

class RadioProgramSimulator_;
class HitParadProgramSimulator_;
class RequestsProgramSimulator_;
class Simulator_;

using RadioProgramSimulator = std::shared_ptr<RadioProgramSimulator_>;
using HitParadProgramSimulator = std::shared_ptr<HitParadProgramSimulator_>;
using RequestsProgramSimulator = std::shared_ptr<RequestsProgramSimulator_>;
using Simulator = std::shared_ptr<Simulator_>;

#include "statistics.h"
#include "radioprogram.h"
#include "requestsgenerator.h"
#include "events.h"

class RadioProgramSimulator_ {
public:
    struct EventComparator {
        bool operator () (const Event &a, const Event &b);
    };

    using Queue = std::set<Event, EventComparator>;

    RadioProgramSimulator_(std::string name, Genre genre, int duration, int timestamp, Statistics statistics);

    int simulate(Catalog catalog);

    virtual std::vector<Event> buildInitialEvents(Catalog catalog) = 0;
    virtual void process(Queue &events, Event event, Catalog catalog) = 0;

protected:
    std::string name;
    Genre genre;
    int duration;
    int timestamp;
    Statistics statistics;
};

class HitParadProgramSimulator_ : public RadioProgramSimulator_ {
public:
    HitParadProgramSimulator_(std::string name, Genre genre, int duration, int timestamp, Statistics statistics);

    std::vector<Event> buildInitialEvents(Catalog catalog);

    void process(Queue &events, Event event, Catalog catalog);

    void endOfSongEvent(Queue &events, EndOfSongEvent event, Catalog catalog);
private:
    HitParadProgram program;
};

class RequestsProgramSimulator_ : public RadioProgramSimulator_ {
public:
    RequestsProgramSimulator_(std::string name, Genre genre, int duration, int timestamp, Statistics statistics);

    std::vector<Event> buildInitialEvents(Catalog catalog);

    void process(Queue &events, Event event, Catalog catalog);

    void query(Queue &events, QueryEvent event, Catalog catalog);

    void endOfSongEvent(Queue &events, EndOfSongEvent event, Catalog catalog);

private:
    RequestsProgram program;
};

class Simulator_ {
public:
    Simulator_(std::string fileName);

    Statistics simulate(Catalog catalog);

    std::vector<std::tuple<std::string, std::string, std::string, int>> entities;
};

#endif // SIMULATOR_H
