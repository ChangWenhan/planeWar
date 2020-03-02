#ifndef MAP_H
#define MAP_H
#include<QPixmap>


class Map
{
public:
    //构造函数
    Map();
    //地图滚动坐标运算
    void mapPosition();
public:
    QPixmap m_map1; //地图图片对象
    QPixmap m_map2;

    int m_map1_posY; //地图Y轴坐标
    int m_map2_posY;

    int m_scroll_speed; //地图滚动幅度
};

#endif // MAP_H
