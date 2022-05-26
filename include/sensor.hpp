#ifndef SENSOR_H
#define SENSOR_H
#include <SFML/Graphics.hpp>
class  sensor
{
private:
    float size;
    sf::CircleShape sensorLeft;
    sf::CircleShape sensorRight;
    sf::CircleShape sensorCenter; 
    sf::Vector2f centerVec;
    sf::Vector2f leftVec;
    sf::Vector2f rightVec;
    
    void buildSensor();     
    void setPos(sf::Vector2f pos);
public:
     sensor(sf::Vector2f antPos, float rotation);
     
    ~ sensor();

    void update(sf::Vector2f pos,float orientation);
    void render(sf::RenderTarget &target);
};
#endif