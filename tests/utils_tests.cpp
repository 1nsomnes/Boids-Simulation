#include "../src/util/utils.hpp"
#include <iostream>

using namespace std;

template<typename T>
bool assert_equal(T t1, T t2) {
  if(t1 == t2) return true; 
  cout << "Test failed";
  return false;
};

void run_utils_tests() {
  cout << "Running util tests" << endl;

  // distance test 
   
  // rotate direction test
  assert_equal(-1.f, utils::rotate_direction(30, 20));
  assert_equal(-1.f, utils::rotate_direction(350, 340));
  assert_equal(-1.f, utils::rotate_direction(170, 160));

  assert_equal(1.f, utils::rotate_direction(20, 30));
  assert_equal(1.f, utils::rotate_direction(350, 353));
  assert_equal(1.f, utils::rotate_direction(170, 182));
   
  // check distance test
  
}

