// Copyright[2023]<William King>
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP
#include <vector>
#include <memory>
#include "CelestialBody.hpp"

class Universe : public sf::Drawable {
 public:
     // constructors
     Universe() : radius(0.0) { }
     explicit Universe(double r) : radius(r) { }
     // setters
     void setRadius(const float newRad);

     // getters
     float getRadius() const;
     std::vector<std::shared_ptr<CelestialBody>> getCelestialBodies() const;

     friend std::istream& operator>>(std::istream& in, Universe& universe);
     friend std::ostream& operator<<(std::ostream& out, const Universe& universe);
     void addCelestialBody(std::shared_ptr<CelestialBody> body);
     void update(float dt);

 private:
     double radius;
     std::vector<std::shared_ptr<CelestialBody>> celestialBodies;
     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
