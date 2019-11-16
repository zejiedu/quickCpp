/********************************************************************************
 *  @author Zejie Du (duzejie@hotmail.com)                                      *
 *  @copyright Copyright (c) 2019                                               *
 *                                                                              *
 ********************************************************************************/
#pragma once


#include <iostream>

struct Dim {
    short d0;  //z
    short d1;  //y
    short d2;  //x
};

struct TDim {
    short d0 = 1;
    short d1 = 1;
    short d2 = 1;
    short d3 = 1;
};

template<class Tin, class Tout>
using Reduce_fun = Tout (Tin * tensor_data, short elimNum, short elimStride);

template<class T>
T reduce_sum_k(short tbDim_z, short tbDim_y, short tbDim_x, Dim tbStrideDim,
    short elimStride, short elimNum, void * tensor_data) {
    int start = tbDim_z * tbStrideDim.d0 + tbDim_y * tbStrideDim.d1 + tbDim_x * tbStrideDim.d2;
    T sum = 0;
    for (short i = 0; i < elimNum; i++) {
        int position = start + i * elimStride;
        sum += *(T*)((char*)tensor_data + position);
    }
    return sum;
}

template<class T, class Tout = T>
Tout sum(T * tensor_data, short elimNum, short elimStride) {
    T sum = (T)0;
    for (short i = 0; i < elimNum; i++) {
        int position = i * elimStride;
        sum += *(T*)((char*)tensor_data + position);
    }
    return (Tout)sum;
}


template<class T, class Tout = T>
Tout mean(T * tensor_data, short elimNum, short elimStride) {
    Tout sum = (Tout)0;
    for (short i = 0; i < elimNum; i++) {
        int position = i * elimStride;
        sum += *(T*)((char*)tensor_data + position);
    }
    return sum/ (Tout)elimNum;
}

template<class T, class Tout = T>
Tout max(T * tensor_data, short elimNum, short elimStride) {
    T max_ = tensor_data[0];
    for (short i = 1; i < elimNum; i++) {
        int position = i * elimStride;
        T tmp = *(T*)((char*)tensor_data + position);
        if (tmp > max_) max_ = tmp;
    }
    return (Tout)max_;
}

template<class T, class Tout = T>
Tout min(T * tensor_data, short elimNum, short elimStride) {
    T min_ = tensor_data[0];
    for (short i = 1; i < elimNum; i++) {
        int position = i * elimStride;
        T tmp = *(T*)((char*)tensor_data + position);
        if (tmp < min_) min_ = tmp;
    }
    return (Tout)min_;
}



template<class T, class Tout = T>
Tout argMax(T * tensor_data, short elimNum, short elimStride) {
    Tout maxIdx = (Tout)0;
    T elimMax = *(T*)((char*)tensor_data );
    for (short i = 1; i < elimNum; i++) {
        int position = i * elimStride;
        T elim= *(T*)((char*)tensor_data + position);
        if (elim > elimMax)
        {
            elimMax = elim;
            maxIdx = i;
        }
    }
    return  maxIdx;
}



template<class T, class Tout = T>
Tout argMin(T * tensor_data, short elimNum, short elimStride) {
    Tout minIdx = (Tout)0;
    T elimMin = *(T*)((char*)tensor_data);
    for (short i = 1; i < elimNum; i++) {
        int position = i * elimStride;
        T elim = *(T*)((char*)tensor_data + position);
        if (elim < elimMin)
        {
            elimMin = elim;
            minIdx = i;
        }
    }
    return  minIdx;
}


template<class T, class Tout >
static void reduce_lmp(Dim tbDim, Dim tbStrideDim, short elimStride,
    short elimNum, void* tensor_data, void* out_data, Reduce_fun<T, Tout> Fun) {
    int idx = 0;
    for (short tbDim_z = 0; tbDim_z < tbDim.d0; tbDim_z++) {

        for (short tbDim_y = 0; tbDim_y < tbDim.d1; tbDim_y++) {

            for (short tbDim_x = 0; tbDim_x < tbDim.d2; tbDim_x++) {

                //((T*)out_data)[idx++] = reduce_sum_k<T>(tbDim_z, tbDim_y, tbDim_x, tbStrideDim,
                //                                        elimStride,  elimNum,  tensor_data);

                int start = tbDim_z * tbStrideDim.d0 + tbDim_y * tbStrideDim.d1 + tbDim_x * tbStrideDim.d2;
                ((Tout*)out_data)[idx++] = Fun((T*)((char*)tensor_data + start), elimNum, elimStride);

                std::cout << " " << ((Tout*)out_data)[idx - 1];
            }
            std::cout << " ]" << std::endl;
        }
        std::cout << " ]" << std::endl;
    }
}


template<class T, class Tout >
Dim reduce(void* tensor_data, TDim tensor_dim, void* out_data, /*short &elimStride,*/ size_t reduce_index, Reduce_fun<T, Tout> Fun) {
    Dim tbDim, tbStrideDim;
    short elimStride;
    short elimSize = sizeof(T);
    short elimNum;
    if (reduce_index == 3) {
        tbDim.d0 = tensor_dim.d0;
        tbDim.d1 = tensor_dim.d1;
        tbDim.d2 = tensor_dim.d2;
        elimStride = 1 * elimSize;
        elimNum = tensor_dim.d3;
        tbStrideDim.d2 = tensor_dim.d3 * elimSize;
        tbStrideDim.d1 = tensor_dim.d3 * tensor_dim.d2 * elimSize;
        tbStrideDim.d0 = tensor_dim.d3 * tensor_dim.d2 * tensor_dim.d1 * elimSize;

    }
    else if (reduce_index == 2) {
        tbDim.d0 = tensor_dim.d0;
        tbDim.d1 = tensor_dim.d1;
        tbDim.d2 = tensor_dim.d3;
        elimStride = tensor_dim.d3 * elimSize;
        elimNum = tensor_dim.d2;
        tbStrideDim.d2 = 1 * elimSize;
        tbStrideDim.d1 = tensor_dim.d3 * tensor_dim.d2 * elimSize;
        tbStrideDim.d0 = tensor_dim.d3 * tensor_dim.d2 * tensor_dim.d1 * elimSize;

    }
    else if (reduce_index == 1) {
        tbDim.d0 = tensor_dim.d0;
        tbDim.d1 = tensor_dim.d2;
        tbDim.d2 = tensor_dim.d3;
        elimStride = tensor_dim.d3 * tensor_dim.d2 * elimSize;
        elimNum = tensor_dim.d1;
        tbStrideDim.d2 = 1 * elimSize;
        tbStrideDim.d1 = tensor_dim.d3 * elimSize;
        tbStrideDim.d0 = tensor_dim.d3 * tensor_dim.d2 * tensor_dim.d1 * elimSize;

    }
    else if (reduce_index == 0) {
        tbDim.d0 = tensor_dim.d1;
        tbDim.d1 = tensor_dim.d2;
        tbDim.d2 = tensor_dim.d3;
        elimStride = tensor_dim.d3 * tensor_dim.d2 * tensor_dim.d1 * elimSize;
        elimNum = tensor_dim.d0;
        tbStrideDim.d2 = 1 * elimSize;
        tbStrideDim.d1 = tensor_dim.d3 * elimSize;
        tbStrideDim.d0 = tensor_dim.d3 * tensor_dim.d2 * elimSize;

    }
    else {
        std::cout << "err!" << std::endl;
    }

    reduce_lmp<T, Tout>(tbDim, tbStrideDim, elimStride,
        elimNum, tensor_data, out_data, Fun);
    return tbStrideDim;
}

