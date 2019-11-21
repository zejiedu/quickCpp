#include <iostream>
#include "../include/reduce.h"
using namespace std;

int main()
{
    short tensor_data[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,-17};
    TDim tensor_dim{2,2,4,1};

    size_t reduce_index=2;

    short out_data[8];
    reduce(tensor_data, tensor_dim , out_data, reduce_index, mean<short,float>);
    cout << "Hello World!" << endl;
    reduce(tensor_data, tensor_dim , out_data, reduce_index, sum<short>);
    cout << "Hello World!" << endl;
    reduce(tensor_data, tensor_dim , out_data, reduce_index, max<short,short>);
    cout << "Hello World!" << endl;
    reduce(tensor_data, tensor_dim , out_data, reduce_index, min<short,short>);
    cout << "Hello World!" << endl;
    reduce(tensor_data, tensor_dim , out_data, reduce_index, argMax<short,short>);
    cout << "Hello World!" << endl;
    return 0;
}
