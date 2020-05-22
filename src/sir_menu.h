#ifndef SIR_MENU_H
#define SIR_MENU_H

#include <QSlider>
#include <QSpinBox>
#include <QWidget>
#include "sir_types.h"
#include "ui_sir_menu.h"

class SIRMenu : public QWidget, public Ui::SIRMenu {
  Q_OBJECT

 public:
  explicit SIRMenu(QWidget* parent = 0);
  ~SIRMenu();

  std::map<QString, float> getArgs();

  int getTotalPop();

  int getTotalTime();

  float getIntervalSize();

  void updateResults(std::map<QString, float> results);

 private:
  Ui::SIRMenu* ui;

  std::map<SIR_types::time, QSlider*> _slidersTime;

  std::map<SIR_types::type, QSpinBox*> _spinBoxes;

  std::map<SIR_types::type, QSlider*> _sliders;

  std::map<SIR_types::rate, QDoubleSpinBox*> _spinBoxesRates;

  std::map<SIR_types::rate, QSlider*> _slidersRates;

  void connectSpinBoxToSlider(SIR_types::types item,
                              int type,
                              float min,
                              float max,
                              float value);

  void updateSliders();

  void updateSpinBoxes();

  void validateSettings();

 signals:
  void recalculate();
};

#endif  // SIR_MENU_H
