#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

template<typename OS,typename T>
static void ostr(OS& o,T t)
{
    o << t;
}
template<typename... ARG>
auto makeString(ARG... arg)->string
{
    ostringstream os;
    int arr[] = { (ostr(os,arg),0)...};
    arr[0]=0;
    return os.str();
}

int main()
{

//#ifdef _MSC_VER
//    std::cerr<< (strrchr(__FILE__, '\\') + 1);
//#else
    std::cerr<< __FILE__;
//#endif
    cout << "Hello World!" << endl;
    cout << makeString(1, 2.3, "my name is", '\t',"lc") << endl;
    return 0;
}
