#ifndef BULLET_H
#define BULLET_H

#include"config.h"
#include"block.h"

#include <QObject>
#include<QTimer>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QDebug>
#include<QList>
#include<QSound>
#include<QPointer>

class Weapon;//前置声明武器类
class Pawn;
class Enemy;


//子弹类
class Bullet : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QPointer<QTimer> pTimer;
//    QTimer* pTimer;//计时器，用于子弹飞行
    bool MoveDirection;
    QPointer<Weapon> pShootFrom;
//    Weapon* pShootFrom;//指向发射子弹的武器
    void Move();//子弹飞行函数
public:
    explicit Bullet(const QPointF& _Shooter,QPointer<Weapon> _ShootFrom);
    ~Bullet();
signals:

};

#endif // BULLET_H
