
#include <math.h>
#include <iostream>
#include "../include/math/q_exp.h"
using namespace std;

void test_exp()
{
    /*
     * diff_max 0.0393887 arg diff :0.0152265 ([0.01*i for i in 0:6400] )
     * diff_max 0.0393742   arg diff :0.0153876 ([0.001*i for i in 0:6400] )
     * diff_max 0.0393903   arg diff :0.0146068  ([0.0001*i for i in 0:6400] )
     * diff_max 0.0393903   arg diff :0.0170642  ([0.00005*i for i in 0:6400] )
     */
    float diff_sum = 0;
    float diff_max = 0;
    for (size_t i = 0; i < 6400; i++)
    {
        float x = i * 0.012;
        float _y = Q_exp(x);
        float y_gt = exp(x);
        float diff = (_y - y_gt) / y_gt;
        diff_sum += abs(diff);

        if (abs(diff) > diff_max)
        {
            diff_max = abs(diff);
        }
    }

    cout << "diff_max " << diff_max;
    cout << "   arg diff :" << diff_sum / 6400 << endl;
}

void test_exp2()
{
    /*
     * diff_max 0.0227558 arg diff ::0.00679041 ([0.01*i for i in 0:6400] )
     * diff_max 0.00918921   arg diff ::0.00392875 ([0.001*i for i in 0:6400] )
     * diff_max 0.00789452   arg diff :::0.00390868  ([0.0001*i for i in 0:6400] )     
     */
    float diff_sum = 0;
    float diff_max = 0;
    for (size_t i = 0; i < 10000; i++)
    {
        float x = i * 0.001;
        float _y = fastExp3(x);
        float y_gt = exp(x);
        float diff = (_y - y_gt) / y_gt;
        diff_sum += abs(diff);

        if (abs(diff) > diff_max)
        {
            diff_max = abs(diff);
            if (diff_max > 0.03)
            {
                cout << "x" << x << endl;
            }
        }
    }
    cout << "exp2  diff_max " << diff_max;
    cout << "   arg diff :" << diff_sum / 1000 << endl;
}

int main()
{
    test_exp();
    test_exp2();

    return 0;
}
