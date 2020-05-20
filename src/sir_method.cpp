#include "sir_method.h"
#include <map>

SIRMethod::SIRMethod(int S, int I, int Total, int num_of_intervals, int total_time, float beta, float nu, float lambda, float alpha){
    _S = QVector<float>(num_of_intervals+1);
    _I = QVector<float>(num_of_intervals+1);
    _R = QVector<float>(num_of_intervals+1);
    _V = QVector<float>(num_of_intervals+1);
    _D = QVector<float>(num_of_intervals+1);
    _total = Total;
    _S[0] = S;
    _I[0] = I;
    r4_calculator = new R4Method(total_time/num_of_intervals, beta, nu, lambda, alpha);
}

void SIRMethod::set_initial_value(SIR_types::type type, float value){
    switch (type) {
    case SIR_types::S:
        if(_S[0] == value)
            break;
        _S[0] = value;
        eval();
        break;

    case SIR_types::I:
        if(_I[0] == value)
            break;
        _I[0] = value;
        eval();
        break;
    case SIR_types::TOTAL:
        if(_total == value)
            break;
        _total = value;
        eval();
    default:
        break;
    }
}

void SIRMethod::eval(){
    std::map<SIR_types::type,float> args;
    for(int i = 1; i < _S.size(); i++){
        args = get_args(i-1);
        _S[i] = r4_calculator->eval(SIR_types::S, args);
        _I[i] = r4_calculator->eval(SIR_types::I, args);
        _R[i] = r4_calculator->eval(SIR_types::R, args);
        _V[i] = r4_calculator->eval(SIR_types::V, args);
        _D[i] = r4_calculator->eval(SIR_types::D, args);
        correct_total(i);
    }
}

std::map<SIR_types::type,float> SIRMethod::get_args(int index){
    std::map<SIR_types::type,float> args;
    args[SIR_types::S] = _S[index];
    args[SIR_types::I] = _I[index];
    args[SIR_types::R] = _R[index];
    args[SIR_types::V] = _V[index];
    args[SIR_types::D] = _D[index];

}

void SIRMethod::correct_total(int index){
    float proportion = (_S[index]+_I[index]+_R[index]+_V[index]+_D[index])/_total;
    _S[index] = _S[index] * proportion;
    _I[index] = _I[index] * proportion;
    _R[index] = _R[index] * proportion;
    _V[index] = _V[index] * proportion;
    _D[index] = _D[index] * proportion;
}
