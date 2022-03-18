#ifndef __UTILITIES_HPP
#define __UTILITIES_HPP

template<typename _Tp>
_Tp gcd(const _Tp &__x, const _Tp &__y) {return __y?gcd(__y, __x%__y):__x;}

template<typename _Tp>
_Tp lcm(const _Tp &__x, const _Tp &__y) {return __y/gcd(__x, __y)*__x;}

template<typename _Tp, typename ...tp>
_Tp gcd(const _Tp &_x, const _Tp &_y, const tp& ...pkg)
{
    if (sizeof...(pkg) == 0) return gcd(_x, _y);
    return gcd(gcd(_x, _y), pkg...);
}

template<typename _Tp, typename ...tp>
_Tp lcm(const _Tp &_x, const _Tp &_y, const tp& ...pkg)
{
    if (sizeof...(pkg) == 0) return lcm(_x, _y);
    return lcm(lcm(_x, _y), pkg...);
}




#endif