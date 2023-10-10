#include "weapon.h"

Weapon::Weapon(WeaponType _WeaponType,QPointer<Character> _Holder)
{
    ifcanshoot=false;
    switch(_WeaponType)
    {
    case Pistol:
    {
        this->ClipBulletMax=7;
        this->ClipBullet=ClipBulletMax;
        this->ClipNum=4;
        this->Damage=25;
        this->BulletSpeed=25;
        this->pHolder=_Holder;
//        this->pShootEffect=new QSound(":/Resource/Sound/Gun/PistolSoundEffect.wav");
        this->pShootEffect=new QSound(":/Resource/Sound/Gun/PistolSoundEffect.wav");
        this->pGunReload=new QSound(":/Resource/Sound/Gun/PistolReload.wav");
        this->ShootWaiting=new QTimer;
        connect(ShootWaiting,&QTimer::timeout,this,&Weapon::ControlShoot);
        ShootWaiting->start(500);

        break;
    }
    }
}

void Weapon::ControlShoot()
{
    ifcanshoot=true;
}



void Weapon::Shoot()
{
    if(ifcanshoot)
    {
            if(ClipBullet==0)
            {
                return;
            }
            pShootEffect->play();
            pHoldBullet=new Bullet(pHolder->pos(),this);
            pHolder->scene()->addItem(pHoldBullet);
            this->ClipBullet--;
            ifcanshoot=false;
    }

}

void Weapon::Reload()
{
    if(ClipNum==0)
    {
        return;
    }
    else
    {
        this->ClipNum--;
        this->ClipBullet=ClipBulletMax;
        pGunReload->play();
    }
}


int Weapon::getClipBullet() const
{
    return this->ClipBullet;
}

int Weapon::getClipNum() const
{
    return this->ClipNum;
}

int Weapon::getClipBulletMax() const
{
    return this->ClipBulletMax;
}

int Weapon::getBulletSpeed() const
{
    return this->BulletSpeed;
}



QPointer<Character> Weapon::getHolder() const
{
    return pHolder;
}

int Weapon::getDamage() const
{
    return this->Damage;
}

Weapon::~Weapon()
{

    if(pShootEffect!=nullptr)
    {
        delete pShootEffect;
    }
    if(pGunReload!=nullptr)
    {
        delete pGunReload;
    }
}

