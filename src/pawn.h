#ifndef PAWN_H
#define PAWN_H
#include"character.h"
#include<QVector>


class Pawn:public Character
{

public:
    Pawn(QPoint Location);
    void keyPressEvent(QKeyEvent* event);//移动键盘事件
    void keyReleaseEvent(QKeyEvent* event);
    void SwitchMap();//贴图转换
    QPointer<QTimer> pSwitchmap;
//    QTimer* pSwitchmap;
    QVector<QPixmap> RAnimation;
    int Rnum=1;
    QVector<QPixmap> LAnimation;
    int Lnum=1;
    void MakePawnAnimation();
    ~Pawn();
};

#endif // PAWN_H
