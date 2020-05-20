#ifndef RENDER_AREA_H
#define RENDER_AREA_H

#include <QWidget>

class renderArea : public QWidget {
  Q_OBJECT
 public:
  explicit renderArea(QWidget* parent = nullptr);

 signals:
};

#endif  // RENDER_AREA_H
