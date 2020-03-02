#ifndef CONFIG_H
#define CONFIG_H

//游戏配置
#define GAME_WIDTH  512
#define GAME_HEIGHT 768
#define GAME_TITLE "PlaneWar 1.0"
#define GAME_RES_PATH "./plane.rcc"
#define GAME_ICON ":/res/app.ico"
#define GAME_RATE 10  //定时器刷新的间隔 单位毫秒

//地图配置路径
#define MAP_PATH ":/res/img_bg_level_1.jpg"
#define MAP_SCROLL_SPEED 2 //地图滚动的速度

//飞机的属性
#define HERO_PATH ":/res/hero2.png"
//子弹的属性
#define BULLET_PATH ":/res/bullet_9.png"
#define BULLET_SPEED 5
#define BULLET_NUM 30
#define BULLET_INTERVAL 20
//敌方的属性
#define ENEMY_PATH ":/res/img-plane_1.png"
#define ENEMY_SPEED 5
#define ENEMY_NUM 20
#define ENEMY_INTERVAL 30
//碰撞效果
#define BOMB_PATH ":/res/bomb-%1.png" //爆炸资源图片
#define BOMB_NUM 20 //爆炸数量
#define BOMB_MAX 7 //爆炸图片最大索引
#define BOMB_INTERVAL 20 //爆炸切图时间间隔

#define SOUND_BACKGROUND ":/res/bg.wav"
#define SOUND_BOMB ":/res/bomb.wav"

#endif // CONFIG_H
