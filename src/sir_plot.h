#ifndef SIR_PLOT_H
#define SIR_PLOT_H

#include <QChart>
#include <QChartView>
#include <QSplineSeries>
#include <QWidget>
#include "sir_method.h"
#include "sir_types.h"
#include "ui_sir_plot.h"

class SIRPlot : public QWidget, public Ui::SIRPlot {
  Q_OBJECT

 public:
  explicit SIRPlot(QWidget* parent = 0);
  ~SIRPlot() = default;
  void getPlot(int max_time, int max_population);
  void resetSeries(SIR_types::type type);
  void setSeries(SIR_types::type type,
                 QVector<float> data,
                 float interval_size);
  void setSeries(std::map<SIR_types::type, QVector<float>> data,
                 float interval_size);

 private:
  std::map<SIR_types::type, QtCharts::QSplineSeries*> series;
  QtCharts::QChart* chart = new QtCharts::QChart();
  QtCharts::QChartView* chart_view = new QtCharts::QChartView(chart);
};

#endif  // SIR_PLOT_H
