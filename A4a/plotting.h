#ifndef PLOTTING_H
#define PLOTTING_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Plotting; }
QT_END_NAMESPACE

class Plotting : public QMainWindow
{
    Q_OBJECT

public:
    Plotting(QWidget *parent = nullptr);
    ~Plotting();

private slots:
    void plotting();

    void on_pushButton_clicked();

    void on_textbox1_textEdited(const QString &arg1);

    void on_textbox2_textEdited(const QString &arg1);

private:
    Ui::Plotting *ui;

};
#endif // PLOTTING_H
