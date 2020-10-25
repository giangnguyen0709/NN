#include "dialog.h"
#include "ui_dialog.h"
#include<QFileDialog>
#include<QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    NNmode();
    Display();
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::plotting()
{
    // generate some data:
    QVector<double> x, y;

    // create graph:
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x, y);



    // give the axes some labels:
    ui->plot->xAxis->setLabel("NEpoch");
    ui->plot->yAxis->setLabel("Effiziency");

    ui->plot->replot();
    ui->plot->update();

}


void Dialog::on_pushButton_clicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*);;Text File (*.txt);;Excell File (*.xlsx);;Image File (*.png)"
                );
    /*QString filename1 = QFileDialog::getExistingDirectory(
                this,
                tr("Open File"),
                "C://"
                );*/


}

void Dialog::on_pushButton_2_clicked()
{
    ui->plot->yAxis->scaleRange(ui->spinBox_3->value());


    plotting();
}


void Dialog::on_spinBox_valueChanged(int)
{

}

void Dialog::on_spinBox_2_valueChanged(int)
{

}

void Dialog::on_spinBox_3_valueChanged(int)
{

}

void Dialog::on_spinBox_4_valueChanged(int)
{

}

void Dialog::NNmode()
{
    //create combo box:
    ui->comboBox->addItem("FC NN without Hidden-Layer");
    ui->comboBox->addItem("FC NN with one Hidden-Layer");
    ui->comboBox->addItem("FC NN with two Hidden-Layer");


}

void Dialog::Display()
{
    ui->comboBox_2->addItem("Histogram");
    ui->comboBox_2->addItem("Success rate");
    ui->comboBox_2->addItem("Distribution");
}


