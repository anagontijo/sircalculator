#ifndef SIR_PLOT_H
#define SIR_PLOT_H

#include <QWidget>
#include <QChart>
#include <QSplineSeries>
#include <QChartView>
#include "sir_method.h"
#include "sir_types.h"

namespace Ui {
class SIRPlot;
}

class SIRPlot : public QWidget
{
    Q_OBJECT

public:
    explicit SIRPlot(QWidget *parent = 0);
    ~SIRPlot();
    void initializePlot(int max_population, int max_time);
    void resetSeries(SIR_types::type type);
    void setSeries(SIR_types::type type, QVector<double> data);
private:
    Ui::SIRPlot *ui;
    std::map<SIR_types::type, QtCharts::QSplineSeries*> series;
    QtCharts::QChart* chart = new QtCharts::QChart();
    QtCharts::QChartView* chart_view = new QtCharts::QChartView(chart);
};

#endif // SIR_PLOT_H
