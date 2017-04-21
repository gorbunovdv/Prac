#ifndef ROYALMANAGER_H
#define ROYALMANAGER_H

#include "simulator.h"

class RoyalManager {
public:
    RoyalManager(std::string catalogPath, std::string programsPath);

    Statistics simulate();

private:
    std::string catalogPath;
    std::string programsPath;
};

#endif // ROYALMANAGER_H
