#include "sir_interface.h"
#include <memory>
#include "../ui_sir_interface.h"

SIRInterface::SIRInterface(QWidget* parent)
    : QWidget(parent), Ui::SIRInterface() {
  setupUi(this);
  method = new SIRMethod(menu_area->getArgs());
  connect(menu_area, &SIRMenu::recalculate, this,
          &SIRInterface::prepareCalculation);
  prepareCalculation();
}

void SIRInterface::prepareCalculation() {
  auto args = menu_area->getArgs();
  method->setArgs(args);
  method->eval();
  plot_area->setSeries(method->getResults(), 0.5);
  menu_area->updateResults(method->getResultsInfo());
  plot_area->getPlot(menu_area->getTotalTime(), menu_area->getTotalPop());
}
