#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QObject>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QList>
#include<QTimer>
#include<QPointF>

#include"pawn.h"
#include"coremap.h"
#include"enemy.h"
#include"config.h"




class GameWindow :public QGraphicsScene
{
    Q_OBJECT
private:
    QPointer<CoreMap> pMap;
//    CoreMap* pMap;
public:
    bool ifStartGaming;
    bool ifPawnDying;
    QPointer<Pawn> pPawn;
    QPointer<Block> temp;
    QPointer<Enemy> tempEnemy;
    QList<QPointer<Enemy>> enemy;

//    Pawn* pPawn;
    GameWindow();
    void getController();
    //以下用于传递信息
    QPointF PawnLocation;
    QPointer<QTimer> pData;
//    QTimer* pData;
    void UpdateData();
    void Init();
    void ReInit();
    ~GameWindow();


signals:

};

#endif // GAMEWINDOW_H
