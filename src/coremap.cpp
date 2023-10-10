#include "coremap.h"


CoreMap::CoreMap(int (*Map)[X_NUMBER])
{
    for(int i=0;i<Y_NUMBER;i++)
    {
        for(int j=0;j<X_NUMBER;j++)
        {
            if(Map[i][j]==GrassBlock)
            {
                QPoint Topleft(j*CUBE,i*CUBE);
                GrassBlockArray.push_back(Topleft);
            }
            if(Map[i][j]==LandBlock)
            {
                QPoint Topleft(j*CUBE,i*CUBE);
                LandBlockArray.push_back(Topleft);
            }
            if(Map[i][j]==StoneBlock)
            {
                QPoint Topleft(j*CUBE,i*CUBE);
                StoneBlockArray.push_back(Topleft);
            }
            if(Map[i][j]==StartBlock)
            {
                PawnLocation={j*CUBE,i*CUBE};
            }
            if(Map[i][j]==EnemyBlock)
            {
                QPoint Topleft(j*CUBE,i*CUBE);
                EnemyArray.push_back(Topleft);
            }
        }
    }
}




