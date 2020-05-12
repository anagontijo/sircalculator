#ifndef R4_METHOD_H
#define R4_METHOD_H
#include <vector>

class r4_method
{
public:
    r4_method(float _s, float _i, float _r, float _h, float _beta, float _snu);
    float eval_s();
    float eval_i();
    float eval_r();

    std::vector<float> eval();
private:
    float s;
    float i;
    float r;
    float h;
    float beta;
    float nu;
};

#endif // R4_METHOD_H
