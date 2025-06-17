// Copyright[2023]<William King>
#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

class CelestialBody : public sf::Drawable {
 public:
    // constructors
    CelestialBody() : position(0.0, 0.0), velocity(0.0, 0.0), mass(0.0) { }
    CelestialBody(float xpos, float ypos, float xvel,
        float yvel, float m, const std::string& texturePath);
    // getters
    const sf::Texture& getTexture() const;
    sf::Vector2f getPos() const;
    sf::Vector2f getVel() const;
    float getMass() const;

    // setters
    void setPos(const sf::Vector2f& newPos);
    void setVel(const sf::Vector2f& newVel);
    void setMass(const float m);

    friend std::istream& operator>>(std::istream& in, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& out, const CelestialBody& body);

    bool loadTexture(const std::string& imagePath);

 private:
    sf::Texture texture;
    sf::Sprite object;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float mass;
    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
};

#endif
