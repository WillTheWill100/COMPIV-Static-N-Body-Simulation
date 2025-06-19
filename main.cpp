// Copyright[2023]<William King>
#include "Universe.hpp"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <T> <∆t>" << std::endl;
        return 1;
    }


    double T = 3.15e7;
    double dt = std::stod(argv[2]);

    int n;
    double r;
    std::cin >> n >> r;
    Universe universe(r);
    sf::Vector2f windowCenter(800.0f / 2.0f, 600.0f / 2.0f);

    // Adjust the time step to slow down the simulation
    dt *= 3;
    sf::Texture backGroundTexture;
    if (!backGroundTexture.loadFromFile("background.gif")) {
        std::cout << "Failed!" << std::endl;
    }
    sf::Sprite backGround;
    backGround.setTexture(backGroundTexture);

    std::vector<std::shared_ptr<CelestialBody>> initialPlanets;

    for (int i = 0; i < n; ++i) {
        float xpos, ypos, xvel, yvel, mass;
        std::string texturePath;
        std::cin >> xpos >> ypos >> xvel >> yvel >> mass >> texturePath;

        // Adjust initial velocities to make planets move slower

        // Adjust initial positions to space planets further apart
        float scale = 800.0f / (2.0f * r);
        xvel *= scale;
        yvel *= scale;
        xpos = windowCenter.x + xpos * scale;
        ypos = windowCenter.y - ypos * scale;

        std::shared_ptr<CelestialBody> body =
            std::make_shared<CelestialBody>(xpos, ypos, xvel, yvel, mass, texturePath);
        universe.addCelestialBody(body);

        initialPlanets.push_back(std::make_shared<CelestialBody>(xpos, ypos, xvel, yvel, mass, texturePath));
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "N-Body Simulation (static)");
    sf::Clock clock;
    double simulationTime = 0.0;
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        universe.step(dt);

        window.clear();
        window.draw(backGround);
        window.draw(universe);
        window.display();

        simulationTime += dt;

        // Repeat the simulation when T is reached
        if (simulationTime >= T) {
            // Reset planet positions and velocities
            for (size_t i = 0; i < static_cast<size_t>(n); ++i) {
                initialPlanets[i]->setPos(initialPlanets[i]->getPos());
                initialPlanets[i]->setVel(initialPlanets[i]->getVel());
            }

            // Print the final state of the universe
            for (const auto& planet : universe.getCelestialBodies()) {
                const sf::Vector2f pos = planet->getPos();
                const sf::Vector2f vel = planet->getVel();
                const float mass = planet->getMass();

                std::cout << std::scientific;
                std::cout << pos.x << " " << pos.y << " ";
                std::cout << vel.x << " " << vel.y << " ";
                std::cout << mass << std::endl;
            }

            return 0; // Exit the program
        }
        }
        return 0;
    }

