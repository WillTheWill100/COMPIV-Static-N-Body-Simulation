// Copyright[2023]<William King>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include "Universe.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testCbConstructor) {
    CelestialBody body(5.0, 10.0, 15.0, 20.0, 25.0, "earth.gif");
    BOOST_CHECK_CLOSE(body.getPos().x, 5.0, 0.01);
    BOOST_CHECK_CLOSE(body.getPos().y, 10.0, 0.01);
    BOOST_CHECK_CLOSE(body.getVel().x, 15.0, 0.01);
    BOOST_CHECK_CLOSE(body.getVel().y, 20.0, 0.01);
    BOOST_CHECK_CLOSE(body.getMass(), 25.0, 0.01);
}

BOOST_AUTO_TEST_CASE(testUniConstructor) {
    Universe universe(69.0);
    BOOST_CHECK_CLOSE(universe.getRadius(), 69.0, 0.01);
    BOOST_CHECK(universe.getCelestialBodies().empty());
}

BOOST_AUTO_TEST_CASE(testLoadTexture) {
    CelestialBody body(69.0, 420.0, 77.0, 81.0, 999.0, "venus.gif");
    bool result = body.loadTexture("venus.gif");
    BOOST_CHECK(result == true);
}

BOOST_AUTO_TEST_CASE(testAddCelestialBody) {
    Universe universe(10.0);
    std::shared_ptr<CelestialBody> body =
    std::make_shared<CelestialBody>(1.0, 2.0, 3.0, 4.0, 5.0, "mars.gif");
    universe.addCelestialBody(body);
    BOOST_CHECK_EQUAL(universe.getCelestialBodies().size(), 1);
    BOOST_CHECK_EQUAL(universe.getCelestialBodies()[0], body);
}

