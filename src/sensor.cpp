#include "../include/sensor.hpp"
#include <cmath>

sensor::sensor(sf::Vector2f antPos, float rotation){
    size = 15;
    buildSensor();
    update(antPos,rotation);
}

void sensor::buildSensor(){
    sensorLeft = sf::CircleShape(size);
    sensorCenter= sf::CircleShape(size);
    sensorRight= sf::CircleShape(size);
    setOriginandColor();
}

void sensor::update(sf::Vector2f pos, float orientation){
    orientation*=(M_PI/180.f);
    float theta = 45.f;
    sf::Vector2f centerPos = pos+sf::Vector2f(25*sin(orientation), -25 *cos(orientation) );
    sensorCenter.setPosition(centerPos);
    sf::Vector2f righPos =pos + sf::Vector2f(31*sin(orientation + theta),- 31* cos(orientation + theta));
    sensorRight.setPosition(righPos);
    sf::Vector2f leftPos=pos + sf::Vector2f(31*sin(orientation - theta),- 31* cos(orientation - theta));
    sensorLeft.setPosition(leftPos);

}

void sensor::setOriginandColor(){
    sensorCenter.setOrigin(sensorCenter.getLocalBounds().width/2.f, sensorCenter.getLocalBounds().height/2);
    sensorLeft.setOrigin(sensorLeft.getLocalBounds().width/2.f, sensorLeft.getLocalBounds().height/2);
    sensorRight.setOrigin(sensorRight.getLocalBounds().width/2.f, sensorRight.getLocalBounds().height/2);
    sensorCenter.setFillColor(sf::Color::Green);
    sensorRight.setFillColor(sf::Color::Blue);
    sensorLeft.setFillColor(sf::Color::Yellow);
}
void sensor::render(sf::RenderTarget &target){
    target.draw(sensorCenter);
    target.draw(sensorRight);
    target.draw(sensorLeft);
}