#ifndef AMBER_TENSOR_OP
#define AMBER_TENSOR_OP

#include "tensor.hpp"

namespace amber {

namespace op {

    struct mul {
        _XINLINE_ static real_t
        Map(real_t a, real_t b)
        {
            return a * b;
        }
    };

    struct add {
        _XINLINE_ static real_t
        Map(real_t a, real_t b)
        {
            return a + b;
        }
    };

    struct minus {
        _XINLINE_ static real_t
        Map(real_t a, real_t b)
        {
            return a - b;
        }
    };

    struct divide {
        _XINLINE_ static real_t
        Map(real_t a, real_t b)
        {
            return a / b;
        }
    };

}; // namespace op

namespace sv {

    struct saveto {
        _XINLINE_ static void
        Save(real_t& a, real_t& b)
        {
            a = b;
        }
    };

    struct addto {
        _XINLINE_ static void
        Save(real_t& a, real_t& b)
        {
            a += b;
        }
    };

    struct minusto {
        _XINLINE_ static void
        Save(real_t& a, real_t& b)
        {
            a -= b;
        }
    };

    struct multo {
        _XINLINE_ static void
        Save(real_t& a, real_t& b)
        {
            a *= b;
        }
    };

}; // namespace sv

}; // namespace amber
#endif