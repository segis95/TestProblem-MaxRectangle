#pragma once
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <sstream>
#include <cassert>
#include <chrono>

// point <x, y>
struct Point{
    bool operator==(const Point& other) const {return (x == other.x) && (y == other.y);}
    int x;
    int y;
};


// rectangle defined by two corner points
struct Rectangle {
    Point top_left;
    Point bottom_right;

    explicit Rectangle(const Point& p1, const Point& p2)
        : top_left(p1), bottom_right(p2) {
        assert (p1.x <= p2.x);
        assert (p1.y <= p2.y);
    }

    int64_t area() const {
        return (int64_t) (bottom_right.x - top_left.x + 1) * (bottom_right.y - top_left.y + 1);
    }

    bool check_all_ones(std::vector<std::vector<bool>>& matrix){
        for (int i = top_left.y; i < bottom_right.y + 1; i++){
            for (int j = top_left.x; j < bottom_right.x + 1; j++){
                if (!matrix[i][j]) return false;
            }
        }
        return true;
    }
};

void update_max_submatrix(int& current_mx, Point& upper_left, Point& bottom_right,
        const int candidate_mx, const int x, const int y,
        const int height, const int width);
