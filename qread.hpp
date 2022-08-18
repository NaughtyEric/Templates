#ifndef __QREAD_HPP
#define __QREAD_HPP
#include <cstdio>
#include <cctype>

template<typename _Tp>
int read(_Tp &_x) {
    _x = 0;
    int c, i = 1;
    while(!isdigit(c = getchar()))
        switch(c) {
            case EOF:return 0;
            case '-':i=-1;break;
        }
    if(!isdigit(c)) return 0;
    _x = c - '0';
    while(isdigit(c = getchar())) _x = _x * 10 + c - '0';
    _x *= i;
    return 1;
}

template<typename _Tp, typename ...tp>
int read(_Tp &_x, tp &...pkg) {
    if(!read(_x)) return 0;
    return read(pkg...)+1;
}

#endif