#include "block.h"


Block::Block()
{
}

Block::Block(BlockType _TheBlock,QPoint& _Location)
{
    this->TheBlock=_TheBlock;
    this->setPos(_Location);
    if(_TheBlock==GrassBlock)
    {
        QPixmap temp(":/Resource/Image/Block/GrassBlock.png");//加载对应图片
        temp=temp.scaled(QSize(CUBE,CUBE));//图片拉伸，适应分辨率
        this->setPixmap(temp);
    }

    if(_TheBlock==LandBlock)
    {
        QPixmap temp(":/Resource/Image/Block/LandBlock.png");
        temp=temp.scaled(QSize(CUBE,CUBE));
        this->setPixmap(temp);
    }
}

Block::Block(const Block& _Block)
{
    this->TheBlock=_Block.TheBlock;
}



QRectF Block::boundingRect() const
{
    return QRectF(0,0,CUBE,CUBE);
}
