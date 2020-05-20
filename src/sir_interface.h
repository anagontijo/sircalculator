#ifndef SIR_INTERFACE_H
#define SIR_INTERFACE_H

#include <QWidget>
#include "sir_menu.h"
#include "sir_plot.h"
#include "sir_method.h"
#include <memory>

namespace Ui {
class SIRInterface;
}

class SIRInterface : public QWidget
{
    Q_OBJECT

public:
    explicit SIRInterface(QWidget* parent = 0);
    ~SIRInterface();

private:

    Ui::SIRInterface *ui;
};

#endif // SIR_INTERFACE_H
