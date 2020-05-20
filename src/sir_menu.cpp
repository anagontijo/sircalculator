#include "sir_menu.h"
#include "ui_sir_menu.h"

SIRMenu::SIRMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SIRMenu)
{
    ui->setupUi(this);
    _spinBoxes[SIR_types::TOTAL] = spinBox_total;
    _spinBoxes[SIR_types::S] = spinBox_s;
    _spinBoxes[SIR_types::I] = spinBox_i;
}

SIRMenu::~SIRMenu()
{
    delete ui;
}

void SIRMenu::connectSpinBoxToSlider(SIR_types::types item, int type_index, float min, float max, float value){
    QSpinBox* spinbox;
    QSlider* slider;
    switch (item) {
        case SIR_types::types::type_type:
            spinbox = _spinBoxes[SIR_types::type(type_index)];
            slider = _sliders[SIR_types::type(type_index)];
            break;
        case SIR_types::types::time_type:
            spinbox = _spinBoxesTime[SIR_types::time(type_index)];
            slider = _slidersTime[SIR_types::time(type_index)];
            break;
        case SIR_types::types::rate_type:
            spinbox = _spinBoxesRates[SIR_types::rate(type_index)];
            slider = _slidersRates[SIR_types::rate(type_index)];
            break;
    }
    spinbox->setMaximum(max);
    spinbox->setMinimum(min);
    slider->setMaximum(max);
    slider->setMinimum(min);
    spinbox->blockSignals(true);
    spinbox->setValue(value);
    spinbox->blockSignals(false);
    slider->blockSignals(true);
    slider->setValue(value);
    slider->blockSignals(false);
    this->connect(spinbox, QOverload<int>::of(&QSpinBox::valueChanged), [this](){
        update_sliders();
    });
    this->connect(slider, QOverload<int>::of(&QSlider::valueChanged), [this](){
        update_spinBoxes();
    });
}

void SIRMenu::update_sliders(){
    for(auto pair: _sliders){
        pair.second->blockSignals(true);
        pair.second->setValue(_spinBoxes[pair.first]->value());
        pair.second->blockSignals(false);
    }
    for(auto pair: _slidersRates){
        pair.second->blockSignals(true);
        pair.second->setValue(_spinBoxesRates[pair.first]->value());
        pair.second->blockSignals(false);
    }
    for(auto pair: _slidersTime){
        pair.second->blockSignals(true);
        pair.second->setValue(_spinBoxesTime[pair.first]->value());
        pair.second->blockSignals(false);
    }
}

void SIRMenu::update_spinBoxes(){
    for(auto pair: _spinBoxes){
        pair.second->blockSignals(true);
        pair.second->setValue(_sliders[pair.first]->value());
        pair.second->blockSignals(false);
    }
    for(auto pair: _spinBoxesRates){
        pair.second->blockSignals(true);
        pair.second->setValue(_slidersRates[pair.first]->value());
        pair.second->blockSignals(false);
    }
    for(auto pair: _spinBoxesTime){
        pair.second->blockSignals(true);
        pair.second->setValue(_slidersTime[pair.first]->value());
        pair.second->blockSignals(false);
    }
}
