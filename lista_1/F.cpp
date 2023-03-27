#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

bool triangleFitsRectangle(double width, double triangleSize, double angle) {
    return width >= triangleSize*sin(angle) + triangleSize*cos(angle + M_PI/6);
}

int main() {
    int A, B;
    double height, width, start = 0.0, end = M_PI/6, mid, triangleSize, result;
    double error = 10e-12;

    cin >> A >> B;

    height = A > B ? B : A;
    width = A > B ? A : B;

    while(abs(start - end) >= error) {
        mid = (start + end)/2.0;

        // hypotenuse
        triangleSize = height / cos(mid);

        if (triangleFitsRectangle(width, triangleSize, mid)) {
            result = triangleSize;
            start = mid;
        } else {
            end = mid;
        }
    }

    result = height / cos(start);

    cout << fixed << setprecision(20) << result << endl;
    
    return 0;
}