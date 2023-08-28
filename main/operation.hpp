#include "default_include.hpp"

#ifndef OPERATION
#define OPERATION

// namespace amber::op
namespace amber{ 
    
namespace op {

// binary operators
struct plus{
  inline static float Map(float a, float b) {
    return a + b;
  }
};

struct minus{
  inline static float Map(float a, float b) {
    return a - b;
  }
};

struct mul{
  inline static float Map(float a, float b) {
    return a * b;
  }
};

struct div {
  inline static float Map(float a, float b) {
    return a / b;
  }
};

}

// namespace amber::sv
namespace sv{

// in-place operators
struct saveto{
    inline static void Save(float &a, float&b){
        a = b;
    }
};

struct plusto{
    inline static void Save(float &a, float&b){
        a += b;
    }
};

struct minusto{
    inline static void Save(float &a, float&b){
        a -= b;
    }
};

struct multo{
    inline static void Save(float &a, float&b){
        a *= b;
    }
};

struct divto{
    inline static void Save(float &a, float&b){
        a /= b;
    }
};

}

}
#endif