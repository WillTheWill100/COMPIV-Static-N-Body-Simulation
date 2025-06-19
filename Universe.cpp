// Copyright[2023]<William King>
#include "Universe.hpp"
const float G = 6.67430e-11;
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
    universe.setRadius(r);
    for (int i = 0; i < n; ++i) {
        std::shared_ptr<CelestialBody> body = std::make_shared<CelestialBody>();
        in >> *body;
        universe.addCelestialBody(body);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
    out << universe.getCelestialBodies().size();
    out << universe.getRadius();
    const std::vector<std::shared_ptr<CelestialBody>>& bodies = universe.getCelestialBodies();
    for (const auto& body : bodies) {
        out << *body;
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
// part b stuff
void Universe::step(double seconds) {
    calculateForces();
    for (auto& body : celestialBodies) {
        sf::Vector2f acceleration = body->getAcceleration(celestialBodies, G);
        body->setAcceleration(acceleration);

        // Update positions using new velocities
        sf::Vector2f oldPos = body->getPos();
        sf::Vector2f newPos = oldPos + body->getVel() * static_cast<float>(seconds);
        body->setPos(newPos);
    }
}


void Universe::calculateForces() {
    for (size_t i = 0; i < celestialBodies.size(); i++) {
        sf::Vector2f acceleration(0.0f, 0.0f);

        for (size_t j = 0; j < celestialBodies.size(); j++) {
            if (i != j) {
                sf::Vector2f delta = celestialBodies[j]->getPos() - celestialBodies[i]->getPos();
                float distanceSquared = delta.x * delta.x + delta.y * delta.y;

                // Ensure distance is not too small to avoid division by zero
                if (distanceSquared > 0.001f) {
                    float forceMagnitude = G * celestialBodies[i]->getMass() * celestialBodies[j]->getMass() / distanceSquared;
                    sf::Vector2f force = (forceMagnitude / std::sqrt(distanceSquared)) * delta;
                    acceleration += force / celestialBodies[i]->getMass();
                }
            }
        }

        celestialBodies[i]->setAcceleration(acceleration); // Set the new acceleration
    }
}
void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    for (const auto& body : celestialBodies) {
        window.draw(*body, states);
    }
}