#include "sir_plot.h"
#include "ui_sir_plot.h"
#include <QDebug>

SIRPlot::SIRPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SIRPlot)
{
    ui->setupUi(this);
    for(int i = 0; i < SIR_types::numTypes; i++){
        qDebug() << i;
        qDebug() << SIR_types::toString(SIR_types::type(i));
        series[SIR_types::type(i)] = new QtCharts::QSplineSeries();
        series[SIR_types::type(i)]->setName(SIR_types::toString(SIR_types::type(i)));
    }
    initializePlot(3000, 300);
}

SIRPlot::~SIRPlot()
{
    delete ui;
}

void SIRPlot::initializePlot(int max_population, int max_time){
    chart->setTitle("Results plot");
    for(int i = 0; i < SIR_types::numTypes; i++){
        chart->addSeries(series[SIR_types::type(i)]);
    }
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, max_population);
    chart->axes(Qt::Vertical).first()->setRange(0, max_time);
    chart_view->setRenderHint(QPainter::Antialiasing);
    layout()->addWidget(chart_view);
}

void SIRPlot::setSeries(SIR_types::type type, QVector<double> data){
    series[type] = new QtCharts::QSplineSeries();
    series[type]->setName(SIR_types::toString(type));
    for(int i = 0; i < data.size(); i++){
        series[type]->append(i, data[i]);
    }
}
