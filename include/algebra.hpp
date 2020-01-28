#ifndef SH_ALGEBRA_HPP
#define SH_ALGEBRA_HPP

// Comment out to disable additional logging
#define SH_ALGEBRA_LOGGING

#include <vector>
#include <math.h>
#include <memory>
#include <fstream>
#include <sstream>

namespace SH{


// If SH_LOGGER module not included, log to stdout -----------------------------
#ifndef SH_LOGGER
template <typename T>
void Log(const T& entry){
    std::cout << entry;
}
template <typename T>
void LogLn(const T& entry){
    std::cout << entry << std::endl;
}
#endif
// -----------------------------------------------------------------------------


namespace ALG{
// Points and linked points ----------------------------------------------------
template <typename T>
struct Point{
public:
    using Type = T;
    Point(Type x_, Type y_, int idx_):x(x_),y(y_),idx(idx_){};

    std::string ToString() const{
        std::ostringstream ss;
        ss << idx << "[" << x << "," << y << "]";
        std::string s(ss.str());
        return s;
    }
    friend std::ostream& operator <<(std::ostream &o, const Point<T>& p)
    {
        return o << p.ToString();
    }

    Type x, y;
    int idx;
};

template <typename T>
struct LinkedPoint : Point<T>{
public:
    using Type = T;
    using Point<Type>::Point;

    LinkedPoint<Type>* next = this;
};
// -----------------------------------------------------------------------------

// Triangles -------------------------------------------------------------------
template <typename Type>
struct Triangle{
public:
    Triangle(Point<Type> p1_, Point<Type> p2_, Point<Type> p3_)
    :   p1(std::make_shared<Point<Type>>(p1_)),
        p2(std::make_shared<Point<Type>>(p2_)),
        p3(std::make_shared<Point<Type>>(p3_))
    {};
    Triangle(LinkedPoint<Type> p1_, LinkedPoint<Type> p2_, LinkedPoint<Type> p3_)
    :   p1(std::make_shared<LinkedPoint<Type>>(p1_)),
        p2(std::make_shared<LinkedPoint<Type>>(p2_)),
        p3(std::make_shared<LinkedPoint<Type>>(p3_))
    {};
    float GetAngle(){
        Type dx21 = (p2->x-p1->x);
        Type dy21 = (p2->y-p1->y);
        Type dx32 = (p3->x-p2->x);
        Type dy32 = (p3->y-p2->y);

        Type dot = (dx21 * dx32 + dy21 * dy32);

        Type d21 = sqrt(dx21 * dx21 + dy21 * dy21);
        Type d32 = sqrt(dx32 * dx32 + dy32 * dy32);

        Type angle = acos(dot/(d21 * d32));

        return angle * 180.0 / M_PI;
    };

    std::shared_ptr<Point<Type>> p1, p2, p3;
};
// -----------------------------------------------------------------------------

// Lines and contours ----------------------------------------------------------
template <typename T>
using Contour = std::vector<LinkedPoint<T>>;
// -----------------------------------------------------------------------------

}   // ALG
}   // SH

#endif  // SH_ALGEBRA_HPP
