#include "character.h"
#include"weapon.h"


Character::Character(QPoint _Location)
{

    this->setPos(_Location);
//    QPixmap pixController(":/Resource/Image/Character/Pawnright.png");
//    pixController=pixController.scaled(QSize(CUBE,CUBE*2));
//    this->setPixmap(pixController);

//角色属性初始化
  Health=100;
  pWeaponHolded=new Weapon(Pistol,this);

//物理效果启用
  this->PhysicsStart();

}

Character::~Character()
{
    if(pPhysics)
    {
        delete pPhysics;
    }
    if(pWeaponHolded)
    {
        delete pWeaponHolded;
    }
//    prepareGeometryChange();
}

void Character::PhysicsStart()//物理效果启用
{
    //初始化数值
    X_Speed=0;
    Y_Speed=0;
    ifCanGoleft=false;
    ifCanGoright=false;
    Going=None;
    Facing=Right;

    pQtransform=new QTransform;
    //启用碰撞检测
    pPhysics=new QTimer;
    connect(pPhysics,&QTimer::timeout,this,&Character::Physics);
    pPhysics->start(8);


}

void Character::Physics()
{
    JudgeCollision();
    Moveleft();
    Moveright();
    SimulateInertia();
    SimulateGravity();
    AdjustCollision();
}




//碰撞检测检测函数
void Character::JudgeCollision()
{
    if(this->scene()->itemAt(this->x(),this->y()+2*CUBE+1,*pQtransform)!=nullptr||
            this->scene()->itemAt(this->x()+CUBE,this->y()+2*CUBE+1,*pQtransform)!=nullptr)
    {
        ifBeSupported=true;
    }
    else
    {
        ifBeSupported=false;
    }
    if(this->scene()->itemAt(this->x()+1+CUBE,this->y()+CUBE,*pQtransform)==nullptr&&
            this->scene()->itemAt(this->x()+CUBE+1,this->y()+2*CUBE-3,*pQtransform)==nullptr&&
            this->scene()->itemAt(this->x()+CUBE+1,this->y()+CUBE/2,*pQtransform)==nullptr)//胸前点
    {
        ifCanGoright=true;
    }
    else
    {
        ifCanGoright=false;
    }

    if(this->scene()->itemAt(this->x()-1,this->y()+CUBE,*pQtransform)==nullptr&&
            this->scene()->itemAt(this->x()-1,this->y()+2*CUBE-3,*pQtransform)==nullptr&&
            this->scene()->itemAt(this->x()-1,this->y()+CUBE/2,*pQtransform)==nullptr)
    {
        ifCanGoleft=true;
    }
    else
    {
        ifCanGoleft=false;
    }
    if(this->scene()->itemAt(this->x()+CUBE/2,this->y()-2,*pQtransform)==nullptr)
    {
        ifCanJump=true;
    }
    else
    {
        ifCanJump=false;
    }


}


//惯性模拟
void Character::SimulateInertia()
{
    QTransform Qtransform;
    if(X_Speed>0&&ifCanGoright)
    {
        Going=Right;
        this->setPos(this->x()+X_Speed*0.016,this->y());
    }

    else if(X_Speed<0&&ifCanGoleft)
    {
        Going=Left;
        this->setPos(this->x()+X_Speed*0.016,this->y());
    }
    else
    {
        Going=None;
    }
    if(Y_Speed<0)
    {
        ifJumping=true;
        this->setPos(this->x(),this->y()+Y_Speed*0.128);
    }
    else if(Y_Speed>0&&ifFalling)
    {
        this->setPos(this->x(),this->y()+Y_Speed*0.016);
    }

}



//重力模拟
void Character::SimulateGravity()
{
    if(ifBeSupported==false)//是否踩踏地面
    {
        Y_Speed+=GAcceleration*float(0.016);//坠落
        ifFalling=true;
    }
    else//重置运动状态
    {
        Y_Speed=0;
        ifFalling=false;
        ifJumping=false;
    }
}

//左移
void Character::Moveleft()
{
    if(ifpressgoleft)
    {
        if(pos().x()>0&&pos().x()+CUBE<=this->scene()->width())
        {
            if(ifFalling==false&&ifJumping==false)
            {
               if(X_Speed<=(-X_MaxSpeed))
               {
                    return;
               }
              else
              {
                   X_Speed+=(-Acceleration)*0.016;
              }
            }
        }
    }
    else if(!ifpressgoleft&&X_Speed<0)
    {
        X_Speed+=stopAcceleration*0.016;
        if(X_Speed>0)
        {
            X_Speed=0;
        }
    }

}

//右移
void Character::Moveright()
{
    if(ifpressgoright)
    {
        if(pos().x()>=0&&pos().x()+CUBE<this->scene()->width())
        {
            if(ifFalling==false&&ifJumping==false)
            {
                if(X_Speed>=X_MaxSpeed)
                {
                    return;
                }
                else
                {
                    X_Speed+=Acceleration*0.016;
                }
            }
        }
    }
    else if(!ifpressgoright&&X_Speed>0)
    {
        X_Speed-=stopAcceleration*0.016;
        if(X_Speed<0)
        {
            X_Speed=0;
        }
    }
}



void Character::Jump()
{
    if(ifBeSupported==false)//未踩踏地面无法跳跃
    {
        return;
    }
    Y_Speed-=JumpSpeed;
    ifJumping=true;

}

//跳跃动作

//碰撞修复
void Character::AdjustCollision()
{
    QGraphicsItem* SupportedBlock=this->scene()->itemAt(this->x()+CUBE/2,this->y()+2*CUBE+1,*pQtransform);
    QGraphicsItem* HeadBlock=this->scene()->itemAt(this->x()+CUBE/2,this->y()-2,*pQtransform);
    QGraphicsItem* RightBlock=this->scene()->itemAt(this->x()+CUBE+1,this->y()+CUBE/2,*pQtransform);
    QGraphicsItem* LeftBlock=this->scene()->itemAt(this->x()-1,this->y()+CUBE/2,*pQtransform);
    if(SupportedBlock!=nullptr)
    {
        this->setPos(this->x(),SupportedBlock->y()-2*CUBE);
    }
    if(HeadBlock!=nullptr)
    {
        this->setPos(this->x(),HeadBlock->y()+CUBE);
    }
//    if(LeftBlock!=nullptr)
//    {
//        this->setPos(LeftBlock->x()+CUBE,this->y());
//    }
//    if(RightBlock!=nullptr)
//    {
//        this->setPos(RightBlock->x(),this->y());
//    }

}


Direction Character::getDirection() const
{
    return Going;
}

Direction Character::getFacing() const
{
    return Facing;
}





 QRectF Character::boundingRect() const
 {
     return QRectF(0,0,CUBE,CUBE*2);
 }








 void Character::getDamaged(int _Damage)
 {
     Health-=_Damage;
     if(Health<=0)
     {
         Health=0;
     }
 }


 QPointer<Weapon> Character::getWeapon()
 {
     return this->pWeaponHolded;
 }

//Weapon* Character::getWeapon()
//{
//    return pWeaponHolded;
//}

