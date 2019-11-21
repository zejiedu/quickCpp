/**  fast inverse square root
 * @author Zejie Du (duzejie@hotmail.com)
 * @brief  Quake III《雷神之锤III竞技场》
 *       	y = 1/sqrt(x)
 *      	https://blog.csdn.net/heloowird/article/details/21862251
 *      	http://h14s.p5r.org/2012/09/0x5f3759df.html
 * @version 0.1
 * @date 2019-11-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

float Q_rsqrt( float number )
{
	/*
     * relative error 0.00175235    Mean relative margin of error ::0.000868799  ([0.001*i for i in 1:6400000] )
     * relative error 0.00175235    Mean relative margin of error ::0.000956487  ([0.01*i for i in 1:6400000] )
     */
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
 
	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking（对浮点数的邪恶位级hack）
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?（这他妈的是怎么回事？）
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration （第一次牛顿迭代）
    // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed（第二次迭代，可以删除）
 
	return y;
}

float Q_reciprocal( float number ){
	
	unsigned int s = (*(unsigned int*)&number) & 0x80000000;
	unsigned int  t = ((*(unsigned int *)&number) & 0x7fffffff);
	number = *(float *)&t;
	
	
	long i;
	float x2, y;
	const float threehalfs = 1.5F; 
	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking（对浮点数的邪恶位级hack）
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?（这他妈的是怎么回事？）
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration （第一次牛顿迭代）
    // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed（第二次迭代，可以删除）
	y = y*y;
	
	t = (*(unsigned*)&y) | s;
	y = *(float *)&t;	
	
	return y;

}




















