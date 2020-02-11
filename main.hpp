#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include "tree.hpp"

//#define CATCH_CONFIG_RUNNER
#include "./tests/catch.hpp"


using namespace std;

int pipelined_func();
bool is_invalid(Rectangle a, Rectangle b);
bool in_range(float x, float r1, float r2);
bool inclusive_in_range(float x, float r1, float r2);
bool three_identical_bool(bool a, bool b, bool c, bool d, bool val);
bool check_bool_pattern(bool a, bool b, bool c, bool d);
bool is_touching(float x, float y, Rectangle a);
bool is_overlap(bool c1, bool c2, bool c3, bool c4);
void print_rect(Rectangle r);