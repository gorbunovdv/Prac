#ifndef STATISTICS_H
#define STATISTICS_H

#include <map>
#include <iostream>
#include <memory>

class Statistics_;

using Statistics = std::shared_ptr<Statistics_>;

#include "structures.h"
#include "types.h"
#include "events.h"

class Statistics_ {
public:
    const std::vector<Play>& getPlays();

    int getSongRequestsCount(Song song);

    void addPlay(RadioProgram program, Song song, int timestamp);

    void addQuery(RadioProgram program, Query query, int timestamp);

    void printStats();

    const std::vector<StatisticsEvent>& getEvents() {
        return events;
    }

private:
    std::vector<Play> plays;
    std::vector<StatisticsEvent> events;
    std::map<Song, int> songRequestsCount;
};

#endif // STATISTICS_H
