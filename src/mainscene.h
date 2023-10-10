#ifndef MAINSCENE_H
#define MAINSCENE_H

#include"config.h"
#include"optionscene.h"
#include"gamewindow.h"
#include"weapon.h"


#include<QWidget>
#include<QPushButton>
#include<QPixmap>
#include<QKeyEvent>
#include<QTimer>
#include<QMouseEvent>
#include<QPointer>
#include<QSound>


QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QWidget
{
    Q_OBJECT

private:
    void UpdateData();
    void InitScene();

    QPointer<OptionScene> pOptionWindow;
    QPointer<Character> pController;
    QPointer<QTimer> pPawnUi;
    QPointer<GameWindow> pGameWindow;
    Ui::MainScene *ui;
//    GameWindow* pGameWindow;

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    bool ifGaming;
    bool ifPaintMap;
    void mousePressEvent(QMouseEvent* event);


protected://按键操作



private slots:
    void on_BtnOption_clicked();
    void on_BtnStartGame_clicked();
    void on_BtnOption2_clicked();
    void on_BtnQuitGame_clicked();



    void on_RestartButton_clicked();
    void on_QuitButton_clicked();
    void on_BtnRestart_clicked();
};
#endif // MAINSCENE_H
