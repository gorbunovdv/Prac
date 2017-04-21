#ifndef REQUESTSGENERATOR_H
#define REQUESTSGENERATOR_H

#include "types.h"
#include "structures.h"
#include "catalog.h"
#include "events.h"
#include <random>

class RequestsGenerator {
public:
    RequestsGenerator(int timestamp, int duration) : mt(timestamp), timestamp(timestamp), duration(duration) {}

    std::vector<Event> generate(Catalog catalog);

private:
    Event generate_query(Catalog catalog);

    int randInt(int leftBound, int rightBound);

    std::mt19937 mt;
    int timestamp;
    int duration;
};

#endif // REQUESTSGENERATOR_H
