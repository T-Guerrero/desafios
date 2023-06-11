#include <iostream>
#include <math.h>
#include <vector>
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

int main() {
    int n;
    long long x, y, twoTimesArea = 0;
    vector<Point> points;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    points.push_back(points[0]);

    for (int i = 0; i < n; i++) {
        twoTimesArea += (points[i].x * points[i + 1].y);
        twoTimesArea -= (points[i + 1].x * points[i].y);
    }

    cout << abs(twoTimesArea) << endl;

    return 0;
}