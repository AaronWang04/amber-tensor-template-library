#include "default_include.hpp"

// struct declarations
template <int ndim>
struct Shape;

template<int dimension>
struct Shape
{
    // dimension of current shape
    static const int kDimension = dimension;
    //dimension of current shape minus one
    static const int kSubdim = dimension - 1;
    // storing the dimension information
    size_t shape_[kDimension];
    // default constructor, do nothing
    Shape(void) {}
    // constuctor
    Shape(const Shape<kDimension> &s)
    {
    #pragma unroll
        for (int i = 0; i < kDimension; ++i)
        {
            this->shape_[i] = s[i];
        }
    }
    /*!
     * \brief get corresponding index
     * \param idx dimension index
     * \return the corresponding dimension size
     */
    size_t &operator[](size_t idx)
    {
        return shape_[idx];
    }
    /*!
     * \brief get corresponding index
     * \param idx dimension index
     * \return the corresponding dimension size
     */
    const size_t &operator[](size_t idx) const
    {
        return shape_[idx];
    }
    /*!
     * \return whether two shape equals
     * \param s the shape to compare against
     */
    bool operator==(const Shape<kDimension> &s) const
    {
        #pragma unroll
        for (int i = 0; i < kDimension; ++i)
        {
            if (s.shape_[i] != this->shape_[i])
                return false;
        }
        return true;
    }
    
    bool operator!=(const Shape<kDimension> &s) const
    {
        return !(*this == s);
    }
    
    Shape<1> FlatTo1D(void) const
    {
        Shape<1> s;
        s[0] = this->Size();
        return s;
    }
    
    Shape<2> FlatTo2D(void) const
    {
        Shape<2> s;
        s.shape_[1] = this->shape_[kDimension - 1];
        size_t ymax = 1;
        #pragma unroll
        for (int i = 0; i < kDimension - 1; ++i)
        {
            ymax *= this->shape_[i];
        }
        s.shape_[0] = ymax;
        return s;
    }
    
    size_t Size(void) const
    {
        size_t size = this->shape_[0];
        #pragma unroll
        for (int i = 1; i < kDimension; ++i)
        {
            size *= this->shape_[i];
        }
        return size;
    }
    
    size_t ProdShape(int dimstart, int dimend) const
    {
        size_t num = 1;
        #pragma unroll
        for (int i = dimstart; i < dimend; ++i)
        {
            num *= this->shape_[i];
        }
        return num;
    }
    
    Shape<kSubdim> SubShape(void) const
    {
        Shape<kSubdim> s;
        // for cuda
        #pragma unroll
        for (int i = 0; i < kSubdim; ++i)
        {
            s.shape_[i] = this->shape_[i + 1];
        }
        return s;
    }
    
    template <int dimstart, int dimend>
    Shape<dimend - dimstart> Slice(void) const
    {
        Shape<dimend - dimstart> s;
        #pragma unroll
        for (int i = dimstart; i < dimend; ++i)
        {
            s[i - dimstart] = this->shape_[i];
        }
        return s;
    }

    template <int dim>
    friend std::ostream &operator<<(std::ostream &os, const Shape<dim> &shape);
};

Shape<1> Shape1(size_t s0) {
  Shape<1> s; s[0] = s0;
  return s;
}

Shape<2> Shape2(size_t s0, size_t s1) {
  Shape<2> s; s[0] = s0; s[1] = s1;
  return s;
}

Shape<3> Shape3(size_t s0, size_t s1, size_t s2) {
  Shape<3> s;
  s[0] = s0; s[1] = s1; s[2] = s2;
  return s;
}