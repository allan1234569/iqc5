#ifndef ROUND_H
#define ROUND_H

#include <stdio.h>
#include <stdlib.h>

#define Random(a,b) (int)(((float)rand()/RAND_MAX)*((b)-(a)) + (a))    //产生区间[a,b]上的随机整数

#endif // ROUND_H
