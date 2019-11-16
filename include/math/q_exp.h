/**
 * @file q_exp.h
 * @author Zejie Du (duzejie@hotmail.com)
 * @brief Compact Approximation of the Exponential Function
 * @version 0.1
 * @date 2019-11-01
 * 
 * @copyright Copyright (c) 2019
 * 
 *      Schraudolph N N. A Fast, Compact Approximation of the Exponential Function[J]. Neural Computation, 1999, 11(4):853.
 *      https://blog.csdn.net/shakingWaves/article/details/78450500?locationNum=6&fps=1
 * 
 */

#pragma once

#include <stdio.h>
#include <iostream>

static int isLittleEndian(){
	int a = 1;	
	return (*(char*)&a);
}

double Q_exp(double val)
{
    union {
        struct
        {
            uint32_t i;
            uint32_t j;
        } n;
        double d;
    } v;
    if (isLittleEndian() )
    {
        v.n.j = (1 << 20) * (1.4426950409 * val + 1022.9420151853);
    } else
    {
        v.n.i = (1 << 20) * (1.4426950409 * val + 1022.9420151853);
    }    
    return v.d;
}

float Q_exp(float val)
{
    /*
     * % diff_max 0.0393887 arg diff :0.0152265 ([0.01*i for i in 0:6400] )
     * % diff_max 0.0393742   arg diff :0.0153876 ([0.001*i for i in 0:6400] )
     * % diff_max 0.0393903   arg diff :0.0146068  ([0.0001*i for i in 0:6400] )
     * % diff_max 0.0393903   arg diff :0.0170642  ([0.00005*i for i in 0:6400] )
     */
    union {
        uint32_t i;
        float f;
    } v;
    v.i = (1 << 23) * (1.4426950409 * val + 126.94201519f);
    return v.f;
}

/** Using Faster Exponential Approximation
 * @brief 
 *   https://codingforspeed.com/using-faster-exponential-approximation/
 * @param x 
 * @return float 
 */
float Q_exp2(float x)
{
    /*
     *% diff_max 0.0227558 arg diff ::0.00679041 ([0.01*i for i in 0:6400] )
     *% diff_max 0.00918921   arg diff ::0.00392875 ([0.001*i for i in 0:6400] )
     *% diff_max 0.00789452   arg diff :::0.00390868  ([0.0001*i for i in 0:6400] )     
     */
    x = 1 + x/131072;
    x *= x; //1
    x *= x; //2
    x *= x; //3
    x *= x; //4
    x *= x; //5
    x *= x; //6
    x *= x; //7
    x *= x; //8
    x *= x; //9
    x *= x; //10  2**10 = 1024
    x *= x; //11
    x *= x; //12
    x *= x; //13
    x *= x; //14  2**14 = 16384
    x *= x; // 15 2**15 = 32768
    x *= x; // 16 2**16 = 65536
    x *= x; // 17 2**17 = 131072
    
    return x;
}

float fastExp3(register float x)  // cubic spline approximation
{
    union { float f; int32_t i; } reinterpreter;

    reinterpreter.i = (int32_t)(12102203.0f*x) + 127*(1 << 23);
    int32_t m = (reinterpreter.i >> 7) & 0xFFFF;  // copy mantissa
    // empirical values for small maximum relative error (8.34e-5):
    reinterpreter.i +=
         ((((((((1277*m) >> 14) + 14825)*m) >> 14) - 79749)*m) >> 11) - 626;
    return reinterpreter.f;
}

float fastExp4(register float x)  // quartic spline approximation
{
    union { float f; int32_t i; } reinterpreter;

    reinterpreter.i = (int32_t)(12102203.0f*x) + 127*(1 << 23);
    int32_t m = (reinterpreter.i >> 7) & 0xFFFF;  // copy mantissa
    // empirical values for small maximum relative error (1.21e-5):
    reinterpreter.i += (((((((((((3537*m) >> 16)
        + 13668)*m) >> 18) + 15817)*m) >> 14) - 80470)*m) >> 11);
    return reinterpreter.f;
}