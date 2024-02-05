#include "test_MaxRectangle.h"

template<class U>
void AssertEqual(const U& u, const U& v, const std::string& hint = {}) {
  if (!(v == u)) {
      std::ostringstream os;
    os << "Assertion failed: " << u << " != " << v;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw std::runtime_error(os.str());
  }
}

#define ASSERT_EQUAL(x, y) {            \
  std::ostringstream os;                \
  os << #x << " != " << #y << ", "      \
    << __FILE__ << ":" << __LINE__;     \
  AssertEqual(x, y, os.str());          \
}



void test_find_max_submatrix(decltype(find_max_submatrix_maps) solution, std::string file_name,
        bool timer = false){

    std::cout << "Testing on " << file_name << "..." << std::endl;
    std::ifstream tests(file_name);
    if (!tests.is_open()) {
          std::cerr << "Could not open file" << std::endl;
          throw std::runtime_error("Could not open file");
    }
    MyTest my_test;
    int tests_num = 0, correct_tests = 0;

    while(tests >> my_test){
        tests_num++;
        try{
            auto start = std::chrono::steady_clock::now();
            Rectangle result = solution(my_test.matrix);
            auto end = std::chrono::steady_clock::now();
            if (timer){std::cout << "Time elapsed " <<
                std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;}
            std::cout << "Test " << tests_num << " " << result.top_left << result.bottom_right << std::endl;
            ASSERT_EQUAL(result.area(), my_test.max_area);
            ASSERT_EQUAL(result.check_all_ones(my_test.matrix), true);
            correct_tests++;

        }catch (std::exception& e) {
            std::cerr << "Test number " << tests_num << " failed: " << e.what() << std::endl;

        }catch (...) {
            std::cerr << "Unknown exception caught" << std::endl;
                throw;

        }
    }
    std::cerr << correct_tests << " / " << tests_num << " tests passed correctly" << std::endl;

    tests.close();
    return;
}

int main(){
    // A Bunch of Small Tests
    test_find_max_submatrix(find_max_submatrix_maps, "tests.txt");
    test_find_max_submatrix(find_max_submatrix_stack, "tests.txt");

    // 100x100 (Lower Triangular  Matrix)
    test_find_max_submatrix(find_max_submatrix_maps, "bigger.txt", true); // порядка 150ms
    test_find_max_submatrix(find_max_submatrix_stack, "bigger.txt", true); // порядка 1ms

    // 1000x1000 (Lower Triangular  Matrix)
    test_find_max_submatrix(find_max_submatrix_maps, "huge.txt", true); // порядка 3минут
    test_find_max_submatrix(find_max_submatrix_stack, "huge.txt", true); // порядка 0.1c

    // 1000x1000 (Lower Triangular Random Matrix)
    test_find_max_submatrix(find_max_submatrix_maps, "huge_random.txt", true); // 324ms
    test_find_max_submatrix(find_max_submatrix_stack, "huge_random.txt", true); // 118ms

    return 0;
}
