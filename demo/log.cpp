#include<iostream>
#include "../include/log.h"

int main()
{   
    //LogInit("log","log2");
    LogInit("log");
    CHECK(2==2)<<"相等吗？";
    INFO << 12335 <<"DUZEJIE TEST";
    CHECK(3==3) <<"相等吗？"<<"相等吗？"<<"相等吗？";
    WARNING(2==3)<<2 <<" and " << 3 << "不相等";
    CAUTION <<3 <<" and " << 3 << "不相等";
    CHECK(3==4) << "3与4不相等"<< "3与4不相等"<<3<<4;
    return 0;
}