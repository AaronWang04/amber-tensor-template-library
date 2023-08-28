#include "default_include.hpp"
#include "shape.hpp"
#include "device.hpp"
#include "expression.hpp"

#ifndef TENSOR
#define TENSOR

namespace amber{

/*!
 * \brief General tensor to store floats
 * \tparam Device which device the tensor is on (CPU, GPU)
 * \tparam dimension dimension of the tensor
 */
template <int dimension>
struct Tensor: public expr::Exp<Tensor<dimension>>{

    bool isCPU = true;
    // data pointer
    float *dptr_ = nullptr;
    Shape<dimension> shape_;
    size_t stride_;

    // Default constructor
    Tensor(void) {};
    Tensor(float *dptr) : dptr_(dptr){};
    Tensor(const Shape<dimension> &shape) : shape_(shape){};
    Tensor(float *dptr, const Shape<dimension> &shape) : dptr_(dptr), shape_(shape), stride_(shape[dimension-1]){};

    inline size_t size(void) const{
        size_t size = this->shape_[0];
        #pragma unroll
        for (int i = 1; i < shape_.dimension; ++i) { size *= this->shape_[i]; }
        return size;
    }

    inline size_t size(size_t idx) const{
        return shape_[idx];
    }
    
    template<int startdim>
    inline size_t MemSize(void) const {
        size_t memsz = this->stride_;
        #pragma unroll
        for (int i = startdim; i < shape_.kSubdim; ++i) {
            memsz *= this->shape_[i];
        }
        return memsz;
    }

    inline Tensor<dimension - 1> operator[](size_t idx) const {
        return Tensor<dimension-1>(dptr_ + this->MemSize<1>() * idx, shape_.SubShape());
    }

};

}

#endif