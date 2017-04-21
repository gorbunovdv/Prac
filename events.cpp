//
// Created by dgorbunov on 09.04.17.
//

#include "events.h"

std::string process(int timestamp) {
    static char buf[100];
    sprintf(buf, "%02d:%02d:%02d", (timestamp % (24 * 3600)) / 3600, (timestamp % 3600) / 60, timestamp % 60);
    return std::string(buf);
}

void PlayEvent_::describe(std::ostream& stream) {
  stream << std::string("Event at ") << process(timestamp) << std::string(": station ") << program->getName()
         << std::string(", playing song ");
  song->describe(stream);
  stream << std::endl;
}

PlayEvent_::PlayEvent_(int timestamp, Song song, RadioProgram program) : StatisticsEvent_(
    timestamp), song(song), program(program) {}

void StatisticsQueryEvent_::describe(std::ostream& stream) {
  stream << std::string("Event at ") << process(timestamp) << std::string(": station ") << program->getName()
         << std::string(", query ");
  query->describe(stream);
  stream << std::endl;
}

StatisticsQueryEvent_::StatisticsQueryEvent_(int timestamp, Query query, RadioProgram program)
    : StatisticsEvent_(timestamp), query(query), program(program) {}

QueryEvent_::QueryEvent_(int timestamp, Query query) : Event_(timestamp), query(query) {}

Event_::Event_(int timestamp) : timestamp(timestamp) {}

EndOfSongEvent_::EndOfSongEvent_(int timestamp) : Event_(timestamp) {}

StatisticsEvent_::StatisticsEvent_(int timestamp) : timestamp(timestamp) {}
