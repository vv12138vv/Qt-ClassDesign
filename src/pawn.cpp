#include "pawn.h"
#include"weapon.h"

Pawn::Pawn(QPoint _Location):Character(_Location)
{
    Health=200;
    MakePawnAnimation();
    this->setPixmap(RAnimation[1]);
    pSwitchmap=new QTimer;
    connect(pSwitchmap,&QTimer::timeout,this,&Pawn::SwitchMap);
    pSwitchmap->start(64);
}

void Pawn::MakePawnAnimation()
{
    QPixmap PawnRightShoot(":/Resource/Image/Character/PawnRightShoot.png");//0
    RAnimation.push_back(PawnRightShoot);
    QPixmap Pawnright1(":/Resource/Image/Character/PawnRightMove1.png");//1
    RAnimation.push_back(Pawnright1);
    QPixmap Pawnright2(":/Resource/Image/Character/PawnRightMove2.png");//2
    RAnimation.push_back(Pawnright2);
    QPixmap Pawnright3(":/Resource/Image/Character/PawnRightMove3.png");//3
    RAnimation.push_back(Pawnright3);
    QPixmap Pawnright4(":/Resource/Image/Character/PawnRightMove4.png");//4
    RAnimation.push_back(Pawnright4);
    QPixmap Pawnright5(":/Resource/Image/Character/PawnRightMove5.png");//5
    RAnimation.push_back(Pawnright5);
    QPixmap Pawnright6(":/Resource/Image/Character/PawnRightMove6.png");//6
    RAnimation.push_back(Pawnright6);
    QPixmap PawnLeftShoot(":/Resource/Image/Character/PawnLeftShoot.png");//7
    LAnimation.push_back(PawnLeftShoot);
    QPixmap Pawnleft1(":/Resource/Image/Character/PawnLeftMove1.png");//8
    LAnimation.push_back(Pawnleft1);
    QPixmap Pawnleft2(":/Resource/Image/Character/PawnLeftMove2.png");//9
    LAnimation.push_back(Pawnleft2);
    QPixmap Pawnleft3(":/Resource/Image/Character/PawnLeftMove3.png");//10
    LAnimation.push_back(Pawnleft3);
    QPixmap Pawnleft4(":/Resource/Image/Character/PawnLeftMove4.png");//11
    LAnimation.push_back(Pawnleft4);
    QPixmap Pawnleft5(":/Resource/Image/Character/PawnLeftMove5.png");//12
    LAnimation.push_back(Pawnleft5);
    QPixmap Pawnleft6(":/Resource/Image/Character/PawnLeftMove6.png");//13
    LAnimation.push_back(Pawnleft6);
    for(int i=0;i<RAnimation.size();i++)
    {
        RAnimation[i]=RAnimation[i].scaled(CUBE,CUBE*2);
    }
    for(int i=0;i<LAnimation.size();i++)
    {
        LAnimation[i]=LAnimation[i].scaled(CUBE,CUBE*2);
    }
}

void Pawn::keyPressEvent(QKeyEvent* event)
{

   switch(event->key())
   {
       case Qt::Key::Key_D:
       {
           if(!event->isAutoRepeat())
           {
               ifpressgoright=true;
           }
           break;
       }
       case Qt::Key::Key_A:
       {
           if(!event->isAutoRepeat())
           {
               ifpressgoleft=true;
           }
           break;
       }
       case Qt::Key::Key_J:
       {
           if(Facing==Right)
           {
               this->setPixmap(RAnimation[0]);
           }
           else if(Facing==Left)
           {
               this->setPixmap(LAnimation[0]);
           }
           pWeaponHolded->Shoot();
           break;
       }
       case Qt::Key::Key_K:
       {
           if(ifCanJump)
           {
               ifJumping=true;
               Jump();
           }
           break;
       }
       case Qt::Key::Key_R:
       {
           pWeaponHolded->Reload();
           break;
       }

   }
}


void Pawn::keyReleaseEvent(QKeyEvent *event)
{
   switch(event->key())
   {
       case Qt::Key::Key_D:
       {
           if(!event->isAutoRepeat())
           {
               ifpressgoright=false;
           }
           break;
       }
       case Qt::Key::Key_A:
       {
           if(!event->isAutoRepeat())
           {
               ifpressgoleft=false;
           }
           break;
       }
   }
}



void Pawn::SwitchMap()
{
    if(Going==Left)
    {
        if(ifpressgoleft)
        {
            this->setPixmap(LAnimation[Lnum]);
            Facing=Left;
            Lnum++;
            if(Lnum>6)
            {
                Lnum=1;
            }
            return;
        }
        else
        {
            Lnum=1;
            this->setPixmap(LAnimation[Lnum]);
        }

    }
    if(Going==Right)
    {
        if(ifpressgoright)
        {
            this->setPixmap(RAnimation[Rnum]);
            Facing=Right;
            Rnum++;
            if(Rnum>6)
            {
                Rnum=1;
            }
            return;
        }
        else
        {
             Rnum=1;
             this->setPixmap(RAnimation[Rnum]);
        }
    }
}

Pawn::~Pawn()
{
   if(pSwitchmap)
   {
       delete pSwitchmap;
   }
//   prepareGeometryChange();
}
