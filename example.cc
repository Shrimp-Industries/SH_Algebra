#include <iostream>
#include <vector>

#include "algebra.hpp"

using namespace SH;

int main(){

    ALG::LinkedPoint<float> p1(0.0, 0.0, 1);
    ALG::LinkedPoint<float> p2(1.0, 1.0, 2);
    ALG::LinkedPoint<float> p3(2.0, 0.0, 3);

    ALG::Triangle<float> tri(p1, p2, p3);

    // If logger module included, swap ALG:: for LOG::
    ALG::LogLn(p1);
    ALG::LogLn(p2);
    ALG::LogLn(p3);
    ALG::Log("3-point angle: ");
    ALG::LogLn(tri.GetAngle());

    return 0;
}
