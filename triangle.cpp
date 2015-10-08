#include "triangle.h"

Triangle::Triangle()
{
    z = 0;
}

bool operator <(Triangle t1, Triangle t2)
{
    return t1.z < t2.z;
}
