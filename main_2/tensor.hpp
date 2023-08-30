#ifndef AMBER_TENSOR
#define AMBER_TENSOR

// macro definition for inline as CUDA uses a different inline
// inline reduces function call overhead
#ifdef __CUDACC__
  #define _XINLINE_ inline __device__ __host__
#else
  #define _XINLINE_ inline
#endif

// type declaration goes here
// TODO: macro definition for double
namespace amber{
    typedef float real_t;
    typedef unsigned index_t;
};

namespace amber{

template<int dimension>
struct Shape{

	public:
		const static int zMaxShape = dimension;
        const static int zSubShape = dimension - 1;

		_XINLINE_ Shape(void) {}
        _XINLINE_ Shape( const Shape<dimension> &s ){
			#pragma unroll
            for( int i = 0; i < zMaxShape; i ++ ){
                this->shape_[i] = s[i];
            }
            this->stride_ = s.stride_;
        }

		_XINLINE_ index_t& operator[](index_t idx) {
            return shape_[ idx ];
        }

		_XINLINE_ const index_t& operator[](index_t idx) const {
            return shape_[ idx ];
        }

		_XINLINE_ const index_t& stride(void) const {
            return stride_;
        }

		_XINLINE_ bool operator==(const Shape<zMaxShape> &s) const {
            #pragma unroll
            for (int i = 0; i < zMaxShape; i++) {
                if (s.shape_[i] != this->shape_[i]) return false;
            }
            return true;
        }

		_XINLINE_ Shape<2> FlatTo2D(void) const {
            Shape<2> s;
            s.stride_ = this->stride_;
            s.shape_[ 0 ] = this->shape_[ 0 ];
            index_t ymax = 1;

            #pragma unroll
            for (int i = 1; i < zMaxShape; ++i) {
                ymax *= this->shape_[ i ];
            }
            s.shape_[1] = ymax;
            return s;
        }

		_XINLINE_ size_t Size(void) {
            size_t memsz = this->shape_[ 0 ];
            #pragma unroll
            for (int i = 1; i < zMaxShape; ++i) {
                memsz *= this->shape_[ i ];
            }
            return memsz;
        }

		_XINLINE_ size_t MSize(void) const {
            size_t memsz = this->stride_;
            #pragma unroll
            for (int i = 1; i < zMaxShape; ++i) {
                memsz *= this->shape_[ i ];
            }
            return memsz;
        }

		_XINLINE_ Shape<zSubShape> SubShape(void) const {
            Shape<zSubShape> s;
            s.stride_ = this->stride_;
            // for cuda
            #pragma unroll
            for (int i = 0; i < zSubShape; ++i) {
                s.shape_[ i ] = this->shape_[ i ];
            }
            return s;
        }

	public:
		index_t stride_;
		index_t shape_[ zMaxShape ];

};


_XINLINE_ Shape<1> Shape1( index_t s0 ){
	Shape<1> s; s[0] = s0;
	return s;
}

_XINLINE_ Shape<2> Shape2( index_t s1, index_t s0 ){
	Shape<2> s; s[0] = s0; s[1] = s1;
	return s;
}

_XINLINE_ Shape<3> Shape3( index_t s2, index_t s1, index_t s0 ){
	Shape<3> s; s[0] = s0; s[1] = s1; s[2] = s2;
	return s;
}

_XINLINE_ Shape<4> Shape4( index_t s3, index_t s2, index_t s1, index_t s0 ){
	Shape<4> s; s[0] = s0; s[1] = s1; s[2] = s2; s[3] = s3;
	return s;
}

struct cpu{
	const static bool kDevCPU = true;
};

struct gpu{
	const static bool kDevCPU = false;
};

template<typename Device, int dimension>
struct Tensor{

	public:
		// data pointer
		real_t *dptr;
		Shape<dimension> shape;

		// void constructor
		_XINLINE_ Tensor(void) {}
		// constructor from shape
		_XINLINE_ Tensor(const Shape<dimension> &shape): shape(shape) {}
		// constructor from datapointer and shape
		_XINLINE_ Tensor(real_t *dptr, const Shape<dimension> &shape): dptr((real_t*)dptr), shape(shape) {}

		_XINLINE_ Tensor<Device, 2> FlatTo2D(void) const {
            return Tensor<Device, 2>(reinterpret_cast<real_t*> (dptr), shape.FlatTo2D());
        }

		_XINLINE_ Tensor<Device, kSubdim> operator[](index_t idx) const {
            Shape<kSubdim> s = shape.SubShape();
            return Tensor<Device, kSubdim>(reinterpret_cast<real_t*> (dptr) + s.MSize() * idx, s);
        }

		_XINLINE_ Tensor<Device, dimension> Slice(index_t begin, index_t end) const {
            Shape<dimension> s = this->shape;
            s[ dimension - 1 ] = end - begin;
            return Tensor<Device, dimension>(reinterpret_cast<real_t*> (dptr) + s.SubShape().MSize() * begin, s);
        }
};

template <typename Device>
struct Tensor<Device, 1>{
	public:
		real_t *dptr;
        Shape<1> shape;

	public:
		_XINLINE_ Tensor(void) {}
		_XINLINE_ Tensor(real_t *dptr, Shape<1> shape) :dptr(dptr), shape(shape) {}
		_XINLINE_ Tensor<Device, 2> FlatTo2D(void) const {
            return Tensor<Device, 2>(reinterpret_cast<real_t*> (dptr), shape.FlatTo2D());
        }
		_XINLINE_ Tensor<Device, 1> Slice(index_t begin, index_t end) const {
            Shape<1> s;
            s[0] = s.stride_ = end  - begin;
            return Tensor<Device, 1>(reinterpret_cast<real_t*> (dptr) + begin, s);
        }

		_XINLINE_ real_t &operator[](index_t idx) { return dptr[ idx ]; }
		_XINLINE_ const real_t &operator[](index_t idx)const { return dptr[ idx ]; }

};

};

namespace amber{
	typedef Tensor<cpu, 1> CTensor1D;
    typedef Tensor<cpu, 2> CTensor2D;
    typedef Tensor<cpu, 3> CTensor3D;
    typedef Tensor<cpu, 4> CTensor4D;

    typedef Tensor<gpu, 1> GTensor1D;
    typedef Tensor<gpu, 2> GTensor2D;
    typedef Tensor<gpu, 3> GTensor3D;
    typedef Tensor<gpu, 4> GTensor4D;
};

#endif