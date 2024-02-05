#include "pch.h"
#include "test_MaxRectangle.h"

void gtest_find_max_submatrix(decltype(find_max_submatrix_maps) solution, std::string file_name) {
    std::cout << "Testing on " << file_name << "..." << std::endl;
    std::ifstream tests(file_name);

    if (!tests.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    MyTest my_test;
    while (tests >> my_test) {
        Rectangle result = solution(my_test.matrix);
        ASSERT_EQ(result.area(), my_test.max_area);
        ASSERT_EQ(result.check_all_ones(my_test.matrix), true);
    }

    tests.close();
    return;
}

TEST(MapsSolution, Small_Test) {
    gtest_find_max_submatrix(find_max_submatrix_maps, "tests.txt");
}

TEST(StackSolution, Small_Test) {
    gtest_find_max_submatrix(find_max_submatrix_stack, "tests.txt");
}

TEST(MapsSolution, 100x100_Test) {
    gtest_find_max_submatrix(find_max_submatrix_maps, "bigger.txt");
}

TEST(StackSolution, 100x100_Test) {
    gtest_find_max_submatrix(find_max_submatrix_stack, "bigger.txt");
}

TEST(MapsSolution, 1000x1000_Test) {
    gtest_find_max_submatrix(find_max_submatrix_maps, "huge.txt");
}

TEST(StackSolution, 1000x1000_Test) {
    gtest_find_max_submatrix(find_max_submatrix_stack, "huge.txt");
}

TEST(MapsSolution, 1000x1000_RandomTest) {
    gtest_find_max_submatrix(find_max_submatrix_maps, "huge_random.txt");
}

TEST(StackSolution, 1000x1000_RandomTest) {
    gtest_find_max_submatrix(find_max_submatrix_stack, "huge_random.txt");
}