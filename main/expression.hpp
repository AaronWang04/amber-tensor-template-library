#include "default_include.hpp"
#include "operation.hpp"

#ifndef EXPRESSION
#define EXPRESSION

namespace amber{

namespace expr{

template<typename SubType>
struct Exp{
  // returns const reference of the actual type of this expression
  inline const SubType& self(void) const {
    return *static_cast<const SubType*>(this);
  }
};


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