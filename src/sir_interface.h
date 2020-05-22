#ifndef SIR_INTERFACE_H
#define SIR_INTERFACE_H

#include <QWidget>
#include <memory>
#include "sir_menu.h"
#include "sir_method.h"
#include "sir_plot.h"
#include "ui_sir_interface.h"

class SIRInterface : public QWidget, Ui::SIRInterface {
  Q_OBJECT

 public:
  explicit SIRInterface(QWidget* parent = 0);
  ~SIRInterface() = default;

 public slots:
  void prepareCalculation();

 private:
  SIRMethod* method;
};

#endif  // SIR_INTERFACE_H
