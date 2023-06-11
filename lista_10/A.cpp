#include <iostream>
#include <math.h>
using namespace std;

using coord = long long;

struct Point {
    coord x, y;

    Point() : x(0), y(0) {}
    Point(coord x, coord y) : x(x), y(y) {}

    double norm() { return sqrt(norm2()); }
    coord norm2() { return (*this) * (*this); }

    Point operator+(const Point& rhs) const { return Point(x+rhs.x, y+rhs.y); }
    Point operator-(const Point& rhs) const { return Point(x-rhs.x, y-rhs.y); }
    Point operator*(const coord t) const { return Point(x*t, y*t); }
    Point operator/(const coord t) const { return Point(x/t, y/t); }

    // produto escalar (dot product)
    coord operator*(const Point& rhs) const { return x*rhs.x + y*rhs.y; }

    // produto vetorial (cross product)
    coord operator^(const Point& rhs) const { return x*rhs.y - y*rhs.x; }

    // rotaciona 90 graus em sentido horario
    Point perp(){ return Point(-y, x); }
    Point rot(Point rhs) { return Point((*this)^rhs, (*this)*rhs); }
    Point rot(double ang) { return rot(Point(sin(ang), cos(ang))); }
};

struct Line {
    Point v; // v = q-p
    coord c;

    Line(Point v, coord c) : v(v), c(c) {}
    Line(coord a, coord b, coord c) : v({b,-a}), c(c) {}
    Line(Point p, Point q) : v(q-p), c(v^p) {}

    // > 0: acima, < 0: abaixo, =0: colinear
    coord side(Point p) { return (v^p)-c; }
    coord dist(Point p) { return abs(side(p))/v.norm(); }
    coord dist2(Point p) { return side(p)*side(p)/v.norm2(); }

    Line perp(Point p) { return Line(p, p+v.perp()); }
    Point proj(Point p) { return p - v.perp()*side(p)/v.norm2(); }
};

string pointLocation(Line line, Point point) {
    coord side = line.side(point);

    return (side > 0 ? "LEFT" : (side < 0 ? "RIGHT" : "TOUCH"));
}

int main() {
    long long t, x1, y1, x2, y2, x3, y3;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        
        Point p1(x1, y1), p2(x2, y2), p3(x3, y3);
        Line line(p1, p2);

        cout << pointLocation(line, p3) << endl;
    }

    return 0;
}