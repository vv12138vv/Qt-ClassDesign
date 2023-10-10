#ifndef CHARACTER_H
#define CHARACTER_H

#include"config.h"

#include<QWidget>
#include<QPainter>
#include<QGraphicsItem>
#include<QGraphicsPixmapItem>
#include<QKeyEvent>
#include<QDebug>
#include<QGraphicsScene>
#include<QTimer>
#include<QPointer>



//前置声明
class Weapon;
class Bullet;


enum CharacterType
{
    Controller,Ai
};


enum Direction
{
    None,Right,Left
};

class Character:public QObject,public QGraphicsPixmapItem
{
  Q_OBJECT
public:
    QPointer<Weapon> pWeaponHolded;
//    Weapon* pWeaponHolded;
    //角色生命值
    int Health;
    //简易物理系统
    QTransform* pQtransform;
    const float X_MaxSpeed=3*CUBE;
    const float Acceleration=2*CUBE;
    const float JumpSpeed=10*CUBE;
    const float GAcceleration=7*CUBE;
    const float stopAcceleration=5*CUBE;

    float X_Speed;
    float Y_Speed;
    bool ifpressgoleft=false;
    bool ifpressgoright=false;
    bool ifBeSupported;
    bool ifCanGoleft;//是否可向左移动
    bool ifCanGoright;//是否可向右移动
    bool ifCanJump;
    Direction Going;
    Direction Facing;
    bool ifJumping;//判断是否正在跳跃
    bool ifFalling;//判断是否正在自由落体
//    QTimer* pPhysics;
    QPointer<QTimer> pPhysics;



public:

    Character(QPoint _Location);
    ~Character();
    void PhysicsStart();
    void Physics();
    void JudgeCollision();
    QRectF boundingRect() const;//碰撞检测依据
    void getDamaged(int _Damage);//受到伤害
    void SimulateInertia();
    void SimulateGravity();//模拟重力
    void Moveleft();
    void Moveright();
    void Jump();//跳跃
    void AdjustCollision();
    Direction getDirection() const;
    Direction getFacing() const;
    QPointer<Weapon> getWeapon();
//    Weapon* getWeapon();//返回所持武器

};

#endif // CHARACTER_H
