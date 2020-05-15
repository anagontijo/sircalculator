#ifndef SIR_METHOD_H
#define SIR_METHOD_H

#include <vector>

class SIR_method {
 public:
  SIR_method();

  // S is the vector in time for susceptible people
  std::vector<float> S;

  // I is the vector in time for infectious people
  std::vector<float> I;

  // R is the vector in time for recovered people
  std::vector<float> R;

  // V is the vector in time for vaccinated people
  std::vector<float> V;

  // D is the vector in time for dead people
  std::vector<float> D;

  // Beta represents the infection rate
  float beta;

  // Nu represents the recovery rate
  float nu;

  // Rho represents the vaccination rate
  float rho;

  // Mi represents the death rate
  float mi;
};

#endif  // SIR_METHOD_H
