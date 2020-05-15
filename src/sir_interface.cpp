#include "sir_interface.h"
#include "ui_sir_interface.h"

SIRInterface::SIRInterface(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::SIRInterface) {
  ui->setupUi(this);
}

SIRInterface::~SIRInterface() {
  delete ui;
}
