#ifndef ABC_H
#define ABC_H

#include <iostream>
#include <utility>
#include <QString>
#include <QByteArray>

#include "population.h"

using namespace std;


class abc {

private:
    int a = 1;

public:

    //abc();

    abc( QString file,int N, float epsilon, int limit, int selected, int max, int not_improving, QString &A, QString &B);

    static bool uvjet_1 (pair<double, int> i, pair<double, int> j); //funkcija iz maina
    static bool uvjet_2 (pair<double, int> i, pair<double, int> j); //funkcija iz maina
    static double dsecnd (void); //vrijeme iz maina


    friend class MainWindow;
};

#endif // ABC_H
