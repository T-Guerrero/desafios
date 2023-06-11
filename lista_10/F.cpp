#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <float.h>
using namespace std;

using Coord = double;

struct Point {
    Coord x, y;

    Point() : x(0), y(0) {}
    Point(Coord x, Coord y) : x(x), y(y) {}

    double norm() { return sqrt(norm2()); }
    Coord norm2() { return (*this) * (*this); }

    Point operator+(const Point& rhs) const { return Point(x+rhs.x, y+rhs.y); }
    Point operator-(const Point& rhs) const { return Point(x-rhs.x, y-rhs.y); }
    Point operator*(const Coord t) const { return Point(x*t, y*t); }
    Point operator/(const Coord t) const { return Point(x/t, y/t); }

    // produto escalar (dot product)
    Coord operator*(const Point& rhs) const { return x*rhs.x + y*rhs.y; }

    // produto vetorial (cross product)
    Coord operator^(const Point& rhs) const { return x*rhs.y - y*rhs.x; }

    // rotaciona 90 graus em sentido horario
    Point perp(){ return Point(-y, x); }
    Point rot(Point rhs) { return Point((*this)^rhs, (*this)*rhs); }
    Point rot(double ang) { return rot(Point(sin(ang), cos(ang))); }
};

struct Line {
    Point v; // v = q-p
    Coord c;

    Line(Point v, Coord c) : v(v), c(c) {}
    Line(Coord a, Coord b, Coord c) : v({b,-a}), c(c) {}
    Line(Point p, Point q) : v(q-p), c(v^p) {}

    // > 0: acima, < 0: abaixo, =0: colinear
    Coord side(Point p) { return (v^p)-c; }
    Coord dist(Point p) { return abs(side(p))/v.norm(); }
    Coord dist2(Point p) { return side(p)*side(p)/v.norm2(); }

    Line perp(Point p) { return Line(p, p+v.perp()); }
    Point proj(Point p) { return p - v.perp()*side(p)/v.norm2(); }
};

double distance(Point p1, Point p2) {
    // Calculating distance
    return sqrt((double) pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

Coord dot(Line l1, Line l2) {
    // Dot product
    return (l1.v * l2.v);
}

// returns the distance from p to the line segment ab defined by two points a and b
// the closest Point is stored in the 4th parameter
double distToLineSegment(Point p, Point a, Point b, Point &c) {
    Line ap(a, p), ab(a, b);

    double u = dot(ap, ab) / ab.v.norm2();
    if (u < 0.0) {
        c = Point(a.x, a.y); // closer to a
        return distance(p, a);
    }
    if (u > 1.0) { 
        c = Point(b.x, b.y); // closer to b
        return distance(p, b);
    }
    
    c = a + (ab.v * u); // translate a to c
    return distance(p, c);
}

int main() {
    int n;
    Coord xm, ym, x, y;

    while(cin >> xm >> ym) {
        Point m(xm, ym);
        cin >> n;

        cin >> x >> y;
        Point p1(x, y), bestPoint;

        double bestDistance = DBL_MAX, distance;
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            Point p2(x, y), c;
            distance = distToLineSegment(m, p1, p2, c);

            if(distance < bestDistance) {
                bestDistance = distance;
                bestPoint = c;
            }

            p1 = p2;
        }

        cout << setprecision(4) << fixed << bestPoint.x << endl;
        cout << setprecision(4) << fixed << bestPoint.y << endl;
    } 

    return 0;
}