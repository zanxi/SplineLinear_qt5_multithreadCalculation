#ifndef SPLINE_H
#define SPLINE_H

#include <QFileInfo>
#include <QPoint>
#include <vector>
#include <QVector>

#include "polynomial.h"

//  -----    класс получения кубического сплайна

class Interpolation {
 private:
  void check_points() const;  // raises exception if something is wrong
 public:
  Interpolation(){};
  static Interpolation FromFile(QString);
  static Interpolation GetInputPoints(std::vector<QPointF> points);

  std::vector<QPointF> points;
  std::vector<Polynomial> Interpolate();
};

#endif  // SPLINE_H
