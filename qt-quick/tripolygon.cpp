#include "tripolygon.h"

TriPolygon::TriPolygon(int i, int j, int k)
{
    a = i;
    b = j;
    c = k;
}

bool operator <(TriPolygon t1, TriPolygon t2)
{
    return t1.z < t2.z;
}
