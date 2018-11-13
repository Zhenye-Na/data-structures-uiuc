/**
 * Created: FA17
 *      By: Jordi Paris Ferrer
 *
 * Modified:
 *      By: 
 */
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <unistd.h>

#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

#include "../drawable.h"
#include "../color.h"
#include "../vector2.h"
#include "../shape.h"
#include "../circle.h"
#include "../triangle.h"
#include "../rectangle.h"
#include "../truck.h"
#include "../flower.h"

// include at bottom to avoid copying includes
#include "catchlib.h"

int probability = 50;
int maxLevel = 50;

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("test_virtual_perim", "[weight=10]")
{
    Vector2 rectangle_center(4,5);
    Rectangle * rectangle = new Rectangle(rectangle_center, color::BLUE,
            32, 32);

    Shape * shape = rectangle;

    int rect_perim = rectangle->perimeter();
    int shape_perim = shape->perimeter();

    delete rectangle;

    REQUIRE(rect_perim == shape_perim);
}

TEST_CASE("test_virtual_area", "[weight=10]")
{
    Vector2 rectangle_center(4,5);
    Rectangle * rectangle = new Rectangle(rectangle_center, color::GREEN,
            47, 47);

    Shape * shape = rectangle;

    int rect_area = rectangle->area();
    int shape_area = shape->area();

    delete rectangle;

    REQUIRE(rect_area == shape_area);
}

/*
VALGRIND_TEST(test_destructor, 20, 20, 10000)
{
    Shape * triangle = new Triangle(color::ORANGE, Vector2(8,7), Vector2(5,5),
            Vector2(9,9));
    delete triangle;

    PASS;
}
*/

TEST_CASE("test_constructor", "[weight=20]")
{
    Circle circle(Vector2(26,26), color::ORANGE, 3);

    REQUIRE(circle.color().h == color::ORANGE.h);

    REQUIRE(circle.color().s == color::ORANGE.s);

    REQUIRE(circle.color().l == color::ORANGE.l);
}

/*
VALGRIND_TEST(test_drawable_destructor, 10, 10, 10000)
{
    Drawable * truck = new Truck(Vector2(123,456));
    delete truck;

    PASS;
}
*/

TEST_CASE("test_truck_draw", "[weight=10]")
{
    PNG canvas;
    canvas.resize(128, 128);

    PNG soln;

    Drawable * truck = new Truck(Vector2(64, 64));
    truck->draw(&canvas);

    soln.readFromFile("soln_truck.png");

    delete truck;

    //REQUIRE(canvas == soln);
    compare_and_report(canvas, soln);
}

TEST_CASE("test_slicing", "[weight=20]")
{
    PNG canvas;
    canvas.resize(128,128);

    PNG soln;
    PNG soln_old;
    soln.readFromFile("soln_flower.png");
    //soln_old.readFromFile("soln_flower_old.png");

    Drawable * flower = new Flower(Vector2(64,64));

    flower->draw(&canvas);

    delete flower;

    compare_and_report(canvas, soln);

}

/*
VALGRIND_TEST(test_flower_destructor, 10, 10, 10000)
{
    Drawable * flower = new Flower(Vector2(64,64));
    delete flower;

    PASS; 
}
*/

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
///////////////////////// End of Tests /////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    srand(time(NULL));

    if (argc == 1)
    {
        // put our beloved quotes
        print_quote("tests/quotes.txt");
    }

    // so we don't have to prepend tests/ to all the paths above
    chdir("tests");

    int result = Catch::Session().run(argc, argv);

    return (result < 0xFF ? result : 0xFF);
}
