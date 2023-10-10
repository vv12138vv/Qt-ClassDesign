#ifndef BLOCK_H
#define BLOCK_H

#include"config.h"
#include <QObject>
#include<QPixmap>
#include<QGraphicsPixmapItem>

//地图方块类型枚举
enum BlockType
{
    FreeBlock,GrassBlock,LandBlock,StoneBlock,StartBlock,EnemyBlock
};


//方块类，继承于QOBject和QGraphicsPixmapItem
class Block:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    BlockType TheBlock;
public:
    Block();
    explicit Block(BlockType _TheBlock,QPoint& _Location);//构造函数，构造地图
    Block(const Block& _Block);
    QRectF boundingRect() const;//重载矩形框，用于碰撞检测
signals:

};

#endif // BLOCK_H
