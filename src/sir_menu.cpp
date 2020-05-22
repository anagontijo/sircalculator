#include "sir_menu.h"
#include "math.h"

SIRMenu::SIRMenu(QWidget* parent) : QWidget(parent), Ui::SIRMenu() {
  setupUi(this);
  _spinBoxes[SIR_types::total] = spinBox_total;
  _spinBoxes[SIR_types::I] = spinBox_i;
  _sliders[SIR_types::total] = slider_total;
  _sliders[SIR_types::I] = slider_i;
  for (auto pair : _spinBoxes) {
    connectSpinBoxToSlider(SIR_types::type_type, pair.first,
                           pair.second->minimum(), pair.second->maximum(),
                           pair.second->value());
  }
  _spinBoxesRates[SIR_types::i] = doubleSpinBox_i_r;
  _spinBoxesRates[SIR_types::r] = doubleSpinBox_r_r;
  _spinBoxesRates[SIR_types::v] = doubleSpinBox_v_r;
  _spinBoxesRates[SIR_types::d] = doubleSpinBox_d_r;
  _spinBoxesRates[SIR_types::n] = doubleSpinBox_not_immune;
  _slidersRates[SIR_types::i] = slider_i_r;
  _slidersRates[SIR_types::r] = slider_r_r;
  _slidersRates[SIR_types::v] = slider_v_r;
  _slidersRates[SIR_types::d] = slider_d_r;
  _slidersRates[SIR_types::n] = slider_not_immune;
  for (auto pair : _spinBoxesRates) {
    connectSpinBoxToSlider(SIR_types::rate_type, pair.first,
                           pair.second->minimum(), pair.second->maximum(),
                           pair.second->value());
  }

  slider_total_time->setMaximum(spinBox_total_time->maximum());
  slider_total_time->setMinimum(spinBox_total_time->minimum());
  slider_total_time->setValue(spinBox_total_time->value());
  connect(spinBox_total_time, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &SIRMenu::updateSliders);
  connect(slider_total_time, &QSlider::valueChanged, this,
          &SIRMenu::updateSpinBoxes);
}

SIRMenu::~SIRMenu() {}

void SIRMenu::connectSpinBoxToSlider(SIR_types::types item,
                                     int type_index,
                                     float min,
                                     float max,
                                     float value) {
  QSpinBox* spinbox = nullptr;
  QDoubleSpinBox* double_spinbox = nullptr;
  QSlider* slider;
  int i = 1;
  switch (item) {
    case SIR_types::types::type_type:
      spinbox = _spinBoxes[SIR_types::type(type_index)];
      slider = _sliders[SIR_types::type(type_index)];
      break;
    case SIR_types::types::time_type:
      spinbox = spinBox_total_time;
      slider = _slidersTime[SIR_types::time(type_index)];
      break;
    case SIR_types::types::rate_type:
      double_spinbox = _spinBoxesRates[SIR_types::rate(type_index)];
      slider = _slidersRates[SIR_types::rate(type_index)];
      if (SIR_types::rate(type_index) == SIR_types::i) {
        i = 100;
      } else if (SIR_types::rate(type_index) == SIR_types::v) {
        i = 10;
      }
      break;
  }
  if (spinbox != nullptr) {
    spinbox->setMaximum(max);
    spinbox->setMinimum(min);
    spinbox->blockSignals(true);
    spinbox->setValue(value);
    spinbox->blockSignals(false);
    this->connect(spinbox, QOverload<int>::of(&QSpinBox::valueChanged),
                  [this]() { updateSliders(); });
  }
  if (double_spinbox != nullptr) {
    double_spinbox->setMaximum(max);
    double_spinbox->setMinimum(min);
    double_spinbox->blockSignals(true);
    double_spinbox->setValue(value);
    double_spinbox->blockSignals(false);
    this->connect(double_spinbox,
                  QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                  [this]() { updateSliders(); });

    max *= 100 * i;
    min *= 100 * i;
    value *= 100 * i;
  }
  slider->setMaximum(max);
  slider->setMinimum(min);
  slider->blockSignals(true);
  slider->setValue(value);
  slider->blockSignals(false);
  this->connect(slider, QOverload<int>::of(&QSlider::valueChanged),
                [this]() { updateSpinBoxes(); });
}

void SIRMenu::updateSliders() {
  for (auto pair : _sliders) {
    pair.second->blockSignals(true);
    pair.second->setValue(_spinBoxes[pair.first]->value());
    pair.second->blockSignals(false);
  }
  for (auto pair : _slidersRates) {
    pair.second->blockSignals(true);
    int i = 1;
    if (pair.first == SIR_types::i) {
      i = 100;
    } else if (pair.first == SIR_types::v) {
      i = 10;
    }
    pair.second->setValue(_spinBoxesRates[pair.first]->value() * 100 * i);
    pair.second->blockSignals(false);
  }
  slider_total_time->blockSignals(true);

  slider_total_time->setValue(spinBox_total_time->value());

  slider_total_time->blockSignals(false);
  validateSettings();
  emit recalculate();
}

void SIRMenu::updateSpinBoxes() {
  for (auto pair : _spinBoxes) {
    pair.second->blockSignals(true);
    pair.second->setValue(_sliders[pair.first]->value());
    pair.second->blockSignals(false);
  }
  for (auto pair : _spinBoxesRates) {
    int i = 1;
    if (pair.first == SIR_types::i) {
      i = 100;
    } else if (pair.first == SIR_types::v) {
      i = 10;
    }
    pair.second->blockSignals(true);
    pair.second->setValue(_slidersRates[pair.first]->value() / (100.0 * i));
    pair.second->blockSignals(false);
  }
  spinBox_total_time->blockSignals(true);

  spinBox_total_time->setValue(slider_total_time->value());

  spinBox_total_time->blockSignals(false);
  validateSettings();
  emit recalculate();
}

void SIRMenu::validateSettings() {
  if (doubleSpinBox_d_r->value() + doubleSpinBox_r_r->value() +
          doubleSpinBox_not_immune->value() >
      1) {
    doubleSpinBox_d_r->blockSignals(true);
    slider_d_r->blockSignals(true);
    doubleSpinBox_d_r->setValue(1 - doubleSpinBox_r_r->value());
    slider_d_r->setValue(1 - doubleSpinBox_r_r->value());
    doubleSpinBox_d_r->blockSignals(false);
    slider_d_r->blockSignals(false);
    if (doubleSpinBox_r_r->value() + doubleSpinBox_not_immune->value() > 1) {
      doubleSpinBox_not_immune->blockSignals(true);
      slider_not_immune->blockSignals(true);
      doubleSpinBox_not_immune->setValue(1 - doubleSpinBox_r_r->value());
      slider_not_immune->setValue(1 - doubleSpinBox_r_r->value());
      doubleSpinBox_not_immune->blockSignals(false);
      slider_not_immune->blockSignals(false);
    }
  }
  if (spinBox_i->value() > spinBox_total->value()) {
    spinBox_i->blockSignals(true);
    slider_i->blockSignals(true);
    slider_i->setValue(spinBox_total->value());
    spinBox_i->setValue(spinBox_total->value());
    spinBox_i->blockSignals(false);
    slider_i->blockSignals(false);
  }
  spinBox_i->setMaximum(spinBox_total->value());
  slider_i->setMaximum(spinBox_total->value());
  if (doubleSpinBox_v_r->value() + doubleSpinBox_i_r->value() > 1) {
    doubleSpinBox_v_r->blockSignals(true);
    slider_v_r->blockSignals(true);
    doubleSpinBox_v_r->setValue(1 - doubleSpinBox_i_r->value());
    slider_v_r->setValue(1 - doubleSpinBox_i_r->value());
    doubleSpinBox_v_r->blockSignals(false);
    slider_v_r->blockSignals(false);
  }
}

std::map<QString, float> SIRMenu::getArgs() {
  std::map<QString, float> args;
  for (auto pair : _spinBoxes) {
    args[SIR_types::toString(pair.first)] = pair.second->value();
  }
  for (auto pair : _spinBoxesRates) {
    args[SIR_types::toString(pair.first)] = pair.second->value();
  }
  args[SIR_types::toString(SIR_types::totalTime)] = spinBox_total_time->value();

  return args;
}

int SIRMenu::getTotalPop() {
  return spinBox_total->value();
}

int SIRMenu::getTotalTime() {
  return spinBox_total_time->value();
}

void SIRMenu::updateResults(std::map<QString, float> results) {
  QString max_infected;
  max_infected.setNum(int(results[QString("Max I")]));
  float time_duration = results[QString("Duration")];
  QString alive_after;
  alive_after.setNum(int(results[QString("Alive after")]));
  QString not_infected;
  not_infected.setNum(int(results[QString("Not infected")]));
  label_max_I->setText(QString(max_infected));
  if (time_duration == -1) {
    label_duration->setText(QString("Not defined."));
    label_alive_after->setText(QString("Not defined."));
    label_susceptible_and_vaccinated_after->setText(QString("Not defined."));
  } else {
    QString int_time_duration;
    int_time_duration.setNum(int(time_duration));
    if (int(time_duration) != time_duration) {
      label_duration->setText(int_time_duration +
                              QString(" days and 12 hours"));
    } else {
      label_duration->setText(int_time_duration + QString(" days"));
    }
    label_alive_after->setText(alive_after);
    label_susceptible_and_vaccinated_after->setText(not_infected);
  }
}
