#include "bullet.h"
#include"config.h"

Bullet::Bullet()
{
    m_Bullet.load(BULLET_PATH);
    //坐标
    m_X = GAME_WIDTH*0.5-m_Bullet.width()*0.5;
    m_Y = GAME_HEIGHT;
    //状态
    m_Free = true;
    //子弹速度
    m_Speed = BULLET_SPEED;
    //子弹边框
    m_Rect.setWidth(m_Bullet.width());
    m_Rect.setHeight(m_Bullet.height());
    m_Rect.moveTo(m_X,m_Y);
}

void Bullet::updatePosition()
{
    //空闲不计算坐标
    if(m_Free)
    {
        return;
    }
    m_Y -= m_Speed;
    m_Rect.moveTo(m_X,m_Y);

    if(m_Y<=- m_Rect.height())
    {
        m_Free = true;
    }
}
