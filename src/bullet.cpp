#include "bullet.h"
#include "pawn.h"
#include"weapon.h"
#include"enemy.h"

Bullet::Bullet(const QPointF& _Shooter,QPointer<Weapon> _ShootFrom)
{

    this->pShootFrom=_ShootFrom;
    if(this->pShootFrom->getHolder()->getFacing()==Direction::Right)
    {
        this->setPos(_Shooter.x()+CUBE+2,_Shooter.y()+CUBE/2);//设置发射位置
        MoveDirection=true;
        this->setPixmap(QPixmap(":/Resource/Image/Gun/BulletRight.png"));
    }
    else if(this->pShootFrom->getHolder()->getFacing()==Direction::Left)
    {
        this->setPos(_Shooter.x()-CUBE-2,_Shooter.y()+CUBE/2);
        MoveDirection=false;
        this->setPixmap(QPixmap(":/Resource/Image/Gun/BulletLeft.png"));
    }
    //子弹飞行定时器

    pTimer = new QTimer;
    connect(pTimer,&QTimer::timeout,this,&Bullet::Move);
    pTimer->start(8);
}


void Bullet::Move()
{
    QList<QGraphicsItem*> qlColliding_Items=this->collidingItems();//碰撞检测

    for(int i=0,n=qlColliding_Items.size();i<n;i++)//遍历发生碰撞的Items
    {
        if(typeid(*(qlColliding_Items[i]))==typeid(Block))//若与Block发生碰撞
        {
           this->scene()->removeItem(this);//则去除该子弹
           delete this;
           return;
        }
        else if(typeid(*(qlColliding_Items[i]))==typeid(Enemy)||typeid(*(qlColliding_Items[i]))==typeid(Pawn))//若与角色类发生碰撞
        {
            this->scene()->removeItem(this);
            QPointer<Character> pCharacter=static_cast<Character*>(qlColliding_Items[i]);
            pCharacter->getDamaged(this->pShootFrom->getDamage());
            delete this;
            return;
        }
    }

    //子弹飞行其他检测项 
    if(MoveDirection==true)
    {
        //qDebug()<<"to right";
        this->setPos(this->x()+this->pShootFrom->getBulletSpeed(),this->y());
    }
    else if(MoveDirection==false)
    {
        //qDebug()<<"to left";
        this->setPos(this->x()-this->pShootFrom->getBulletSpeed(),this->y());
    }

    if(pos().y()<0||pos().y()>scene()->height()||pos().x()>=this->scene()->width()||pos().x()<0)
    {
        this->scene()->removeItem(this);
        delete this;
    }
}

Bullet::~Bullet()
{
    if(pTimer!=nullptr)
    {
        delete pTimer;
        pTimer=nullptr;
    }
}



