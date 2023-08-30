#ifndef TENSOR_EXPR
#define TENSOR_EXPR

#include "tensor.hpp"
#include "tensor_op.hpp"

namespace amber{

namespace expr{

class Exp{
    public:
        _XINLINE_ real_t eval( index_t y, index_t x ) const;
};

class TensorExp: public Exp{
    public:
        TensorExp( const real_t *dptr, index_t stride ) :dptr_(dptr),stride_(stride){}

        template<typename Device, int dim>
        TensorExp(const Tensor<Device,dim> &t ):dptr_(t.dptr), stride_(t.shape.stride_){}

        _XINLINE_ real_t eval( index_t y, index_t x ) const{
            return dptr_[ y * stride_ + x ];
        }
    private:
        const real_t *dptr_;
        index_t stride_;
};

};

};

#endif