#include "statistics.h"

void Statistics_::printStats() {
  for (StatisticsEvent event : events) {
    event->describe(std::cout);
  }
}

const std::vector<Play>& Statistics_::getPlays() {
  return plays;
}

int Statistics_::getSongRequestsCount(Song song) {
  return songRequestsCount[song];
}

void Statistics_::addPlay(RadioProgram program, Song song, int timestamp) {
  plays.push_back(std::make_shared<Play_>(song, timestamp));
  events.push_back(std::dynamic_pointer_cast<StatisticsEvent_>(
      std::make_shared<PlayEvent_>(timestamp, song, program)));
}

void Statistics_::addQuery(RadioProgram program, Query query, int timestamp) {
  events.push_back(std::dynamic_pointer_cast<StatisticsEvent_>(
      std::make_shared<StatisticsQueryEvent_>(timestamp, query, program)));
}
