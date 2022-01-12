#include <SFML/Graphics.hpp>
#ifndef FOOD_H
#define FOO_H
class food
{
private:
    sf::CircleShape food_shape;
    bool isTake;
    int posX;
    int posY;
    
public:
    
    food(float x, float y);
    ~food();
    void set_isTake(bool value );
    bool get_isTaken();
    void setPos(float x, float y);
    sf::FloatRect getGlobalBounds();
    void render(sf::RenderTarget &target);
    void update_pos(float x, float y);
};
#endif

