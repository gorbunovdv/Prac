#include "royalmanager.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}


/*int main(int argc, char **argv) {
  RoyalManager manager(argv[1], argv[2]);
  for (StatisticsEvent event : manager.simulate()->getEvents()) {
    event->describe(std::cout);
  }
  return 0;
}*/