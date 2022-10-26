#ifndef __INTERGER_HPP
#define __INTERGER_HPP
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

class IntergerExceptions : public std::exception{
    int ErrorLine;
    std::string ErrorReason;
public:
    IntergerExceptions(int);
    IntergerExceptions(int, const char*);

    void printErrorLog();
};
IntergerExceptions::IntergerExceptions(int Line)
{
    ErrorLine = Line;
    ErrorReason = "Unknown error";
}
IntergerExceptions::IntergerExceptions(int Line, const char* errorReason)
{
    ErrorLine = Line;
    ErrorReason = errorReason;
}
void IntergerExceptions::printErrorLog()
{
    fprintf(stderr, "%s at line:%d. Check your source code.", ErrorReason.c_str() ,ErrorLine);
}
class Integer
{
private:
    static const int MOD = 100000;
    static const int WIDTH = 5;
    std::vector<int> num;
    int sign;
protected:
    //Subclass can make changes though operator[]
    int& operator [] (const int &__index)
    {
        if(size() <= __index) 
        {
            fprintf(stderr, "Error:Index [%d] out of range %zu", __index, size());
            exit(-1);
        }
        return num[__index];
    }
    //Visit intergers
    const int operator [] (const int &__index) const 
    {
        if(size() <= __index) 
        {
            fprintf(stderr, "Error:Index [%d] out of range %zu", __index, size());
            exit(-1);
        }
        return num[__index];
    }
public:
    Integer(const std::string&);
    Integer(const Integer&);
    template<typename _Tp> Integer(const _Tp&);
    Integer();

    ~Integer();

	friend std::istream& operator >> (std::istream&,Integer&);
	friend std::ostream& operator << (std::ostream&,const Integer&);

    //initalize from a string.Throw Exception if there're invalid characters in the string.
    Integer operator = (const std::string &s)
    {
        num.clear();
        int sp = 0;
        if (s[0] != '-') sign = 1;
        else if (isdigit(s[0])){
            sign = -1;
            sp = 1;
        }else throw IntergerExceptions(79, "Invalid characters found");
        for(int i = sp; i<s.length(); ++i)
            if(!isdigit(s[i])) throw IntergerExceptions(81, "Invalid characters found");
        int si = s.size();
        for (int r = si-1; r>=sp; r -= WIDTH) {
            int l = std::max(sp,r-WIDTH+1);
            int x = 0;
            sscanf(s.substr(l,r-l+1).c_str(),"%d",&x);
            num.push_back(x);
        }
        return *this;
    }
    template<typename _Tp> Integer operator = (const _Tp &n)
    {
		this->num.clear();
        _Tp t = n;
		if (n >= 0) sign = 1;
		else sign = -1, t = -t;
		while(t) {
			num.push_back(t%MOD);
			t /= MOD;
		}
		return *this;
	}

    Integer operator - () const
    {
        auto __tmp = Integer(*this);
        __tmp.sign = -sign;
        return __tmp;
    }

    inline size_t size() const;
    
    //comparison operators.
    friend bool operator < (const Integer &, const Integer &);
    friend bool operator > (const Integer &, const Integer &);
    friend bool operator >= (const Integer &, const Integer &);
    friend bool operator <= (const Integer &, const Integer &);
    friend bool operator == (const Integer &, const Integer &);
    friend bool operator != (const Integer &, const Integer &);

    Integer operator += (const Integer &);
    Integer operator -= (const Integer &);
    Integer operator *= (const Integer &);
    Integer operator /= (const Integer &);

};
//Initalize through a string
Integer::Integer(const std::string &s)
{
    *this = s;
}
template<typename _Tp> Integer::Integer(const _Tp &n)
{
    *this = n;
}
Integer::Integer(const Integer &_arg)
{
    num = _arg.num;
    sign = _arg.sign;
}
Integer::Integer()
{
    *this = 0;
}
Integer::~Integer()
{
}

std::istream&operator>>(std::istream&in,Integer&n){
	std::string s;
	if (!(in>>s)) return in;
	n = s;
	return in;
}
std::ostream&operator<<(std::ostream&out,const Integer &n){
	if (n.sign == -1) out << '-';
	out<<n.num[n.size()-1];
	for (int i = n.size()-2; i>=0; --i)
		out<<std::setfill('0')<<std::setw(Integer::WIDTH)<<n.num[i];
	return out;
}

inline size_t Integer::size() const {return num.size();}

bool operator < (const Integer &_a, const Integer &_b)
{
    if (_a.sign == -1 && _b.sign == 1) return true;
	if (_a.sign == 1 && _b.sign == -1) return false;
	if (_a.sign == -1 && _b.sign == -1) {
		return -_b<-_a;
	}
	if (_a.size() != _b.size()) return _a.size()<_b.size();
	for (int i = _a.size()-1; i>=0; --i)
		if (_a.num[i] != _b.num[i])
			return _a.num[i] < _b.num[i];
	return false;
}
bool operator > (const Integer &_a, const Integer &_b)
{
    return _b < _a;
}
bool operator >= (const Integer &_a, const Integer &_b) 
{
    return !(_a < _b);
}
bool operator <= (const Integer &_a, const Integer &_b) 
{
    return !(_b < _a);
}
bool operator == (const Integer &_a, const Integer &_b)
{
    return !(_a < _b) && !(_b < _a);
}
bool operator != (const Integer &_a, const Integer &_b)
{
    return (_a < _b) || (_b < _a);
}

Integer Integer::operator+=(const Integer &x)
{
    if (sign != x.sign) {return (*this) -= -x;}
    int _add = 0;
    for(size_t i = 0; i<x.size(); ++i)
    {
        if(i >= size()) num.push_back(0);
        num[i] += x[i] + _add;
        int t = i;
        while(num[t] >= MOD) {
            if(t >= size())
                num.push_back(_add);
            else num[t] += _add;
        }
    }
}
#endif