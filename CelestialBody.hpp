// Copyright[2023]<William King>
#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cmath>

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

    // part b stuff
    sf::Vector2f getAcceleration(const std::vector<std::shared_ptr<CelestialBody>>& otherBodies, float G);
    void setAcceleration(const sf::Vector2f& newAcceleration);

private:
    sf::Texture texture;
    sf::Sprite object;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
};

#endif
