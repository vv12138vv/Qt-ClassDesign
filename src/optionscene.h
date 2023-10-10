#ifndef OPTIONSCENE_H
#define OPTIONSCENE_H

#include <QDialog>
#include"config.h"

namespace Ui {
class OptionScene;
}

class OptionScene : public QDialog
{
    Q_OBJECT

public:
    explicit OptionScene(QWidget *parent = nullptr);
//    ~OptionScene();

private slots:
    void on_BtnCloseOption_clicked();

    void on_HsbAdjustSoundeffect_valueChanged(int value);

    void on_HsbAdjustMusic_valueChanged(int value);

private:
    Ui::OptionScene *ui;
    void InitScene();
};

#endif // OPTIONSCENE_H
