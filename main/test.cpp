#include "default_include.hpp"
#include "amber_include.hpp"
#include "tensor.hpp"

int main(void)
{


    float data[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    amber::Tensor<cpu, 2> ts;
    ts.dptr_ = data;
    ts.shape_ = Shape2(3, 2);
    ts.stride_ = 3;
    
    for (size_t i = 0; i < ts.size(0); ++i)
    {
        for (size_t j = 0; j < ts.size(1); ++j)
        {   
            printf("ts[%u][%u]=%f\n", i, j, ts[i][j]);
        }
    }

    

    return 0;
}