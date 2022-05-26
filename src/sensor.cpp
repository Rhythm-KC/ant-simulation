#include "../include/sensor.hpp"
#include <cmath>

sensor::sensor(sf::Vector2f antPos, float rotation){
    buildSensor();
    update(antPos,rotation);
}

void sensor::buildSensor(){
    sensorLeft = sf::CircleShape(5);
    sensorCenter= sf::CircleShape(15);
    sensorCenter.setOrigin(sensorCenter.getPosition()/2.f);
    sensorRight= sf::CircleShape(5);
    sensorCenter.setFillColor(sf::Color::Green);
    sensorRight.setFillColor(sf::Color::Blue);
    sensorLeft.setFillColor(sf::Color::Yellow);
    centerVec  = sf::Vector2f(3.5,3.5);
}
void sensor::update(sf::Vector2f pos, float orientation){
    orientation*=(M_PI/180.f);
    pos += sf::Vector2f(7*sin(orientation), -7 *cos(orientation) );
    sensorCenter.setPosition(pos);

}
void sensor::render(sf::RenderTarget &target){
    target.draw(sensorCenter);
    target.draw(sensorRight);
    target.draw(sensorLeft);
}