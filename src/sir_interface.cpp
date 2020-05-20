#include "sir_interface.h"
#include "ui_sir_interface.h"
#include <memory>
#include <QDebug>

SIRInterface::SIRInterface(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SIRInterface)
{
    ui->setupUi(this);
}

SIRInterface::~SIRInterface()
{
    delete ui;
}

