#include "point.h"
#include "tools.h"
#include <iostream>

void Point::Print()//Print square block
{
    SetCursorPosition(x, y);
    std::cout << "■" ;
}

void Point::PrintCircular()//Print circle
{
    SetCursorPosition(x, y);
    std::cout << "●" ;
}

void Point::Clear()//Clear output
{
    SetCursorPosition(x, y);
    std::cout << "  " ;
}

void Point::ChangePosition(const int x, const int y)//改变坐标
{
    this->x = x;
    this->y = y;
}
