// Copyright[2023]<William King>
#include "Universe.hpp"

int main(int argc, char* argv[]) {
    int n;
    double r;
    std::cin >> n >> r;
    Universe universe(r);
    sf::Vector2f windowCenter(800.0f / 2.0f, 600.0f / 2.0f);

    sf::Texture backGroundTexture;
    if (!backGroundTexture.loadFromFile("background.gif")) {
        std::cout << "Failed!" << std::endl;
    }
    sf::Sprite backGround;
    backGround.setTexture(backGroundTexture);

    for (int i = 0; i < n; ++i) {
        float xpos, ypos, xvel, yvel, mass;
        std::string texturePath;
        std::cin >> xpos >> ypos >> xvel >> yvel >> mass >> texturePath;
        float scale = 800.0f / (2.0f * r);
        xvel *= scale;
        yvel *= scale;
        xpos = windowCenter.x + xpos * scale;
        ypos = windowCenter.y - ypos * scale;
        std::shared_ptr<CelestialBody> body =
            std::make_shared<CelestialBody>(xpos, ypos, xvel, yvel, mass, texturePath);
        universe.addCelestialBody(body);
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "N-Body Simulation (static)");
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();
        universe.update(dt);

        window.clear();
        window.draw(backGround);
        window.draw(universe);
        window.display();
    }
    return 0;
}
