#include "map.h"
#include <unistd.h> //linux 下的头文件用于sleep
// #include <windows.h>

void Map::PrintInitmap()//绘制初始地图
{
    for (auto& point : initmap)
    {
        point.Print();
        usleep(10000);//将Sleep(10)替换为usleep(10000)，因为usleep的单位是微秒;
    }
}
