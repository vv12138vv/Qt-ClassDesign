#include "optionscene.h"
#include "ui_optionscene.h"

OptionScene::OptionScene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionScene)
{
    ui->setupUi(this);
    InitScene();
    QPoint GlobalPos=parent->mapToGlobal(QPoint(0,0));
    int x=GlobalPos.x()+(parent->width()-this->width())/2;
    int y=GlobalPos.y()+(parent->height()-this->height())/2;
    this->move(x,y);
}

//OptionScene::~OptionScene()
//{
//    delete ui;
//}

void OptionScene::InitScene()
{
    //数值初始化
    //窗体初始化
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    //布局初始化
    //滑动条初始化
    //范围
    this->ui->HsbAdjustMusic->setMinimum(0);
    this->ui->HsbAdjustMusic->setMaximum(100);
    this->ui->HsbAdjustSoundeffect->setMinimum(0);
    this->ui->HsbAdjustSoundeffect->setMaximum(100);
    this->ui->HsbAdjustSoundeffect->setValue(SoundEffectValue);
    this->ui->HsbAdjustMusic->setValue(MusicValue);
    //操作
    this->ui->HsbAdjustMusic->setSingleStep(10);
    this->ui->HsbAdjustSoundeffect->setSingleStep(10);
}


void OptionScene::on_BtnCloseOption_clicked()
{
    this->close();
}


void OptionScene::on_HsbAdjustSoundeffect_valueChanged(int value)//设置音效
{
    SoundEffectValue=value;
    ui->LSounEffectValue->setText(QString::number(SoundEffectValue));
}


void OptionScene::on_HsbAdjustMusic_valueChanged(int value)//设置音乐
{
    MusicValue=value;
    ui->LMusicValue->setText(QString::number(MusicValue));
}

