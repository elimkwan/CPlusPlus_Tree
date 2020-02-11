#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "../main.hpp"
#include "../tree.hpp"

/*
------------------------------------------------------------------------
-------------------------UNIT TESTS for main.cpp------------------------
------------------------------------------------------------------------
*/


SCENARIO( "search tree give correct number of land count", "[tree.cpp]" ) {

    GIVEN( "To inseart a list of rectangles into the tree" ) {
        Tree t;
        Node* node = t.set_root();
        Rectangle r1 (1.0,1.0,10.0,10.0);
        Rectangle r2 (3.0,3.0,4.0,4.0);
        Rectangle r3 (5.0,3.0,6.0,4.0);
        Rectangle r4 (1.5, 1.5,7.0,5.0);
        Rectangle r5 (15.0, 1.0, 20.0, 6.0);

        std::vector<Rectangle> rects = {r1,r2,r3,r4,r5};

        WHEN( "The first rectangle arrives" ) {

            t.insert(node, rects[0]);
            Node* test_r1 = t.root -> children[0];

            THEN( "r1 set as the children of the root" ) {
                REQUIRE( t.root == node );
                REQUIRE( test_r1 -> data.x1 == rects[0].x1 ); //since all the x1 in rects[] are different, can assume if data in node = rect[n].x1, the data stores that rectangle
            }

            t.insert(node,rects[1]);
            t.insert(node, rects[2]);

            THEN( "Rectangles set as the children of r1" ) {
                REQUIRE( test_r1 -> children[0] -> data.x1 == rects[1].x1 );
                REQUIRE( test_r1 -> children[1] -> data.x1 == rects[2].x1);
            }

            t.insert(node, rects[3]);

            THEN( "Rectangle set as parents of r2,r3 but child of r1" ) {
                REQUIRE( t.root -> children[0] -> children[0] -> data.x1 == rects[3].x1 );
                REQUIRE( t.root -> children[0] -> children[0] -> children[0] -> data.x1 == rects[1].x1 );
                REQUIRE( t.root -> children[0] -> children[0] -> children[1] -> data.x1 == rects[2].x1 );
            }

            t.insert(node, rects[4]);

            THEN( "Rectangle set as siblings of r1" ) {
                REQUIRE( t.root -> children[1]-> data.x1 == rects[4].x1 );
                REQUIRE( t.get_count() == 4 );
            }
        }

    }
}

SCENARIO( "Rectangles with invalid coordinates are given to the tree", "[tree.cpp]" ) {

    GIVEN( "To an invalid incoming rectangle" ) {
        Tree t;
        Node* node = t.set_root();
        Rectangle r1 (10.0,10.0,1.0,1.0);

        WHEN( "Storing invalid rectangle to tree" ) {

            THEN( "Insert func return false when given invalid rectangles" ) {
                REQUIRE( t.insert(node, r1) == 0 );
            }
        }

    }
}

TEST_CASE( "Testing is_invalid function in main.cpp","[main.cpp]"){
    Rectangle a (0.0,0.0,1.0,1.0);
    Rectangle b (10.0,10.0,11.0,11.0);
    REQUIRE(is_invalid(a,b) == false);

    Rectangle c (0.0,0.0,1.0,1.0);
    Rectangle d (0.5,0.5,1.5,1.5);
    REQUIRE(is_invalid(c,d) == true);

    Rectangle e (0.0,0.0,1.0,1.0);
    Rectangle f (1.0,1.0,2.0,2.0);
    REQUIRE(is_invalid(e,f) == true);
}

TEST_CASE( "Testing in_range function in main.cpp","[main.cpp]"){
    REQUIRE(in_range(1,0,2) == true);
    REQUIRE(in_range(2,0,2) == false);
    REQUIRE(in_range(3,0,2) == false);
}

TEST_CASE( "Testing inclusive_in_range function in main.cpp","[main.cpp]"){
    REQUIRE(inclusive_in_range(1,0,2) == true);
    REQUIRE(inclusive_in_range(2,0,2) == true);
    REQUIRE(inclusive_in_range(3,0,2) == false);
}

TEST_CASE( "Testing three_identical_bool function in main.cpp","[main.cpp]"){
    REQUIRE(three_identical_bool(true,true,true,false, true) == true);
    REQUIRE(three_identical_bool(false,false,false,true, false) == true);
    REQUIRE(three_identical_bool(true,false,false,true, false) == false);
}

TEST_CASE( "Testing check_bool_pattern function in main.cpp","[main.cpp]"){
    REQUIRE(check_bool_pattern(true,false,false,true) == true);
    REQUIRE(check_bool_pattern(false,true,true,false) == true);
    REQUIRE(check_bool_pattern(true,true,false,false) == true);
    REQUIRE(check_bool_pattern(false,false,true,true) == true);
    REQUIRE(check_bool_pattern(true,false,true,false) == false);
}

TEST_CASE( "Testing is_touching function in main.cpp","[main.cpp]"){
    Rectangle a (1.0,1.0,2.0,2.0);
    REQUIRE(is_touching(1,1,a) == true);
    REQUIRE(is_touching(2,2,a) == true);
    REQUIRE(is_touching(0,0,a) == false);
}

TEST_CASE( "Testing is_overlap function in main.cpp","[main.cpp]"){
    REQUIRE(is_overlap(false, false, false, true) == false);
    REQUIRE(is_overlap(true, true, true, false) == true);
    REQUIRE(is_overlap(true, false, false, true) == true);
}


int main(int argc, char *argv[])
{
    //MPI_Init(argc, argv);
    int result = Catch::Session().run(argc, argv);
    pipelined_func();
    return result;
}