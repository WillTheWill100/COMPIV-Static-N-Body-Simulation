// Copyright[2023]<William King>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include "Universe.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(cb_constructor) {
    CelestialBody body(5.0, 10.0, 15.0, 20.0, 25.0, "earth.gif");
    BOOST_CHECK_CLOSE(body.getPos().x, 5.0, 0.01);
    BOOST_CHECK_CLOSE(body.getPos().y, 10.0, 0.01);
    BOOST_CHECK_CLOSE(body.getVel().x, 15.0, 0.01);
    BOOST_CHECK_CLOSE(body.getVel().y, 20.0, 0.01);
    BOOST_CHECK_CLOSE(body.getMass(), 25.0, 0.01);
}

BOOST_AUTO_TEST_CASE(uni_constructor) {
    Universe universe(69.0);
    BOOST_CHECK_CLOSE(universe.getRadius(), 69.0, 0.01);
    BOOST_CHECK(universe.getCelestialBodies().empty());
}

BOOST_AUTO_TEST_CASE(load_texture_success) {
    CelestialBody body(69.0, 420.0, 77.0, 81.0, 999.0, "venus.gif");
    bool result = body.loadTexture("venus.gif");
    BOOST_CHECK(result == true);
}

BOOST_AUTO_TEST_CASE(load_texture_failure) {
    CelestialBody body(69.0, 420.0, 77.0, 81.0, 999.0, "venus.gif");
    bool result = body.loadTexture("non_existent_texture.gif");
    BOOST_CHECK(result == false);
}
