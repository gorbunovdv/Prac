#ifndef SIMULATIONSTATISTICSFORM_H
#define SIMULATIONSTATISTICSFORM_H

#include "catalog.h"
#include "statistics.h"
#include <QDialog>

namespace Ui {
class SimulationStatisticsForm;
}

class SimulationStatisticsForm : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationStatisticsForm(QWidget *parent = 0);
    ~SimulationStatisticsForm();

    void acceptStatistics(const Catalog &catalog, const Statistics &statistics);

private:
    Ui::SimulationStatisticsForm *ui;
    Catalog catalog;
    Statistics statistics;
};

#endif // SIMULATIONSTATISTICSFORM_H
