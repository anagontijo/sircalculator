#include "r4_method.h"

using namespace SIR_types;

R4Method::R4Method(float beta,
                   float nu,
                   float lambda,
                   float alpha,
                   float gamma) {
  _beta = beta;
  _nu = nu;
  _lambda = lambda;
  _alpha = alpha;
  _gamma = gamma;
}

float R4Method::f_s(std::map<type, float> args) {
  return -this->_beta * args[S] * args[I] + this->_gamma * args[I] -
         this->_lambda * args[S];
}

float R4Method::f_i(std::map<type, float> args) {
  return this->_beta * args[S] * args[I] - this->_gamma * args[I] -
         this->_nu * args[I] - this->_alpha * args[I];
}

float R4Method::f_r(std::map<type, float> args) {
  return this->_nu * args[I];
}

float R4Method::f_v(std::map<type, float> args) {
  return this->_lambda * args[S];
}

float R4Method::f_d(std::map<type, float> args) {
  return this->_alpha * args[I];
}

float R4Method::f(type _type, std::map<type, float> args) {
  switch (_type) {
    case S:
      return f_s(args);
      break;
    case I:
      return f_i(args);
      break;
    case R:
      return f_r(args);
      break;
    case V:
      return f_v(args);
      break;
    case D:
      return f_d(args);
      break;
  }
}

float R4Method::eval(type _type, std::map<type, float> args) {
  std::map<type, float> aux_args = args;
  float f1 = f(_type, aux_args);
  aux_args[_type] += (_t / 2) * f1;
  float f2 = f(_type, aux_args);
  aux_args = args;
  aux_args[_type] += (_t / 2) * f2;
  float f3 = f(_type, aux_args);
  aux_args = args;
  aux_args[_type] += _t * f3;
  float f4 = f(_type, aux_args);

  return args[_type] + (_t / 6) * (f1 + (2 * f2) + (2 * f3) + f4);
}

void R4Method::set_rate(rate rate, double value) {
  switch (rate) {
    case i:
      _beta = value;
      break;
    case r:
      _nu = value;
      break;
    case v:
      _lambda = value;
      break;
    case d:
      _alpha = value;
      break;
    default:
      break;
  }
}
