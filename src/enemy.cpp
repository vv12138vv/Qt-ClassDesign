#include "enemy.h"
#include"weapon.h"
#include"gamewindow.h"

Enemy::Enemy(QPoint _Location,GameWindow* _GameWindow):Character(_Location)
{

    pGameWindow=_GameWindow;
    MakeEnemyAnimation();
    Facing=Left;
    OriginLocation=_Location;
}

void Enemy::init()
{
    pSwitchmap=new QTimer;
    connect(pSwitchmap,&QTimer::timeout,this,&Enemy::SwitchMap);
    pSwitchmap->start(64);

    pJudgeAction=new QTimer;
    connect(pJudgeAction,&QTimer::timeout,this,&Enemy::JudgeAction);
    pJudgeAction->start(64);
}

void Enemy::MakeEnemyAnimation()
{
    if(Enemy::RAnimation.size()!=0&&Enemy::LAnimation.size()!=0)
    {
        return ;
    }
    QPixmap EnemyRightShoot(":/Resource/Image/Character/EnemyRightShoot.png");
    Enemy::RAnimation.push_back(EnemyRightShoot);
    QPixmap EnemyRightMove1(":/Resource/Image/Character/Enemyright.png");
    Enemy::RAnimation.push_back(EnemyRightMove1);
    QPixmap EnemyRightMove2(":/Resource/Image/Character/EnemyRightMove1.png");
    Enemy::RAnimation.push_back(EnemyRightMove2);
    QPixmap EnemyRightMove3(":/Resource/Image/Character/EnemyRightMove2.png");
    Enemy::RAnimation.push_back(EnemyRightMove3);
    QPixmap EnemyRightMove4(":/Resource/Image/Character/EnemyRightMove3.png");
    Enemy::RAnimation.push_back(EnemyRightMove4);
    QPixmap EnemyRightMove5(":/Resource/Image/Character/EnemyRightMove4.png");
    Enemy::RAnimation.push_back(EnemyRightMove5);
    QPixmap EnemyRightMove6(":/Resource/Image/Character/EnemyRightMove5.png");
    Enemy::RAnimation.push_back(EnemyRightMove6);
    QPixmap EnemyRightMove7(":/Resource/Image/Character/EnemyRightMove6.png");
    Enemy::RAnimation.push_back(EnemyRightMove7);

    QPixmap EnemyLeftShoot(":/Resource/Image/Character/EnemyLeftShoot.png");
    Enemy::LAnimation.push_back(EnemyLeftShoot);
    QPixmap EnemyLeftMove1(":/Resource/Image/Character/Enemyleft.png");
    Enemy::LAnimation.push_back(EnemyLeftMove1);
    QPixmap EnemyLeftMove2(":/Resource/Image/Character/EnemyLeftMove1.png");
    Enemy::LAnimation.push_back(EnemyLeftMove2);
    QPixmap EnemyLeftMove3(":/Resource/Image/Character/EnemyLeftMove2.png");
    Enemy::LAnimation.push_back(EnemyLeftMove3);
    QPixmap EnemyLeftMove4(":/Resource/Image/Character/EnemyLeftMove3.png");
    Enemy::LAnimation.push_back(EnemyLeftMove4);
    QPixmap EnemyLeftMove5(":/Resource/Image/Character/EnemyLeftMove4.png");
    Enemy::LAnimation.push_back(EnemyLeftMove5);
    QPixmap EnemyLeftMove6(":/Resource/Image/Character/EnemyLeftMove5.png");
    Enemy::LAnimation.push_back(EnemyLeftMove6);
    QPixmap EnemyLeftMove7(":/Resource/Image/Character/EnemyLeftMove6.png");
    Enemy::LAnimation.push_back(EnemyLeftMove7);

    for(int i=0;i<Enemy::RAnimation.size();i++)

    {
        Enemy::RAnimation[i]=Enemy::RAnimation[i].scaled(QSize(CUBE,CUBE*2));
    }
    for(int i=0;i<Enemy::LAnimation.size();i++)
    {
        Enemy::LAnimation[i]=Enemy::LAnimation[i].scaled(QSize(CUBE,CUBE*2));
    }
}


void Enemy::SwitchMap()
{
    if(Going==Left)
    {
        if(ifpressgoleft)
        {
            this->setPixmap(Enemy::LAnimation[Lnum]);
            Facing=Left;
            Lnum++;
            if(Lnum>7)
            {
                Lnum=2;
            }
            return;
        }
        else
        {
            Lnum=1;
            this->setPixmap(Enemy::LAnimation[Lnum]);
        }
    }
    if(Going==Right)
    {
        if(ifpressgoright)
        {
            this->setPixmap(Enemy::RAnimation[Rnum]);
            Facing=Right;
            Rnum++;
            if(Rnum>7)
            {
                Rnum=2;
            }
            return;
        }
        else
        {
             Rnum=1;
             this->setPixmap(Enemy::RAnimation[Rnum]);
        }
    }
}


void Enemy::JudgeAction()
{
    float PawnX=pGameWindow->PawnLocation.x();
    float PawnY=pGameWindow->PawnLocation.y();
    if(this->y()+CUBE/2<=PawnY+2*CUBE&&PawnY<=this->y()+CUBE/2&&!pGameWindow->ifPawnDying)
    {
        if(this->x()-PawnX>=0&&this->x()-PawnX<=8*CUBE&&this->Facing==Left)
        {
            if(pWeaponHolded->getClipBullet()==0)
            {
                pWeaponHolded->Reload();
            }
            this->setPixmap(LAnimation[0]);
            pWeaponHolded->Shoot();
            return;
        }
        else if(PawnX-this->x()>=0&&PawnX-this->x()<=8*CUBE&&this->Facing==Right)
        {
            if(pWeaponHolded->getClipBullet()==0)
            {
                pWeaponHolded->Reload();
            }
            this->setPixmap(RAnimation[0]);
            pWeaponHolded->Shoot();
            return;
        }
    }
    else
    {
        if(this->x()>OriginLocation.x()-Movefield&&ifCanGoleft)
        {
            ifpressgoleft=true;
        }
        if(this->x()<=OriginLocation.x()-Movefield+CUBE/2&&ifCanGoright)
        {
            ifpressgoleft=false;
            ifpressgoright=true;
        }
        if(this->x()>=OriginLocation.x()+Movefield-CUBE/2&&ifCanGoleft)
        {
            ifpressgoleft=true;
            ifpressgoright=false;
        }
    }

}


Enemy::~Enemy()
{
    if(pJudgeAction)
    {
        delete pJudgeAction;
        pJudgeAction=nullptr;
    }
    if(pSwitchmap)
    {
        delete pSwitchmap;
        pSwitchmap=nullptr;
    }
}
