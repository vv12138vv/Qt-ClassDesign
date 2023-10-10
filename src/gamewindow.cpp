#include "gamewindow.h"
#include"mainscene.h"

GameWindow::GameWindow():QGraphicsScene()
{
    Init();
}

void GameWindow::Init()
{
    this->clear();
    ifPawnDying=false;
    pMap=new CoreMap(Map2);
//    this->setItemIndexMethod(QGraphicsScene::NoIndex);
    this->setBackgroundBrush(QBrush(QPixmap(":/Resource/Image/BackGround/GameBackground.jpg")));

    for(int i=0;i<pMap->GrassBlockArray.size();i++)
    {
        temp=new Block(GrassBlock,pMap->GrassBlockArray[i]);
        this->addItem(temp);
        temp=nullptr;
    }
    for(int i=0;i<pMap->LandBlockArray.size();i++)
    {
        temp=new Block(LandBlock,pMap->LandBlockArray[i]);
        this->addItem(temp);
        temp=nullptr;
    }

    pPawn=new Pawn(pMap->PawnLocation);
    this->addItem(pPawn);

    for(int i=0;i<pMap->EnemyArray.size();i++)
    {
        tempEnemy=new Enemy(pMap->EnemyArray[i],this);
        tempEnemy->init();
        enemy.push_back(tempEnemy);
        this->addItem(tempEnemy);
    }






    pData=new QTimer;
    connect(pData,&QTimer::timeout,this,&GameWindow::UpdateData);
    pData->start(16);
}


void GameWindow::getController()
{
    if(pPawn)
    {
        pPawn->setFlag(QGraphicsItem::ItemIsFocusable);
        pPawn->setFocus();
    }
}

void GameWindow::UpdateData()
{
    if(pPawn)
    {

        this->PawnLocation=pPawn->pos();
//        qDebug()<<PawnLocation.x()<<" "<<PawnLocation.y()<<endl;
    }
    if(pPawn&&pPawn->Health<=0)
    {
        this->removeItem(pPawn);
        delete pPawn;
        ifPawnDying=true;
    }

    for(int i=0;i<enemy.size();i++)
    {
        if(enemy[i]&&enemy[i]->Health==0)
        {
            this->removeItem(enemy[i]);
            delete enemy[i];
            this->enemy.removeAt(i);
            i--;
        }
    }
}

void GameWindow::ReInit()
{
    this->clear();
    while(!enemy.empty())
    {
        delete enemy.back();
        enemy.pop_back();
    }

    for(int i=0;i<pMap->EnemyArray.size();i++)
    {
        tempEnemy=new Enemy(pMap->EnemyArray[i],this);
        tempEnemy->init();
        enemy.push_back(tempEnemy);
        this->addItem(tempEnemy);
    }

    ifPawnDying=false;
    pPawn=new Pawn(pMap->PawnLocation);
    this->addItem(pPawn);
    Init();
}

GameWindow::~GameWindow()
{
    if(pData!=nullptr)
    {
        delete pData;
    }
}
