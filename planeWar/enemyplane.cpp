#include "enemyplane.h"
#include<config.h>

EnemyPlane::EnemyPlane()
{
    enemy.load(ENEMY_PATH);
    m_X=0;
    m_Y=0;

    m_Free = true;

    m_Speed = ENEMY_SPEED;

    m_Rect.setWidth(enemy.width());
    m_Rect.setHeight(enemy.height());
    m_Rect.moveTo(m_X,m_Y);
}

void EnemyPlane::updatePosition()
{
    if(m_Free)
    {
        return;
    }

    m_Y+=m_Speed;
    m_Rect.moveTo(m_X,m_Y);

    if(m_Y>=GAME_HEIGHT + m_Rect.height())
    {
        m_Free = true;
    }
}
