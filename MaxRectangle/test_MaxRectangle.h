#pragma once

#include "data_structures.h"
#include "find_max_submatrix_maps.h"
#include "find_max_submatrix_stack.h"

struct MyTest {
    std::vector<std::vector<bool>> matrix;
    int64_t max_area;
};

std::istream& operator>>(std::istream& istr, std::vector<std::vector<bool>>& matrix);


std::istream& operator>>(std::istream& istr, Point& p);

std::ostream& operator<<(std::ostream& ostr, const Point& p);

std::ostream& operator<<(std::ostream& ostr, const Rectangle& r);

std::istream& operator>>(std::istream& istr, MyTest& test);