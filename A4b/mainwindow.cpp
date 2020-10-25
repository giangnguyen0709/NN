#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVector<double> x, y, a, b;

    // create graph efficiency and assign data to it:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->widget->xAxis->setLabel("Epoch");
    ui->widget->yAxis->setLabel("Efficiency");
    ui->widget->replot();

    // create graph loss rate - epoch
    ui->widget_2->addGraph();
    ui->widget_2->graph()->setData(a, b);
    ui->widget_2->xAxis->setLabel("Epoch");
    ui->widget_2->yAxis->setLabel("Loss-Rate");
    ui->widget_2->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}

