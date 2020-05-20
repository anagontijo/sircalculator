#ifndef SIR_METHOD_H
#define SIR_METHOD_H

#include <QVector>
#include "r4_method.h"

class SIRMethod {
 public:
  SIRMethod(int S, int I, int R, int num_of_intervals, int total_time, float beta, float nu, float lambda, float alpha);

  void set_initial_value(SIR_types::type type, float value);

  void eval();

private:

  std::map<SIR_types::type, float> get_args(int index);

  void correct_total(int index);

  // Object from R4 method for calculations
  R4Method* r4_calculator;

  int _total;

  // S is the vector in time for susceptible people
  QVector<float> _S;

  // I is the vector in time for infectious people
  QVector<float> _I;

  // R is the vector in time for recovered people
  QVector<float> _R;

  // V is the vector in time for vaccinated people
  QVector<float> _V;

  // D is the vector in time for dead people
  QVector<float> _D;
};

#endif  // SIR_METHOD_H
