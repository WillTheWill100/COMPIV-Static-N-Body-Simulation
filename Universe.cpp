// Copyright[2023]<William King>
#include "Universe.hpp"

// setters
void Universe::setRadius(const float newRad) { radius = newRad; }

// getters
float Universe::getRadius() const { return radius; }
std::vector<std::shared_ptr<CelestialBody>> Universe::getCelestialBodies() const {
    return celestialBodies;
}

std::istream& operator>>(std::istream& in, Universe& universe) {
    int n;
    double r;
    in >> n >> r;
    if (r <= 0.0) {
        std::cerr << "Error: Invalid radius for the universe." << std::endl;
        return in;
    }
    universe.setRadius(r);
    for (int i = 0; i < n; ++i) {
        std::shared_ptr<CelestialBody> body = std::make_shared<CelestialBody>();
        in >> *body;
        universe.addCelestialBody(body);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
    out << universe.getCelestialBodies().size() << '\n';
    out << universe.getRadius() << '\n';
    const std::vector<std::shared_ptr<CelestialBody>>& bodies = universe.getCelestialBodies();
    for (const auto& body : bodies) {
        out << *body << '\n';
    }
    return out;
}

void Universe::addCelestialBody(std::shared_ptr<CelestialBody> body) {
    celestialBodies.push_back(body);
}

void Universe::update(float dt) {
    for (auto& body : celestialBodies) {
        sf::Vector2f velocity = body->getVel();
        sf::Vector2f newPosition = body->getPos() + velocity * dt;
        body->setPos(newPosition);
    }
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    for (const auto& body : celestialBodies) {
        window.draw(*body, states);
    }
}
