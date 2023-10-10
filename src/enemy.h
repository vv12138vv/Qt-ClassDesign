#ifndef ENEMY_H
#define ENEMY_H

#include"config.h"
#include"character.h"

#include<QKeyEvent>
#include<QDebug>


class Weapon;
class Bullet;
class GameWindow;



class Enemy :public Character
{
public:
    Enemy(QPoint _Location,GameWindow* _GameWinodw);
    QPointer<QTimer> pSwitchmap;
    QPointer<QTimer> pJudgeAction;

    QVector<QPixmap> RAnimation;
    QVector<QPixmap> LAnimation;
    GameWindow* pGameWindow;
    QPointF OriginLocation;
    int Rnum=2;
    int Lnum=2;
    float Movefield=2*CUBE;
    void SwitchMap();//贴图转换
    void JudgeAction();
    void MakeEnemyAnimation();
    void init();
    ~Enemy();
};

#endif // ENEMY_H
