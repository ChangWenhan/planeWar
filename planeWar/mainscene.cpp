#include "mainscene.h"
#include "config.h"
#include "map.h"
#include "heroplane.h"
#include <QIcon>
#include<QPainter>
#include<QPixmap>
#include<QMouseEvent>
#include<QSound>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    initScence();//调用初始化场景
    playGame();//启动游戏
}

MainScene::~MainScene()
{

}

void MainScene::initScence()
{
    //设置窗口固定尺寸
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    //设置标题
    setWindowTitle(GAME_TITLE);
    //加载图标
    setWindowIcon(QIcon(GAME_ICON));
    //定时器的设置
    m_Timer.setInterval(GAME_RATE);
    //地方初始化
    m_recorder=0;

    //随机数种子（看需求）
    srand((unsigned int)time(NULL));
}

void MainScene::playGame()
{
    //启动背景音乐
    QSound::play(SOUND_BACKGROUND);
    //启动定时器
    m_Timer.start();
    //监听定时器发送的信号
    connect(&m_Timer,&QTimer::timeout,[=]()
    {
        //敌方出场
        enemyToScene();
        //更新游戏中的坐标，绘制到屏幕中
        updatePosition();
        update();
        collisionDetection();
    });
}

void MainScene::updatePosition()
{
    m_map.mapPosition();
    //测试子弹
    //temp.m_Free = false;
    //temp.updatePosition();

    m_hero.shoot();

    //计算所有非空闲子弹的坐标
    for(int i=0;i<BULLET_NUM;i++)
    {
        if(m_hero.m_bullets[i].m_Free==false)
        {
            m_hero.m_bullets[i].updatePosition();
        }
    }

    //敌方出场
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free==false)
        {
            m_enemys[i].updatePosition();
        }
    }
    //计算爆炸播放的图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            m_bombs[i].updateInfo();
        }
    }
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);

    //绘制英雄飞机
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);
    //测试子弹
    for(int i=0;i<BULLET_NUM;i++)
    {
        //如果空闲状态，绘制
        if(m_hero.m_bullets[i].m_Free==false)
        {
            painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets->m_Bullet);
        }
    }
    //绘制敌方
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free==false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].enemy);
        }
    }
    //绘制爆炸图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }

}

void MainScene::mouseMoveEvent(QMouseEvent * event)
{
    int x = event->x()-m_hero.m_Rect.width()*0.5;
    int y = event->y()-m_hero.m_Rect.height()*0.5;

    //边界的检测
    if(x<=0)
    {
        x=0;
    }
    if(x>=GAME_WIDTH-m_hero.m_Rect.width())
    {
        x=GAME_WIDTH-m_hero.m_Rect.width();
    }
    if(y<=0)
    {
        y=0;
    }
    if(y>=GAME_HEIGHT-m_hero.m_Rect.height())
    {
        y=GAME_HEIGHT-m_hero.m_Rect.height();
    }

    m_hero.setPosition(x,y);
}

void MainScene::enemyToScene()
{
    m_recorder++;
    if(m_recorder<ENEMY_INTERVAL)
    {
        return;
    }
    m_recorder=0;

    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            m_enemys[i].m_Free = false;
            m_enemys[i].m_X = rand()%(GAME_WIDTH-m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void MainScene::collisionDetection()
{
    //遍历所有非空闲的敌方
    for(int i=0;i<ENEMY_NUM;i++)
    {
        //若果是空闲的飞机，执行下一次循环
        if(m_enemys[i].m_Free)
        {
            continue;
        }
        //遍历所有非空闲的子弹
        for(int j=0;j<BULLET_NUM;j++)
        {
            //空闲子弹
            if(m_hero.m_bullets[i].m_Free)
            {
                continue;
            }

            //相交则算为碰撞，状态同时设置为真
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[i].m_Rect))
            {
                m_enemys[i].m_Free = true;
                m_hero.m_bullets[i].m_Free = true;
                //播放爆炸效果
                //播放爆炸效果
                for(int k = 0 ; k < BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_Free)
                    {
                        //播放音效
                        QSound::play(SOUND_BOMB);
                        //爆炸状态设置为非空闲
                        m_bombs[k].m_Free = false;

                        //更新坐标
                        m_bombs[k].m_X = m_enemys[i].m_X;
                        m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }
    }

}






