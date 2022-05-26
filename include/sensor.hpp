#ifndef SENSOR_H
#define SENSOR_H
#include <SFML/Graphics.hpp>
#include "pheromon.hpp"
class  sensor
{
private:
    float size;
    sf::CircleShape sensorLeft;
    sf::CircleShape sensorRight;
    sf::CircleShape sensorCenter; 
    void setOriginandColor(); 
    void buildSensor();     
    void setPos(sf::Vector2f pos);
    sf::Vector2f checkPheromon(std::vector<pheromon> storage);
public:
     sensor(sf::Vector2f antPos, float rotation);
     
    ~ sensor();

    void update(sf::Vector2f pos,float orientation);
    void render(sf::RenderTarget &target);
};
#endif