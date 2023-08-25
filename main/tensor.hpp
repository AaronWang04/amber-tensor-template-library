#include "shape.hpp"
#include "device.hpp"

template <typename Device, int dimension>
struct Tensor
{

public:
    static const bool kDevCPU = Device::kDevCPU;
    Shape<dimension> shape_;
    size_t stride_;
    Stream<Device> *stream_;

    float *dptr_ = nullptr;

    // constructors
    Tensor(void) : stream_(NULL) {}
    Tensor(const Shape<dimension> &shape) : shape_(shape), stream_(NULL) {}
    Tensor(float *dptr, const Shape<dimension> &shape) : dptr_(dptr), shape_(shape), stride_(shape[kSubdim]), stream_(NULL) {}
    Tensor(float *dptr, const Shape<dimension> &shape, Stream<Device> *stream)
        : dptr_(dptr), shape_(shape), stride_(shape[kSubdim]), stream_(stream) {}

    Tensor(float *dptr, const Shape<dimension> &shape, size_t stride, Stream<Device> *stream)
        : dptr_(dptr), shape_(shape), stride_(stride), stream_(stream) {}


    void set_stream(Stream<Device> *stream) { this->stream_ = stream; }
    size_t size(index_t idx) const { return shape_[idx]; }


};
