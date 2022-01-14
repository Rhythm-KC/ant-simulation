#ifndef PHERAMON_H
#define PHERAMON_H
#include <SFML/Graphics.hpp>
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
    int strength;
    pheromon_types type;
    void set_color(pheromon_types type);
    
public:
    pheromon();
    pheromon(pheromon_types type, float posX, float posY);
    ~pheromon();
    void update();
    sf::Vector2f get_position();
    int get_strength();
    void strength_update();
    void render(sf::RenderTarget &target);
};
#endif
