// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "lightmarkerswidget.h"

#include <QBrush>
#include <QChart>
#include <QChartView>
#include <QCheckBox>
#include <QComboBox>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QPainter>
#include <QPainterPath>
#include <QSplineSeries>
#include <QtCharts>

#include <iostream>
#include <fstream>

using namespace QtCharts;


LightMarkersWidget::LightMarkersWidget(QWidget *parent)
    : ContentWidget(parent)
{
    pathFileData = QApplication::applicationDirPath()+"/"+ "points.txt";
    x=0;
    y=0;
    h=0.5;

    {
        std::ofstream out;
        out.open(pathFileData.toStdString());
        out.close();
    }
    {
    std::ofstream out;
    out.open(pathFileData.toStdString(),std::ios::app);
    //out.open(fn);
    if(out.is_open())
    {
        for(int i=0; i<20;i++){
            out<<x<<" "<<y<<"\n";
            x+=h;
            y=f(x);
        }
    }
    out.close();
    }


    //![1]
    constexpr qreal marker_size = 20.;

    series = new QSplineSeries;
//    series->append({QPointF(0., 0.),
//                    QPointF(0.5, 2.27),
//                    QPointF(1.5, 2.2),
//                    QPointF(3.3, 1.7),
//                    QPointF(4.23, 3.1),
//                    QPointF(5.3, 2.3),
//                    QPointF(6.47, 4.1)
//    });

    on_loadFileButton_clicked();
    on_calculateInterpolationButton_clicked();

    //series->setMarkerSize(marker_size);
    //series->setLightMarker(rectangle(marker_size, Qt::red));
    //series->setSelectedLightMarker(blueTriangle(marker_size));


    m_axisX = new QValueAxis;
    m_axisY = new QValueAxis;

    auto chart = new QChart;
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->legend()->setVisible(false);
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setTitle("Select points with mouse click");

//    chart->addAxis(m_axisX,Qt::AlignBottom);
//    chart->addAxis(m_axisY,Qt::AlignLeft);

//    series->attachAxis(m_axisX);
//    series->attachAxis(m_axisY);
//    m_axisX->setTickCount(5);

//    auto x_minmax = std::minmax_element(xs.begin(), xs.end());
//    auto y_minmax = std::minmax_element(ys.begin(), ys.end());

//    m_axisX->setRange(*x_minmax.first - 1, *x_minmax.second + 1);
//    m_axisY->setRange(*y_minmax.first - 1, *y_minmax.second + 1);

    auto chartView = new QtCharts::QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    auto controlWidget = new QWidget(this);
    auto controlLayout = new QGridLayout(controlWidget);
    //![2]

    //![3]
    auto charPointCombobox = new QComboBox(controlWidget);
    auto charPointSelectedCombobox = new QComboBox(controlWidget);
    auto lineColorCombobox = new QComboBox(controlWidget);
    auto showUnselectedPointsCheckbox = new QCheckBox(controlWidget);
    //![3]

    //![4]
//    auto charPoint = new QLabel(tr("Char point: "), controlWidget);
//    charPointCombobox->addItems({tr("Red rectangle"),
//                                 tr("Green triangle"),
//                                 tr("Orange circle")
//    });
//    QObject::connect(charPointCombobox, &QComboBox::currentIndexChanged, series, [=](const int index) {
//        if (showUnselectedPointsCheckbox->isChecked())
//            series->setLightMarker(getPointRepresentation(PointType(index), marker_size));
//    });
//    //![4]

//    //![5]
//    auto charPointSelected = new QLabel(tr("Char point selected: "), controlWidget);
//    charPointSelectedCombobox->addItems({tr("Blue triangle"),
//                                         tr("Yellow rectangle"),
//                                         tr("Lavender circle")
//    });
//    QObject::connect(charPointSelectedCombobox, &QComboBox::currentIndexChanged, series, [=](const int index) {
//        series->setSelectedLightMarker(getSelectedPointRepresentation(SelectedPointType(index), marker_size));
//    });

//    auto lineColorLabel = new QLabel(tr("Line color: "), controlWidget);
//    lineColorCombobox->addItems({tr("Blue"),
//                                 tr("Black"),
//                                 tr("Mint")
//    });
//    QObject::connect(lineColorCombobox, &QComboBox::currentIndexChanged, series, [=](const int index) {
//        series->setColor(makeLineColor(LineColor(index)));
//    });
    //![5]

    //![6]
//    auto showUnselectedPointsLabel = new QLabel(tr("Display unselected points: "), controlWidget);
//    showUnselectedPointsCheckbox->setChecked(true);
//    QObject::connect(showUnselectedPointsCheckbox, &QCheckBox::stateChanged, series, [=](const int state) {
//        if (state)
//            series->setLightMarker(getPointRepresentation(PointType(charPointCombobox->currentIndex()), marker_size));
//        else
//            series->setLightMarker(QImage());
//    });
    //![6]

    //![7]
//    controlLayout->addWidget(charPoint, 0, 0);
//    controlLayout->addWidget(charPointCombobox, 0, 1);

//    controlLayout->addWidget(charPointSelected, 1, 0);
//    controlLayout->addWidget(charPointSelectedCombobox, 1, 1);

//    controlLayout->addWidget(lineColorLabel, 2, 0);
//    controlLayout->addWidget(lineColorCombobox, 2, 1);

//    controlLayout->addWidget(showUnselectedPointsLabel, 3, 0);
//    controlLayout->addWidget(showUnselectedPointsCheckbox, 3, 1, 1, 2);

    m_mainWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(m_mainWidget);
    mainLayout->addWidget(chartView);
    mainLayout->addWidget(controlWidget);
    //![7]
}

void LightMarkersWidget::resizeEvent(QResizeEvent *)
{
    m_mainWidget->resize(size());
}

QImage LightMarkersWidget::rectangle(qreal imageSize, const QColor &color)
{
    QImage image(imageSize, imageSize, QImage::Format_RGB32);
    QPainter painter;
    painter.begin(&image);
    painter.fillRect(0, 0, imageSize, imageSize, color);
    painter.end();
    return image;
}

QImage LightMarkersWidget::circle(qreal imageSize, const QColor &color)
{
    QImage image(imageSize, imageSize, QImage::Format_ARGB32);
    image.fill(QColor(0, 0, 0, 0));
    QPainter paint;
    paint.begin(&image);
    paint.setBrush(color);
    QPen pen = paint.pen();
    pen.setWidth(0);
    paint.setPen(pen);
    paint.drawEllipse(0, 0, imageSize * 0.5, imageSize * 0.5);
    paint.end();
    return image;
}

QImage LightMarkersWidget::blueTriangle(qreal imageSize)
{
    return QImage(":/blue_triangle").scaled(imageSize, imageSize);
}

QImage LightMarkersWidget::greenTriangle(qreal imageSize)
{
    return QImage(":/green_triangle").scaled(imageSize, imageSize);
}

QImage LightMarkersWidget::getPointRepresentation(PointType pointType, int imageSize)
{
    switch (pointType) {
    case PointType::RedRectangle:
        return rectangle(imageSize, Qt::red);
    case PointType::GreenTriangle:
        return greenTriangle(imageSize);
    case PointType::OrangeCircle:
        return circle(imageSize, QColor(255, 127, 80));
    default:
        return rectangle(imageSize, Qt::red);
    }
}

QImage LightMarkersWidget::getSelectedPointRepresentation(SelectedPointType pointType, int imageSize)
{
    switch (pointType) {
    case SelectedPointType::BlueTriangle:
        return blueTriangle(imageSize);
    case SelectedPointType::YellowRectangle:
        return rectangle(imageSize, Qt::yellow);
    case SelectedPointType::LavenderCircle:
        return circle(imageSize, QColor(147, 112, 219));
    default:
        return blueTriangle(imageSize);
    }
}

QColor LightMarkersWidget::makeLineColor(LineColor lineColor)
{
    switch (lineColor) {
    case LineColor::Blue:
        return QColor(65, 105, 225);
    case LineColor::Black:
        return QColor(0, 0, 0);
    case LineColor::Mint:
        return QColor(70, 203, 155);
    default:
        return QColor(0, 0, 0);
    }
}

// add function

void LightMarkersWidget::SetupGraph() {
    // for splines
    //  this->ui->customPlot->addGraph();
    //  // for points
    //  this->ui->customPlot->addGraph();
    //  this->ui->customPlot->graph(1)->setPen(QPen(QColor(255, 0, 0)));
    //  this->ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    //  this->ui->customPlot->graph(1)->setScatterStyle(
    //      QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    //  // labels
    //  this->ui->customPlot->xAxis->setLabel("x");
    //  this->ui->customPlot->yAxis->setLabel("y");
}

void LightMarkersWidget::PlotGraph(std::vector<Polynomial> polynomes) {
    return;
    xs.clear(); ys.clear();

    for (Polynomial p : polynomes) {
        for (double x = p.from; x <= p.to; x += STEP2) {
            xs.push_back(x);
            ys.push_back(p.GetValue(x));
        }
    }

    //this->ui->customPlot->graph(0)->setData(xs, ys);

    // pairs to set boundaries
    auto x_minmax = std::minmax_element(xs.begin(), xs.end());
    auto y_minmax = std::minmax_element(ys.begin(), ys.end());

    //  this->ui->customPlot->xAxis->setRange(*x_minmax.first - 1,
    //                                        *x_minmax.second + 1);
    //  this->ui->customPlot->yAxis->setRange(*y_minmax.first - 1,
    //                                        *y_minmax.second + 1);
}

void LightMarkersWidget::PlotInputPoints(std::vector<QPointF> points) {
    //QVector<double> xs, ys;
    for (QPointF p : points) {
        *series <<p;
        //
    }

    //this->ui->customPlot->graph(1)->setData(xs, ys);
}

void LightMarkersWidget::Plot() {
    //SetupGraph();
    PlotGraph(this->spline.Interpolate());
    PlotInputPoints(this->spline.points);
    //this->ui->customPlot->replot();
}

void LightMarkersWidget::on_loadFileButton_clicked() {
    QFileInfo full_path(pathFileData); //QFileDialog::getOpenFileName(this, tr("Open file with points")));
    QString file_name = pathFileData; //full_path.fileName();
    //this->ui->fileLoadedStatusLabel->setText("Loaded " + file_name);
    this->data_file_full_path = full_path.filePath();
}

void LightMarkersWidget::on_calculateInterpolationButton_clicked() {
    try {
        this->spline = Interpolation::FromFile(this->data_file_full_path);
        Plot();
    } catch (std::exception& e) {
        QMessageBox msg;
        msg.setText(e.what());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}
