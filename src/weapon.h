#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include"character.h"
#include"bullet.h"
#include<QDebug>
#include"enemy.h"
#include<QSound>
#include<QMediaPlayer>

enum WeaponType
{
    Pistol=1,Rifle,MachineGun
};


class Weapon : public QObject
{
    Q_OBJECT
private:
    int ClipNum;
    int ClipBulletMax;
    int ClipBullet;
    int Damage;
    int BulletSpeed;
    QPointer<QSound> pShootEffect;
    QPointer<QSound> pGunReload;

    QPointer<Character> pHolder;
    QPointer<Bullet> pHoldBullet;
    QPointer<QTimer> ShootWaiting;
    WeaponType TheType;

    bool ifcanshoot;
public:
    explicit Weapon(WeaponType _WeaponType,QPointer<Character> _Holder);
    void Shoot();
    void Reload();
    int getClipBullet() const;
    int getClipNum() const;
    int getDamage() const;
    int getClipBulletMax() const;
    int getBulletSpeed() const;
    QPointer<Character> getHolder() const;
    void ControlShoot();
    ~Weapon();

signals:

};

#endif // WEAPON_H
