#include "plotting.h"
#include "ui_plotting.h"

Plotting::Plotting(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Plotting)
{
    ui->setupUi(this);



}

Plotting::~Plotting()
{
    delete ui;
}

void Plotting::plotting()
{
    QVector<double> x, y;

    // create graph and assign data to it:
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x, y);
    ui->plot->replot();
    ui->plot->update();

}


void Plotting::on_pushButton_clicked()
{
    //set label axis
    ui->plot->xAxis->setLabel(ui->textbox1->text());
    ui->plot->yAxis->setLabel(ui->textbox2->text());
    plotting();
}

void Plotting::on_textbox1_textEdited(const QString &arg1)
{

}

void Plotting::on_textbox2_textEdited(const QString &arg1)
{

}
