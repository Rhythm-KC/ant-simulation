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

sf::Vector2f sensor::checkPheromon(std::vector<pheromon> storage)
{   
    float centerStr = 0.f;
    float leftStr= 0.f;
    float rightStr= 0.f;

    for(auto & phero : storage){
        float strength = phero.get_strength();
        if(strength <=0){
            phero.~pheromon();
            continue;
        }
        if (phero.get_globalBounds().intersects(sensorCenter.getGlobalBounds())){
            centerStr += phero.get_strength();
        }
        if (phero.get_globalBounds().intersects(sensorLeft.getGlobalBounds())){
            leftStr+= phero.get_strength();
        }
        if (phero.get_globalBounds().intersects(sensorRight.getGlobalBounds())){
            rightStr+= phero.get_strength();
        }
    }
    if (centerStr >= std::max(leftStr,rightStr)){
        return sensorCenter.getPosition(); 
    }
    if (leftStr > rightStr){
        return sensorLeft.getPosition();
    }else{
        return sensorRight.getPosition();
    }
    return sf::Vector2f(-1,-1);
}

void sensor::render(sf::RenderTarget &target){
    target.draw(sensorCenter);
    target.draw(sensorRight);
    target.draw(sensorLeft);
}