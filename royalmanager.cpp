#include "royalmanager.h"

Statistics RoyalManager::simulate() {
  auto catalog = std::make_shared<Catalog_>(catalogPath);
  auto simulator = std::make_shared<Simulator_>(programsPath);
  return simulator->simulate(catalog);
}

RoyalManager::RoyalManager(std::string catalogPath, std::string programsPath) : catalogPath(
    catalogPath), programsPath(programsPath) {}
