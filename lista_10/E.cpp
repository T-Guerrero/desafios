#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
using namespace std;

using Coord = double;

const double EPS = 1e-9;

int sign(Coord x) { return (x > EPS) - (x < -EPS); }

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

ostream& operator<<(ostream& os, Point p) {
    return os<<"("<<p.x<<","<<p.y<<")";
}

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

// Point.rot(ccw90) eh equivalente a rotacionar 
// o ponto 90 graus em sentido anti-horario
Point ccw90(1,0);

struct Circle {
    Point o; Coord r;
    Circle() {}
    Circle(Point o, Coord r) : o(o), r(r) {}

    // checa se as circunferencias se intersectam
    bool intersect(Circle c) {
        return ((sign((o-c.o).norm() - (r+c.r)) <= 0) and 
                (sign((o-c.o).norm() - fabs(r-c.r)) >= 0)); 
    }

    bool contains(Point p){ return (o-p).norm()-r*r <= 0; }

    bool in(Circle c){ 
        double d = (o-c.o).norm();
        return d+r - c.r <= 0; 
    }

    // devolve os pontos de interseccao entre um circulo e uma reta
    vector<Point> operator^(Line l) {
        Coord d = l.dist(o);
        if(sign(d-r) > 0) return {};
        Point proj = l.proj(o);
        if(sign(d-r) == 0) return {proj}; 
        Point aux = (l.v.perp()/l.v.norm()) * sqrt(r*r-d*d);
        return {proj+aux, proj-aux};
    }

    // devolve os pontos de interseccao entre dois circulos
    vector<Point> operator^(Circle c){
        Coord d = (o-c.o).norm();
        if(intersect(c)) return {};
        Coord x = (d*d - c.r*c.r + r*r) / (2*d),
              y = sqrt(r*r - x*x);
        Point v = (c.o-o)/d;
        vector<Point> inter;
        inter.push_back(o + v*x - v.rot(ccw90)*y);
        if(y>EPS) inter.push_back(o+v*x+v.rot(ccw90)*y);
        return inter;
    }
};

double distance(Point p1, Point p2) {
    // Calculating distance
    return sqrt((double) pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

int main() {
    Coord r, xc, yc, x1, y1, x2, y2;

    cin >> r >> xc >> yc >> x1 >> y1 >> x2 >> y2;

    Circle circle(Point(xc, yc), r);
    Line line(Point(x1, y1), Point(x2, y2));
    vector<Point> intersections = circle^line;

    if (intersections.size() >= 2) {
        cout << setprecision(5) << fixed << distance(intersections[0], intersections[1]) << endl;
    } else {
        cout << (intersections.size() == 0 ? -1 : 0) << endl;
    }

    return 0;
}