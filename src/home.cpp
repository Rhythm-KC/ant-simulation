#include "../include/home.hpp"
#include <iostream>
home::home(float radius, float xCoordinate, float yCoordinate){
    homeShape = sf::CircleShape(radius);
    homeShape.setOrigin(sf::Vector2f(radius,radius));
    homeShape.setPosition(xCoordinate,yCoordinate);
    homeShape.setFillColor(sf::Color::Blue);
}

sf::Vector2f home::getPosition(){
    return homeShape.getPosition();
}

void home::setPosition(float x, float y){
    homeShape.setPosition(x,y);
}

float home::getRadius(){
    return homeShape.getRadius();
}

void home::render(sf::RenderTarget & target){
    target.draw(homeShape);
}

void home::rotate(){
    homeShape.rotate(10);
}