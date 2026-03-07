#include "SFML/Graphics/Color.hpp"
#include "engine.h"
#include "particle.h"
#include <SFML/Graphics.hpp>
#include <random>

int main() {
    //init window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "fyzix editor", sf::State::Fullscreen);
    auto [width, height] = window.getSize();
 
    // cartesian view
    sf::View view;
    view.setCenter({0.f, 0.f});
    view.setSize({static_cast<float>(width), -static_cast<float>(height)});
    window.setView(view); 

    //init shapes
    sf::CircleShape particle(2.f);
    particle.setFillColor(sf::Color::White);

    //init text
    sf::Font font("font.ttf");
    sf::Text fps(font);
    fps.setFillColor(sf::Color::Red);
    fps.setPosition({-940,500});
    fps.setCharacterSize(20);
    fps.setScale({1,-1});

    fyzix::particle* shots = new fyzix::particle[100];

    for (fyzix::particle* shot = shots; shot < shots + 100; ++shot) {
        shot->position_ = { 
            static_cast<float>(std::rand() % (width + 1) - width/2.f), 
            static_cast<float>(std::rand() % (height + 1) - height/2.f)
        };
        shot->velocity_ = { 
            static_cast<float>(std::rand() % 101 - 100), 
            static_cast<float>(std::rand() % 101 - 100) 
        };
    } 


    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        float f = 1.f / dt;

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
 
        for (fyzix::particle* shot = shots; shot < shots+100; ++shot) {
            fyzix::engine::step(*shot, 0.0003);
            particle.setPosition({shot->position_.x_, shot->position_.y_});
            window.draw(particle);
        }


        fps.setString(std::format("fps: {}", f));
        window.draw(fps);

        window.display();
    }
    return 0;
}
