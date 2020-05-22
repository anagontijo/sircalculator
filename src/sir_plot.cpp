#include "sir_plot.h"
#include <QValueAxis>
#include "ui_sir_plot.h"

SIRPlot::SIRPlot(QWidget* parent) : QWidget(parent), Ui::SIRPlot() {
  setupUi(this);
  for (int i = 0; i < SIR_types::numTypes; i++) {
    series[SIR_types::type(i)] = new QtCharts::QSplineSeries();
    series[SIR_types::type(i)]->setName(
        SIR_types::toString(SIR_types::type(i)));
  }
  getPlot(3000, 300);
  chart_view->setRenderHint(QPainter::Antialiasing);
  layout()->addWidget(chart_view);
}

void SIRPlot::getPlot(int max_time, int max_population) {
  chart = new QtCharts::QChart();
  for (int i = 0; i < SIR_types::numTypes; i++) {
    chart->addSeries(series[SIR_types::type(i)]);
  }
  chart->createDefaultAxes();
  chart->axes(Qt::Horizontal).first()->setRange(0, max_time);
  chart->axes(Qt::Vertical).first()->setRange(0, max_population);
  chart_view->setChart(chart);
}

void SIRPlot::setSeries(SIR_types::type type,
                        QVector<float> data,
                        float interval_size) {
  series[type] = new QtCharts::QSplineSeries();
  series[type]->setName(SIR_types::toString(type));
  for (int i = 0; i < data.size(); i++) {
    series[type]->append(i * interval_size, data[i]);
  }
}

void SIRPlot::setSeries(std::map<SIR_types::type, QVector<float>> data,
                        float interval_size) {
  for (auto pair : data) {
    setSeries(pair.first, pair.second, interval_size);
  }
}
