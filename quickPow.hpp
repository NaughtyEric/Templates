#ifndef __QUICKPOW_HPP
#define __QUICKPOW_HPP

///非递归版本
///<args>base为底数， index为指数
int quickPow(int base, int index)
{
    int ans = 1;
    while (index != 0)
    { //最终结果始终等于ans * (base^index)
        if (index % 2 == 1)
        {
            ans *= base;
            /*index--; 正常应当有此语句 但是由于除法取整机制 这里可以省略*/
        }           //此时保证index为偶数
        index /= 2; //base ^ index = (base * base)^(index/2)
        base *= base;
    }
    return ans;
}

///递归版本
///<args>base为底数， index为指数
int quickPow2(int base, int index)
{
    //特殊情况
    if(index == 1) return base;
    if(index == 0) return 1;

    //奇偶分别处理
    if (index % 2 == 1)
        return quickPow2(base * base, index / 2) * base;
    else
        return quickPow2(base * base, index / 2);
}
#endif