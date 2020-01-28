#include <iostream>
#include <vector>

#include "algebra.hpp"

using namespace SH;

int main(){

    ALG::LinkedPoint<float> p1(0.0, 0.0, 1);
    ALG::LinkedPoint<float> p2(1.0, 1.0, 2);
    ALG::LinkedPoint<float> p3(2.0, 0.0, 3);

    ALG::Triangle<float> tri(p1, p2, p3);

    // If logger module included, use LOG:: instead
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    std::cout << "3-point angle: " << tri.GetAngle() << std::endl;

    return 0;
}
