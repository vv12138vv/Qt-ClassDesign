#ifndef COREMAP_H
#define COREMAP_H

#include<QWidget>
#include"block.h"
#include<QVector>
#include<QPainter>
#include"config.h"
#include"enemy.h"
#include<QPointer>

class CoreMap :public QWidget
{
    Q_OBJECT
private:
    QPixmap PixGrassBlock;
    QPixmap PixLandBlock;
public:
    QVector<QPoint> GrassBlockArray;
    QVector<QPoint> LandBlockArray;
    QVector<QPoint> StoneBlockArray;
    QVector<QPoint> EnemyArray;
    explicit CoreMap(int (*Map)[X_NUMBER]);
    QPoint PawnLocation;
};


#endif // COREMAP_H
