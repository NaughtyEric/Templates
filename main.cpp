#include "interger.hpp"
#include "qread.hpp"
#include "quickPow.hpp"
using std::cin;
using std::cout;
using std::endl;
int main() {
    std::string a, b;
    cin >> a >> b;
    Integer x1 = a, x2 = b;
    cout << (x1+=x2) << endl;
    return 0;
}
//5678987654 768549307653421 768554986641075