
#include "../include/math/q_rsqrt.h"
#include <math.h>
#include <iostream>
using namespace std;

void test_rsqrt()
{
    /*
     * relative error 0.00175235    Mean relative margin of error ::0.000868799  ([0.001*i for i in 1:6400000] )
     * relative error 0.00175235    Mean relative margin of error ::0.000956487  ([0.01*i for i in 1:6400000] )
     */
    float diff_sum = 0;
    float diff_max = 0;
    int count = 6400000;
    for (float i = 1; i <= count; i++)
    {
        float x = i * 0.01;
        float _y = Q_rsqrt(x);
        float y_gt = 1 / sqrt(x);
        float diff = (_y - y_gt) / y_gt;
        diff_sum += abs(diff);

        if (abs(diff) > diff_max)
        {
            diff_max = abs(diff);
        }
    }

    cout << "diff_max " << diff_max;
    cout << "   arg diff :" << diff_sum / count << endl;
}

void test_reciprocal()
{
    /*
     * relative error 0.00350153    Mean relative margin of error :::0.00173679  ([0.001*i for i in 1:6400000] )
     * relative error 0.00350159    Mean relative margin of error ::0.00191083  ([0.01*i for i in 1:6400000] )
     */
    float diff_sum = 0;
    float diff_max = 0;
    int count = 6400000;
    for (float i = 1; i <= count; i++)
    {
        float x = i * 0.001;
        float _y = Q_reciprocal(x);
        float y_gt = 1 / (x);
        float diff = (_y - y_gt) / y_gt;
        diff_sum += abs(diff);

        if (abs(diff) > diff_max)
        {
            diff_max = abs(diff);
        }
    }

    cout << "diff_max " << diff_max;
    cout << "   arg diff :" << diff_sum / count << endl;
}

int main()
{
    test_rsqrt();
    test_reciprocal();
    return 0;
}
