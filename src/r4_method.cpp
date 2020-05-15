#include "../include/r4_method.h"

r4_method::r4_method(float _s,
                     float _i,
                     float _r,
                     float _h,
                     float _beta,
                     float _nu) {
  s = _s;
  i = _i;
  r = _r;
  h = _h;
  beta = _beta;
  nu = _nu;
}

float r4_method::eval_s() {
  float f1 = -beta * s * i;
  float f2 = -beta * (s + (h / 2) * f1) * i;
  float f3 = -beta * (s + (h / 2) * f2) * i;
  float f4 = -beta * (s + h * f3) * i;

  return s + (h / 6) * (f1 + 2 * f2 + 2 + f3 + f4);
}

float r4_method::eval_i() {
  float f1 = beta * s * i - nu * i;
  float f2 = beta * s * (i + (h / 2) * f1) - nu * (i + (h / 2) * f1);
  float f3 = beta * s * (i + (h / 2) * f2) - nu * (i + (h / 2) * f2);
  float f4 = beta * s * (i + h * f3) - nu * (i + h * f3);

  return i + (h / 6) * (f1 + 2 * f2 + 2 + f3 + f4);
}

float r4_method::eval_r() {
  return i + h * nu * i;
}

std::vector<float> r4_method::eval() {
  return std::vector<float>{eval_s(), eval_i(), eval_r()};
}
