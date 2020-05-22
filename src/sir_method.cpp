#include "sir_method.h"
#include <QDebug>
#include <algorithm>
#include <map>
SIRMethod::SIRMethod(std::map<QString, float> args) {}

void SIRMethod::setInitialValue(SIR_types::type type, float value) {
  switch (type) {
    case SIR_types::S:
      if (_S[0] == value)
        break;
      _S[0] = value;
      eval();
      break;

    case SIR_types::I:
      if (_I[0] == value)
        break;
      _I[0] = value;
      eval();
      break;
    case SIR_types::total:
      if (_total == value)
        break;
      _total = value;
      eval();
    default:
      break;
  }
}

void SIRMethod::eval() {
  std::map<SIR_types::type, float> args;
  _S[0] = _total - _I[0];
  _R[0] = 0;
  _V[0] = 0;
  _D[0] = 0;
  for (int i = 1; i < _S.size(); i++) {
    args = getArgs(i - 1);
    _S[i] = r4_calculator->eval(SIR_types::S, args);
    _I[i] = r4_calculator->eval(SIR_types::I, args);
    _R[i] = r4_calculator->eval(SIR_types::R, args);
    _V[i] = r4_calculator->eval(SIR_types::V, args);
    _D[i] = r4_calculator->eval(SIR_types::D, args);
    correctTotal(i);
  }
}

std::map<SIR_types::type, float> SIRMethod::getArgs(int index) {
  std::map<SIR_types::type, float> args;
  args[SIR_types::S] = _S[index];
  args[SIR_types::I] = _I[index];
  args[SIR_types::R] = _R[index];
  args[SIR_types::V] = _V[index];
  args[SIR_types::D] = _D[index];
  return args;
}

void SIRMethod::correctTotal(int index) {
  float proportion =
      _total / (_S[index] + _I[index] + _R[index] + _V[index] + _D[index]);
  _S[index] = _S[index] * proportion;
  _I[index] = _I[index] * proportion;
  _R[index] = _R[index] * proportion;
  _V[index] = _V[index] * proportion;
  _D[index] = _D[index] * proportion;
}

void SIRMethod::setArgs(std::map<QString, float> args) {
  int Total = args[SIR_types::toString(SIR_types::total)];
  int I = args[SIR_types::toString(SIR_types::I)];
  int total_time = args[SIR_types::toString(SIR_types::totalTime)];
  float intervals_size = 0.5;
  int num_of_intervals = total_time / intervals_size;
  _S = QVector<float>(num_of_intervals + 1);
  _I = QVector<float>(num_of_intervals + 1);
  _R = QVector<float>(num_of_intervals + 1);
  _V = QVector<float>(num_of_intervals + 1);
  _D = QVector<float>(num_of_intervals + 1);
  _total = Total;
  _I[0] = I;
  _S[0] = Total - _I[0];
  float beta = args[SIR_types::toString(SIR_types::i)];
  float nu = args[SIR_types::toString(SIR_types::r)];
  float lambda = args[SIR_types::toString(SIR_types::v)];
  float alpha = args[SIR_types::toString(SIR_types::d)];
  float gamma = args[SIR_types::toString(SIR_types::n)];
  r4_calculator = new R4Method(beta, nu, lambda, alpha, gamma);
}

std::map<SIR_types::type, QVector<float>> SIRMethod::getResults() {
  std::map<SIR_types::type, QVector<float>> results;
  results[SIR_types::S] = _S;
  results[SIR_types::I] = _I;
  results[SIR_types::R] = _R;
  results[SIR_types::V] = _V;
  results[SIR_types::D] = _D;
  return results;
}

std::map<QString, float> SIRMethod::getResultsInfo() {
  std::map<QString, float> results;
  int end_iteration = _I.size();
  float i_max = 0;
  for (int i = 0; i < _I.size(); i++) {
    if (_I[i] < 1 && end_iteration == _I.size()) {
      end_iteration = i;
    }
    i_max = std::max(i_max, _I[i]);
  }
  results[QString("Max I")] = i_max;
  if (end_iteration < _S.size()) {
    results[QString("Not infected")] = _V[end_iteration] + _S[end_iteration];
    results[QString("Alive after")] = _total - _D[end_iteration];
    results[QString("Duration")] = end_iteration * 0.5;
  } else {
    results[QString("Not infected")] = -1;
    results[QString("Alive after")] = -1;
    results[QString("Duration")] = -1;
  }
  return results;
}
