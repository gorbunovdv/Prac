#include "simulator.h"

bool RadioProgramSimulator_::EventComparator::operator()(const Event& a, const Event& b) {
  return std::make_pair(a->timestamp, a) < std::make_pair(b->timestamp, b);
}

RadioProgramSimulator_::RadioProgramSimulator_(std::string name, Genre genre, int duration,
    int timestamp, Statistics statistics) :
    name(name),
    genre(genre),
    duration(duration),
    timestamp(timestamp),
    statistics(statistics) {}

int RadioProgramSimulator_::simulate(Catalog catalog) {
  std::vector<Event> events = buildInitialEvents(catalog);
  Queue eventsQueue(events.begin(), events.end());
  eventsQueue.insert(std::make_shared<EndOfSongEvent_>(timestamp));
  eventsQueue.insert(std::make_shared<EndOfSongEvent_>(timestamp + duration));
  int lastTimestamp = 0;
  while (!eventsQueue.empty()) {
    Event first = *eventsQueue.begin();
    eventsQueue.erase(eventsQueue.begin());
    process(eventsQueue, first, catalog);
    lastTimestamp = first->timestamp;
  }
  return lastTimestamp;
}

HitParadProgramSimulator_::HitParadProgramSimulator_(std::string name, Genre genre, int duration,
    int timestamp, Statistics statistics) :
    RadioProgramSimulator_(name, genre, duration, timestamp, statistics),
    program(std::make_shared<HitParadProgram_>(name, genre, timestamp, duration, statistics)) {}

std::vector<Event> HitParadProgramSimulator_::buildInitialEvents(Catalog catalog) {
  return std::vector<Event>();
}

void HitParadProgramSimulator_::process(RadioProgramSimulator_::Queue& events, Event event,
    Catalog catalog) {
  endOfSongEvent(events, std::dynamic_pointer_cast<EndOfSongEvent_>(event), catalog);
}

void HitParadProgramSimulator_::endOfSongEvent(RadioProgramSimulator_::Queue& events,
    EndOfSongEvent event, Catalog catalog) {
  Song song = program->pickNextSong(catalog, event->timestamp);
  if (event->timestamp + song->duration <= timestamp + duration) {
    events.insert(std::make_shared<EndOfSongEvent_>(event->timestamp + song->duration));
    statistics->addPlay(program, song, event->timestamp);
  }
}

RequestsProgramSimulator_::RequestsProgramSimulator_(std::string name, Genre genre, int duration,
    int timestamp, Statistics statistics) :
    RadioProgramSimulator_(name, genre, duration, timestamp, statistics),
    program(std::make_shared<RequestsProgram_>(name, genre, timestamp, duration, statistics)) {}

std::vector<Event> RequestsProgramSimulator_::buildInitialEvents(Catalog catalog) {
  RequestsGenerator generator(timestamp, duration);
  return generator.generate(catalog);
}

void RequestsProgramSimulator_::process(RadioProgramSimulator_::Queue& events, Event event,
    Catalog catalog) {
  if (std::dynamic_pointer_cast<QueryEvent_>(event)) {
    query(events, std::dynamic_pointer_cast<QueryEvent_>(event), catalog);
  } else {
    endOfSongEvent(events, std::dynamic_pointer_cast<EndOfSongEvent_>(event), catalog);
  }
}

void RequestsProgramSimulator_::query(RadioProgramSimulator_::Queue& events, QueryEvent event,
    Catalog catalog) {
  std::dynamic_pointer_cast<RequestsProgram_>(program)->makeQuery(event->timestamp, event->query);
  statistics->addQuery(program, event->query, event->timestamp);
}

void RequestsProgramSimulator_::endOfSongEvent(RadioProgramSimulator_::Queue& events,
    EndOfSongEvent event, Catalog catalog) {
  Song song = program->pickNextSong(catalog, event->timestamp);
  if (event->timestamp <= timestamp + duration) {
    events.insert(std::make_shared<EndOfSongEvent_>(event->timestamp + song->duration));
    statistics->addPlay(program, song, event->timestamp);
  }
}

Statistics Simulator_::simulate(Catalog catalog) {
  auto statistics = std::make_shared<Statistics_>();
  std::string name;
  std::string type;
  std::string genre;
  int duration;
  int timestamp = 0;
  for (auto tup : entities){
    std::tie(name, type, genre, duration) = tup;
    Genre realGenre = catalog->findGenre(genre);
    if (type == REQUESTS_PROGRAM) {
      RequestsProgramSimulator radioProgramSimulator;
      radioProgramSimulator = std::make_shared<RequestsProgramSimulator_>(name, realGenre, duration,
          timestamp, statistics);
      timestamp = radioProgramSimulator->simulate(catalog);
    } else {
      HitParadProgramSimulator radioProgramSimulator;
      radioProgramSimulator = std::make_shared<HitParadProgramSimulator_>(name, realGenre, duration,
          timestamp, statistics);
      timestamp = radioProgramSimulator->simulate(catalog);
    }
  }
  return statistics;
}

Simulator_::Simulator_(std::string fileName) {
    std::ifstream stream(fileName);
    std::string name;
    std::string type;
    std::string genre;
    int duration;
    while (stream >> name >> type >> genre >> duration) {
      entities.emplace_back(name, type, genre, duration);
    }
}
