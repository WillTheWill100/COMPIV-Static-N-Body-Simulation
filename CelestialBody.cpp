// Copyright[2023]<William King>
#include "CelestialBody.hpp"

// constructors
CelestialBody::CelestialBody(float xpos, float ypos, float xvel,
    float yvel, float m, const std::string& image) :
    position(xpos, ypos), velocity(xvel, yvel), mass(m) {
    if (!texture.loadFromFile(image)) {
        std::cout << "Failed to load" << std::endl;
    }
    object.setTexture(texture);
}

// getters
const sf::Texture& CelestialBody::getTexture() const {
    return texture;
}

sf::Vector2f CelestialBody::getPos() const {
    return position;
}

sf::Vector2f CelestialBody::getVel() const {
    return velocity;
}

float CelestialBody::getMass() const {
    return mass;
}

// setters
void CelestialBody::setPos(const sf::Vector2f& newPos) {
    position = newPos;
    object.setPosition(newPos);
}

void CelestialBody::setVel(const sf::Vector2f& newVel) {
    velocity = newVel;
}

void CelestialBody::setMass(const float m) {
    mass = m;
}

std::istream& operator>>(std::istream& in, CelestialBody& body) {
    double xpos, ypos, xvel, yvel, mass;
    std::string image;
    in >> xpos >> ypos >> xvel >> yvel >> mass >> image;
    body.setPos(sf::Vector2f(xpos, ypos));
    body.setVel(sf::Vector2f(xvel, yvel));
    body.setMass(mass);
    if (!body.loadTexture(image)) {
        std::cout << "Failed to load" << std::endl;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
    out << body.getPos().x << ' ' << body.getPos().y << ' ';
    out << body.getVel().x << ' ' << body.getVel().y << ' ';
    out << body.getMass() << ' ';
    out << body.getTexture().copyToImage().getSize().x << ' ';
    out << body.getTexture().copyToImage().getSize().y << ' ';
    return out;
}

bool CelestialBody::loadTexture(const std::string& image) {
    if (texture.loadFromFile(image)) {
        object.setTexture(texture);
        return true;
    }
    return false;
}

// part b stuff
sf::Vector2f CelestialBody::getAcceleration(const std::vector<std::shared_ptr<CelestialBody>>& otherBodies, float G) {
    sf::Vector2f acceleration(0.0f, 0.0f);

    for (const auto& otherBody : otherBodies) {
        if (otherBody.get() != this) {
            sf::Vector2f delta = otherBody->getPos() - position;
            float distanceSquared = delta.x * delta.x + delta.y * delta.y;

            if (distanceSquared > 0.001f) {  // Ensure distance is not too small to avoid division by zero
                float forceMagnitude = (G * otherBody->getMass()) / distanceSquared;
                sf::Vector2f force = forceMagnitude * (delta / std::sqrt(distanceSquared));
                acceleration += force / mass;
            }
        }
    }

    return acceleration;
}
void CelestialBody::setAcceleration(const sf::Vector2f& newAcceleration) {
    acceleration = newAcceleration;
}
void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(object, states);
}
