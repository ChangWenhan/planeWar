#ifndef MAINSCENE_H
#define MAINSCENE_H
#include"map.h"
#include<heroplane.h>
#include <QWidget>
#include <QTimer>
#include"bullet.h"
#include"enemyplane.h"
#include"bomb.h"

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = 0);
    ~MainScene();

    void initScence();

    //启动游戏
    void playGame();
    //更新游戏的坐标
    void updatePosition();
    //绘制到屏幕
    void paintEvent(QPaintEvent*);
    //重写鼠标移动的事件
    void mouseMoveEvent(QMouseEvent *);
    //敌方出场
    void enemyToScene();
    //碰撞检测函数
    void collisionDetection();
    //敌方数组
    EnemyPlane m_enemys[ENEMY_NUM];
    //爆炸数组
    bomb m_bombs[BOMB_NUM];
    //敌方出场间隔记录
    int m_recorder;
    //地图对象
    Map m_map;
    //飞机对象
    HeroPlane m_hero;
    //定时器
    QTimer m_Timer;
};

#endif // MAINSCENE_H
