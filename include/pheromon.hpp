#ifndef PHERAMON_H
#define PHERAMON_H
#include <SFML/Graphics.hpp>
#include <chrono>
enum pheromon_types{
    home_pheromon,
    food_pheromon,
};
class pheromon
{
private:
    static int PHEROMON_COUNT;
    static int PHEROMON_STRENGTH;
    sf::CircleShape shape;
    float dropTime;
    sf::Clock * antsClock;
    pheromon_types type;
    void set_color(pheromon_types type);
    
public:
    pheromon();
    pheromon(pheromon_types type, sf::Vector2f position, float dropTime,sf::Clock * antsClock);
    ~pheromon();
    void update();
    sf::Vector2f get_position();
    double get_strength();
    sf::FloatRect get_globalBounds();
    void render(sf::RenderTarget &target);
};
#endif

