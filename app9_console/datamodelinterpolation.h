#ifndef DATAMODELINTERPOLATION_H
#define DATAMODELINTERPOLATION_H

#include <QVector>
#include "NumericalCalculation/polynomial.h"
#include "NumericalCalculation/interpolation.h"

//  -----  Участок интерполяционной кривой

struct DataModelInterpolation
{
    std::vector<QPointF> points;    
    int number; // номер участка массива точек
};

#endif // DATAMODELINTERPOLATION_H
