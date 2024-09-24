// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef LIGHTMARKERSWIDGET_H
#define LIGHTMARKERSWIDGET_H

#include "contentwidget.h"

#include <QColor>
#include <QImage>
#include <QtCharts>

#include <vector>

#include "NumericalCalculation/interpolation.h"

const double STEP2 = 1e-2;


QT_FORWARD_DECLARE_CLASS(QChartView)

class LightMarkersWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit LightMarkersWidget(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *) override;

private:
    enum class PointType {
        RedRectangle,
        GreenTriangle,
        OrangeCircle
    };

    enum class SelectedPointType {
        BlueTriangle,
        YellowRectangle,
        LavenderCircle
    };

    enum class LineColor {
        Blue,
        Black,
        Mint
    };

    QImage rectangle(qreal imageSize, const QColor &color);
    QImage circle(qreal imageSize, const QColor &color);
    QImage blueTriangle(qreal imageSize);
    QImage greenTriangle(qreal imageSize);
    QImage getPointRepresentation(PointType pointType, int imageSize);
    QImage getSelectedPointRepresentation(SelectedPointType pointType, int imageSize);
    QColor makeLineColor(LineColor lineColor);

    QWidget *m_mainWidget = nullptr;

    // Plot

    QString pathFileData;


    // add function

    QLineSeries *series;

    void on_loadFileButton_clicked();
    void on_calculateInterpolationButton_clicked();

    QString data_file_full_path;
    Interpolation spline;
    void SetupGraph();
    void PlotGraph(std::vector<Polynomial> polynomes);
    void PlotInputPoints(std::vector<QPointF> points);
    void Plot();

    QValueAxis *m_axisX = nullptr;
    QValueAxis *m_axisY = nullptr;
    QVector<double> xs, ys;

    qreal x,y,h;

};

#endif
