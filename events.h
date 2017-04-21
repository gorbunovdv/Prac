#ifndef EVENTS
#define EVENTS

#include <memory>
#include <iostream>

struct Event_;
struct QueryEvent_;
struct EndOfSongEvent_;
struct StatisticsQueryEvent_;
struct PlayEvent_;
struct StatisticsEvent_;

using Event = std::shared_ptr<Event_>;
using QueryEvent = std::shared_ptr<QueryEvent_>;
using EndOfSongEvent = std::shared_ptr<EndOfSongEvent_>;
using StatisticsQueryEvent = std::shared_ptr<StatisticsQueryEvent_>;
using PlayEvent = std::shared_ptr<PlayEvent_>;
using StatisticsEvent = std::shared_ptr<StatisticsEvent_>;

#include "radioprogram.h"

struct Event_ {
    Event_(int timestamp);

    int timestamp;

    virtual void polymorphic() = 0;
};

struct QueryEvent_ : public Event_ {
    QueryEvent_(int timestamp, Query query);

    Query query;

    void polymorphic() { }
};

struct EndOfSongEvent_ : public Event_ {
    EndOfSongEvent_(int timestamp);

    void polymorphic() { }
};

struct StatisticsEvent_ {
public:
    StatisticsEvent_(int timestamp);

    virtual void describe(std::ostream& stream) = 0;

    int timestamp;
};

struct PlayEvent_ : public StatisticsEvent_ {
public:
    PlayEvent_(int timestamp, Song song, RadioProgram program);

    void describe(std::ostream& stream);

protected:
    Song song;
    RadioProgram program;
};

struct StatisticsQueryEvent_ : public StatisticsEvent_ {
public:
    StatisticsQueryEvent_(int timestamp, Query query, RadioProgram program);

    void describe(std::ostream& stream);

protected:
    Query query;
    RadioProgram program;
};

#endif // EVENTS
