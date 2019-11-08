#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QByteArray>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    N_=0; selected_=0; limit_=0; epsilon_=0; max_=0; non_=0;
    schedule_=""; tardiness_=""; file_=""; file_byte_="";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    epsilon_=arg1.toInt();
}


void MainWindow::on_pushButton_2_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/tihana/Desktop/build-Projekt-Desktop_Qt_5_12_0_GCC_64bit-Debug", "Text Files (*.TXT)");

    filename2 = filename.right(11);
    ui->lineEdit_4->setText(filename2);
}


void MainWindow::on_pushButton_released()
{
    double t1, t2;

    t1 = abc::dsecnd();

     abc ABC(filename2, ui->comboBox_5->currentText().toInt(), epsilon_, ui->comboBox_2->currentText().toInt(), ui->comboBox->currentText().toInt(), ui->comboBox_4->currentText().toInt(), ui->comboBox_3->currentText().toInt(), schedule_, tardiness_);

    t2 = abc::dsecnd();
    time_elapsed_ = QString::number(t2-t1);

    ui->lineEdit_2->setText(schedule_);
    ui->lineEdit_3->setText(tardiness_);
    ui->lineEdit_6->setText(time_elapsed_);

}


