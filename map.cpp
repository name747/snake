#include "map.h"
#include <unistd.h> //linux header file for sleep
// #include <windows.h>

void Map::PrintInitmap()//Draw initial map
{
    for (auto& point : initmap)
    {
        point.Print();
        usleep(10000);//Replace Sleep(10) with usleep(10000), unit is microseconds;
    }
}
