#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QByteArray>

#include "abc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_lineEdit_textEdited(const QString &arg1);

    void on_pushButton_released();

    //void on_lineEdit_4_textEdited(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int N_, limit_, selected_, max_, non_;
    float epsilon_;
    QString schedule_, tardiness_;
    QString file_;
    QByteArray file_byte_;
    QString time_elapsed_;

    QString filename;
    QString filename2;
};

#endif // MAINWINDOW_H
