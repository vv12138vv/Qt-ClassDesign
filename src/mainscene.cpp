#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    InitScene();
}

MainScene::~MainScene()
{
    if(pGameWindow!=nullptr)
    {
        delete pGameWindow;
    }
    delete pOptionWindow;
    delete ui;

}



void MainScene::InitScene()
{
    this->setFixedSize(1280,720);//设置窗口大小
    //游戏界面初始
    pGameWindow=new GameWindow();
    pGameWindow->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->BtnOption->setVisible(false);
    ui->GameWindow->setVisible(false);
    ui->label->setVisible(false);
    ui->RestartButton->setVisible(false);
    ui->QuitButton->setVisible(false);
    ui->GameWindow->setScene(pGameWindow);
    ui->GameWindow->setFixedSize(this->rect().width()-1,this->rect().height()-1);
    pGameWindow->setSceneRect(0,0,ui->GameWindow->rect().width(),ui->GameWindow->rect().height());
    ui->GameWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->GameWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->GameWindow->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->BtnRestart->setVisible(false);
    //Ui初始化
    ui->BloodLabel->setStyleSheet("color:red;");
    pPawnUi=new QTimer;
    connect(pPawnUi,&QTimer::timeout,this,&MainScene::UpdateData);

    //数值初始化
    ifGaming=false;
    ifPaintMap=false;
}




void MainScene::on_BtnOption_clicked()
{
    ifGaming=false;
    pOptionWindow=new OptionScene(this);
    pOptionWindow->exec();
    delete pOptionWindow;
    ifGaming=true;
}



void MainScene::on_BtnStartGame_clicked()
{
   ifGaming=true;
   pGameWindow->ifStartGaming=true;
    //隐藏与显示按钮
   ui->BackGround->setVisible(false);
   ui->BtnStartGame->setVisible(false);
   ui->BtnQuitGame->setVisible(false);
   ui->BtnOption2->setVisible(false);
   ui->GameWindow->setVisible(true);
   ui->BtnOption->setVisible(true);
   ui->Title->setVisible(false);
   ui->BtnRestart->setVisible(true);
   pGameWindow->getController();
   pPawnUi->start(10);
}


void MainScene::on_BtnOption2_clicked()
{
    ifGaming=false;
    pOptionWindow=new OptionScene(this);
    pOptionWindow->exec();
    delete pOptionWindow;
}



void MainScene::on_BtnQuitGame_clicked()
{
    ifGaming=false;
    this->close();
}


void MainScene::UpdateData()
{
    if(this->pGameWindow->pPawn)
    {
        QString ClipBullet=QString::number(this->pGameWindow->pPawn->getWeapon()->getClipBullet());
        QString AmmoSum=QString::number((this->pGameWindow->pPawn->getWeapon()->getClipNum())*(this->pGameWindow->pPawn->getWeapon()->getClipBulletMax()));
        ui->BulletCheck->setText(ClipBullet+"/"+AmmoSum);
        QString NowBlood=QString::number(this->pGameWindow->pPawn->Health);
        ui->BloodLabel->setText(NowBlood+"/"+"200");
    }
    if(pGameWindow->ifPawnDying)
    {
        ui->label->setVisible(true);
        ui->QuitButton->setVisible(true);
        ui->RestartButton->setVisible(true);
    }
    if(pGameWindow->enemy.size()==0)
    {
        ui->label->setVisible(true);
        ui->QuitButton->setVisible(true);
        ui->RestartButton->setVisible(true);
    }


}

void MainScene::mousePressEvent(QMouseEvent* event)
{
    double x=event->globalX();
    double y=event->globalY();
    if(event->button()==Qt::LeftButton&&x>=0&&x<=GAME_WIDTH&&y>=0&&y<=GAME_HIGHT)
    {
        pGameWindow->getController();
    }

}




void MainScene::on_RestartButton_clicked()
{

    ui->GameWindow->setVisible(false);
    pGameWindow->ReInit();
    ui->GameWindow->setScene(pGameWindow);
    ui->GameWindow->setVisible(true);

    ui->RestartButton->setVisible(false);
    ui->QuitButton->setVisible(false);
    ui->label->setVisible(false);

}


void MainScene::on_QuitButton_clicked()
{
    ui->RestartButton->setVisible(false);
    ui->QuitButton->setVisible(false);
    ui->label->setVisible(false);
    this->close();
}


void MainScene::on_BtnRestart_clicked()
{
    ui->GameWindow->setVisible(false);
    pGameWindow->ReInit();
    ui->GameWindow->setScene(pGameWindow);
    ui->GameWindow->setVisible(true);

    ui->RestartButton->setVisible(false);
    ui->QuitButton->setVisible(false);
    ui->label->setVisible(false);
}

