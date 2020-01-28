#ifndef SH_ALGEBRA_HPP
#define SH_ALGEBRA_HPP

#include <vector>
#include <math.h>
#include <memory>
#include <fstream>
#include <sstream>

namespace SH{
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
    float GetAngle() const{
        Type dx21 = (p2->x - p1->x);
        Type dy21 = (p2->y - p1->y);
        Type dx32 = (p3->x - p2->x);
        Type dy32 = (p3->y - p2->y);

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
template <typename Type>
struct Line{
public:
    Line(Point<Type> p1_, Point<Type> p2_)
    :   p1(std::make_shared<Point<Type>>(p1_)),
        p2(std::make_shared<Point<Type>>(p2_))
    {};
    Line(LinkedPoint<Type> p1_, LinkedPoint<Type> p2_)
    :   p1(std::make_shared<LinkedPoint<Type>>(p1_)),
        p2(std::make_shared<LinkedPoint<Type>>(p2_))
    {};

    Type GetXDiff() const{
        return fabs(p2->x - p1->x);
    }
    Type GetYDiff() const{
        return fabs(p2->y - p1->y);
    }
    Type GetDistance() const{
        Type dx = GetXDiff();
        Type dy = GetYDiff();
        return sqrt(dx*dx + dy*dy);
    }
    // y = ax + b
    Type GetACoeff() const{
        return ( (p1->y - p2->y)/(p1->x - p2->x) );
    }
    // y = ax + b
    Type GetBCoeff(Type aCoeff) const{
        return ( p1->y - (aCoeff * (p1->x)) );
    }
    LinkedPoint<Type> GetIntersectionLinked(const Line<Type>& other) const{
        Type a1 = GetACoeff();
        Type b1 = GetBCoeff(a1);
        Type a2 = other.GetACoeff();
        Type b2 = other.GetBCoeff(a2);

        Type x = ( (b2 - b1)/(a1 - a2) );
        Type y = ( a1 * x + b1 );
        return LinkedPoint<Type>(x, y, 0);
    }
    Point<Type> GetIntersection(const Line<Type>& other) const{
        Type a1 = GetACoeff();
        Type b1 = GetBCoeff(a1);
        Type a2 = other.GetACoeff();
        Type b2 = other.GetBCoeff(a2);

        Type x = ( (b2 - b1)/(a1 - a2) );
        Type y = ( a1 * x + b1 );
        return Point<Type>(x, y, 0);
    }

    std::shared_ptr<Point<Type>> p1, p2;
};

template <typename T>
using Contour = std::vector<LinkedPoint<T>>;
// -----------------------------------------------------------------------------

}   // ALG
}   // SH

#endif  // SH_ALGEBRA_HPP
