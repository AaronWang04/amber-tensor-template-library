#include "default_include.hpp"
#include "operation.hpp"
#include "shape.hpp"

#ifndef EXPRESSION
#define EXPRESSION

namespace amber{

namespace expr{

// Base level expression, all expression must derive from this one form or another
template<typename SubType>
struct Exp{
// returns const reference of the actual type of this expression
	inline const SubType& self(void) const {
		return *static_cast<const SubType*>(this);
	}
};

// Scalar Expressions
template<typename DType>
struct ScalarExp : public Exp<ScalarExp<Dtype>>{
	DType scalar_;
	ScalarExp(DType scalar) : scalar_(scalar) {}
};

template<typename DType>
inline ScalarExp<DType> scalar(DType s) {
	return ScalarExp<DType>(s);
}

// Basic Tensor expression, inherits 
template <typename Container, typename Device, int dimension>
class TensorExp : public Exp<Container>{
    inline Container &operator+=(const Exp<Container> &exp){

		return *(this->ptrself());
	}

	inline Container &operator-=(const Exp<Container> &exp){

		return *(this->ptrself());
	}

	inline Container &operator*=(const Exp<Container> &exp){
		return *(this->ptrself());
	}

	inline Container &operator/=(const Exp<Container> &exp){

		return *(this->ptrself());
	}

	// check tensor size and then apply in-place operation
	template<typename Saver, typename left, int dim, typename right>
	inline void MapExp(TensorExp<left, Device, dim> *dst, const Exp<right> &exp){
		Shape<dim> leftShape;
		Shape<dim> rightShape;
	}
};

// Binary Expressions
template<typename OP, typename TLhs, typename TRhs>
struct BinaryMapExp: public Exp<BinaryMapExp<OP, TLhs, TRhs> >{
	const TLhs& lhs;
	const TRhs& rhs;
	BinaryMapExp(const TLhs& lhs, const TRhs& rhs) :lhs(lhs), rhs(rhs) {}
	// evaluation function, evaluate this expression at position i
	inline float Eval(int i) const {
		return OP::Map(lhs.Eval(i), rhs.Eval(i));
	}
};

template<typename OP, typename TLhs, typename TRhs>
inline BinaryMapExp<OP, TLhs, TRhs>
F (const Exp<TLhs>& lhs, const Exp<TRhs>& rhs) {
    return BinaryMapExp<OP, TLhs, TRhs>(lhs.self(), rhs.self());
}

template<typename TLhs, typename TRhs>
inline BinaryMapExp<op::plus, TLhs, TRhs>
operator+(const Exp<TLhs>& lhs, const Exp<TRhs>& rhs) {
    return F<op::plus>(lhs, rhs);
}

template<typename TLhs, typename TRhs>
inline BinaryMapExp<op::minus, TLhs, TRhs>
operator-(const Exp<TLhs>& lhs, const Exp<TRhs>& rhs) {
    return F<op::minus>(lhs, rhs);
}

template<typename TLhs, typename TRhs>
inline BinaryMapExp<op::mul, TLhs, TRhs>
operator*(const Exp<TLhs>& lhs, const Exp<TRhs>& rhs) {
    return F<op::mul>(lhs, rhs);
}

template<typename TLhs, typename TRhs>
inline BinaryMapExp<op::div, TLhs, TRhs>
operator/(const Exp<TLhs>& lhs, const Exp<TRhs>& rhs) {
    return F<op::div>(lhs, rhs);
}

}

}

#endif