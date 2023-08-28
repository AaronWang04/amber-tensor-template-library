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
template <typename Device, int dimension>
struct Tensor: public expr::Exp<Tensor<Device, dimension>>{

    bool isCPU = true;
    // data pointer
    float *dptr_ = nullptr;
    Shape<dimension> shape_;
    size_t stride_;

    // Default constructor
    Tensor(void) {};
    Tensor(float *dptr) : dptr_(dptr){};
    Tensor(const Shape<dimension> &shape) : shape_(shape), stride_(shape[dimension-1]){};
    Tensor(float *dptr, const Shape<dimension> &shape) : dptr_(dptr), shape_(shape), stride_(shape[dimension-1]){};
    Tensor(float*dptr, const Shape<dimension> &shape, size_t stride) : dptr_(dptr), shape_(shape), stride_(stride){};


    inline size_t size(void) const{
        size_t size = this->shape_[0];
        #pragma unroll
        for (int i = 1; i < shape_.dimension; ++i) { size *= this->shape_[i]; }
        return size;
    }

    inline size_t size(size_t idx) const{
        return shape_[idx];
    }
    
    // return memory size of the tensor, starting startdim
    template<int startdim>
    inline size_t MemSize(void) const {
        size_t memsz = this->stride_;
        #pragma unroll
        for (int i = startdim; i < shape_.kSubdim; ++i) {
            memsz *= this->shape_[i];
        }
        return memsz;
    }

    inline Tensor<Device, dimension - 1> operator[](size_t idx) const {
        return Tensor<Device, dimension-1>(dptr_ + this->MemSize<1>() * idx, shape_.SubShape(), stride_);
    }

    // Assignment of same type
    inline Tensor<Device, dimension> operator=(const Tensor<Device, dimension> &exp) {
        dptr_ = exp.dptr_;
        shape_ = exp.shape_;
        stride_ = exp.stride_;
        return *this;
    }

    template<typename E>
    inline Tensor<Device, dimension> operator=(const expr::Exp<E> &exp){
        return this->__assign(exp);
    }

    inline Tensor<Device, dimension> operator=(const float &exp){
        return this->__assign(exp);
    }


};

// A 1d tensor for a different implementation of operator[] (TvT there is no good way)
// differentiated by having no dimension
template <typename Device>
struct Tensor<Device, 1> : public expr::Exp<Tensor<Device, 1>>{

    bool isCPU = true;
    // data pointer
    float *dptr_ = nullptr;
    Shape<1> shape_;
    size_t stride_;

    Tensor(float *dptr, Shape<1> shape, size_t stride) : dptr_(dptr), shape_(shape), stride_(stride){}

    inline float &operator[](size_t idx) {
        return dptr_[idx];
    }
    
    inline const float &operator[](size_t idx) const {
        return dptr_[idx];
    }

};

}
#endif