#ifndef SIR_MENU_H
#define SIR_MENU_H

#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include "sir_types.h"

namespace Ui {
class SIRMenu;
}

class SIRMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SIRMenu(QWidget *parent = 0);
    ~SIRMenu();

private:
    Ui::SIRMenu *ui;

    std::map<SIR_types::time, QSpinBox*> _spinBoxesTime;

    std::map<SIR_types::time, QSlider*> _slidersTime;

    std::map<SIR_types::type, QSpinBox*> _spinBoxes;

    std::map<SIR_types::type, QSlider*> _sliders;

    std::map<SIR_types::rate, QSpinBox*> _spinBoxesRates;

    std::map<SIR_types::rate, QSlider*> _slidersRates;

    void connectSpinBoxToSlider(SIR_types::types item ,int type, float min, float max, float value);

    void update_sliders();

    void update_spinBoxes();
};

#endif // SIR_MENU_H
