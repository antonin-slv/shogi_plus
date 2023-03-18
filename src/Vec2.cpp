#include "Vec2.h"

Vec2::Vec2(int _x, int _y)
{
    x = _x;
    y = _y;
}

Vec2 operator+(Vec2 v1, Vec2 v2)
{
    return Vec2(v1.x + v2.x, v1.y + v2.y);
}

Vec2 operator-(Vec2 v1, Vec2 v2)
{
    return Vec2(v1.x - v2.x, v1.y - v2.y);
}

bool operator==(Vec2 v1, Vec2 v2)
{
    return (v1.x == v2.x && v1.y == v2.y);
}

bool operator!=(Vec2 v1, Vec2 v2)
{
    return !(v1 == v2);
}

Vec2 Vec2::operator+=(Vec2 v)
{
    x += v.x;
    y += v.y;
    return *this;
}