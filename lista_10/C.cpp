#include <iostream>
#include <utility>
using namespace std;

class Land {
    private:
        pair<int, int> lowerLeftCoord;
        pair<int, int> upperRightCoord;
    public:
        Land(int xl, int yl, int xr, int yr) {
            lowerLeftCoord = make_pair(xl, yl);
            upperRightCoord = make_pair(xr, yr);
        }
        bool isInsideTheLand(int x, int y) {
            return (x >= lowerLeftCoord.first && x <= upperRightCoord.first
            && y >= lowerLeftCoord.second && y <= upperRightCoord.second);
        }
};

int main() {
    int t, x1, y1, x2, y2, x, y, m;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        cin >> m;

        Land land(x1, y1, x2, y2);
        cout << "Case " << (i + 1) << ":" << endl;
        for (int j = 0; j < m; j++) {
            cin >> x >> y;
            cout << (land.isInsideTheLand(x, y) ? "Yes" : "No") << endl;
        }
    }

    return 0;
}