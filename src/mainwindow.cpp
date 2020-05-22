#include "mainwindow.h"
#include "../ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), Ui::MainWindow() {
  setupUi(this);
  setWindowIcon(QIcon(":/icons/SIR_icon.ico"));
  setWindowTitle(QString("SIR Calculator"));
  connect(comboBox_page, QOverload<int>::of(&QComboBox::currentIndexChanged),
          stack, &QStackedWidget::setCurrentIndex);
}
