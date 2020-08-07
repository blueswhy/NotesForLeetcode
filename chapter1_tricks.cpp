/*
Leecode编程技巧，shorter is better。能递归一定不用栈，用STL一定不自己实现。
不提倡防御型编程，不需要检查malloc/new返回的指针是否为空，不需要检查内部函数入口参数的有效性。
*/
#include <stdio.h>
#include <math.h>

bool myfunc_equal(float a, float b)
{
    // 判断是否相等用小于阈值的方法
    if (fabs(a - b) <= 1e-9)
        return true;
    else
        return false;
}
bool myfunc_isOdd(int a)
{
    return (a%2 != 0);    // 预防负数存在
}
// 一个字符数组中统计每个字符出现的次数，需要考虑负数，应该先将字符数组强制转为unsigned char，然后再
// 用来做下标。防止转换成int类型时，有符号扩展。