#ifndef TAB5CHARTPLOT_H
#define TAB5CHARTPLOT_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QDateTimeAxis>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Tab5ChartPlot;
}

class Tab5ChartPlot : public QWidget
{
    Q_OBJECT

public:
    explicit Tab5ChartPlot(QWidget *parent = nullptr);
    ~Tab5ChartPlot();

private:
    Ui::Tab5ChartPlot *ui;
    QLineSeries *pCdsLine;
    QLineSeries *pTempLine;
    QLineSeries *pHumiLine;
    QChart *chart;
    QChartView *chartView;
    QDateTimeAxis *axisX;
    QDateTime firstDate;
    QDateTime lastDate;


private slots:
    void ChartPlotClear();
    void CharPlotAdd();
    void slotTab5RecvData(QString);

#endif // TAB5CHARTPLOT_H
};
