#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

#include <QRandomGenerator>
#include <QtMath>


#include <QDateTimeAxis>
#include <QValueAxis>
#include <QValueAxis>

#include "NumericalCalculation/interpolation.h"
#include "Plots/chart.h"
#include "Plots/chartview.h"
#include "Plots/lightmarkerswidget.h"

#include "Workers/responder.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

protected:
//  void resizeEvent(QResizeEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;




 private slots:
  void loadFile();
  void calculateInterpolation();
  void handleTimeout();

 private:
  Ui::MainWindow* ui;
  QString data_file_full_path;
  Interpolation spline;
  void Plot();

  // Plot

  // путь к файлу  с координатами с точками ломанной
  //QString pathFileData;
  //QString pathFileDataInterpolationOutput;

  QGraphicsSimpleTextItem *m_coordX = nullptr;
  QGraphicsSimpleTextItem *m_coordY = nullptr;

  // draw Linerars рисование гоафиков и графической сцены
  Chart *chart ;
  ChartView *chartView;
  QLineSeries *series;
  QLineSeries *seriesIn;

  LightMarkersWidget *lmw;
  QTimer *m_timer;

  qreal x=0,y=0,h=0.05;

  // experimental function for random value

  qreal theta(qreal x);
  qreal f2(qreal x);
  qreal f(qreal x);

  const double STEP = 1e-2;
  // выделение узлов квадратами
  QImage rectangle(qreal imageSize, const QColor &color);

  //Workers for interpolation -------------

  Responder *resp;



};
#endif  // MAINWINDOW_H
