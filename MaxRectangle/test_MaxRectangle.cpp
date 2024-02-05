#include "test_MaxRectangle.h"

std::istream& operator>>(std::istream& istr, std::vector<std::vector<bool>>& matrix) {
    int m, n;
    istr >> m >> n;
    int num;
    matrix.clear();
    for (int i = 0; i < m; i++) {
        std::vector<bool> els(n, false);
        for (int j = 0; j < n; j++) {
            istr >> num;
            els[j] = (num == 1);
        }
        matrix.push_back(els);
    }
    return istr;
}

std::istream& operator>>(std::istream& istr, Point& p) {
    istr >> p.x >> p.y;
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const Point& p) {
    ostr << '(' << p.x << ", " << p.y << ')';
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const Rectangle& r) {
    ostr << r.top_left << '-' << r.bottom_right;
    return ostr;
}

std::istream& operator>>(std::istream& istr, MyTest& test) {
    istr >> test.matrix >> test.max_area;
    return istr;
}