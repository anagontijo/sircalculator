#ifndef R4_METHOD_H
#define R4_METHOD_H
#include <vector>
#include <map>
#include <QString>
#include "sir_types.h"

class R4Method
{
public:
    R4Method(float t, float beta, float nu, float lambda, float alpha);

    float eval(SIR_types::type type, std::map<SIR_types::type, float> args);

    void set_rate(SIR_types::rate rate, double value);
private:

    float f_s(std::map<SIR_types::type, float> args);

    float f_i(std::map<SIR_types::type,float> args);

    float f_r(std::map<SIR_types::type,float> args);

    float f_v(std::map<SIR_types::type,float> args);

    float f_d(std::map<SIR_types::type,float> args);

    float f(SIR_types::type type, std::map<SIR_types::type,float> args);

    // Beta represents the infection rate
    float _beta;

    // Nu represents the recovery rate
    float _nu;

    // Lambda represents the vaccination rate
    float _lambda;

    // Alpha represents the death rate
    float _alpha;

    // Gamma represents the re-suceptibility rate
    float _gamma;

    // t represents the intervals of time between calculations
    float _t;

};

#endif // R4_METHOD_H
