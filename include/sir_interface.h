#ifndef SIRINTERFACE_H
#define SIRINTERFACE_H

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WGridLayout>
#include <Wt/WBorderLayout>
#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WDataSeries>
#include <Wt/WSlider>



using namespace std;
using namespace Wt;

struct SIRInterface : WApplication {
  App(const WEnvironment& env) : WApplication(env) {

    int population;

    auto full_page = root()->setLayout(make_unique<WBorderLayout>());

    auto plot = full_page->addWidget(make_unique<Chart::WCartesianChart>(), LayoutPosition::West);

    auto title = full_page->addWidget(make_unique<WText>("SIR Calculator"), LayoutPosition::North);

    auto settings_area_full = root().addWidget(make_unique<WContainerWidget>, LayoutPosition::East);

    auto settings_area = settings_area_full->setLayout(make_unique<WGridLayout>());

    auto title_S = settings_area->addWidget(make_unique<WText>("Initial S : "), 0, 0);

    auto value_S = settings_area->addWidget(make_unique<WText>(), 0, 1);

    auto slider_S = settings_area->addWidget(make_unique<WSlider>(), 0, 2);


    slider_S->setTickPosition(Wt::WSlider::TickPosition::TicksAbove);
    slider_S->setTickInterval(10);
    slider_S->setMinimum(0);
    slider_S->setMaximum(population);
    slider_S->setValue(0);

    auto editText = [=](WText text, WText edit){edit.setText(text)};

    slider_S->valueChanged().connect(editText(slider_S->valueText(), value_S));

    myEdit->textInput().connect(editFunc);
  }
};

class SIRInterface : public  {
  Q_OBJECT

 public:
  SIRInterface(QWidget* parent = nullptr);
  ~SIRInterface();

 private:
  Ui::SIRInterface* ui;
};
#endif  // SIRINTERFACE_H
