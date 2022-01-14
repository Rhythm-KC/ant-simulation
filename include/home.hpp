#ifndef HOME_H
#define HOME_H
#include <SFML/Graphics.hpp>
class home
{
private:
    sf::CircleShape homeShape;

public:
    home(float radius, float xCoordinat, float yCoordinate);

    ~home();
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    void render(sf::RenderTarget &target);

};





#endif