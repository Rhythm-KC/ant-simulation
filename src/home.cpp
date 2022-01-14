#include "../include/home.hpp"

home::home(float radius, float xCoordinate, float yCoordinate){
    homeShape = sf::CircleShape(radius);
    homeShape.setOrigin(sf::Vector2f(xCoordinate,yCoordinate));
    homeShape.setFillColor(sf::Color::Yellow);
}

sf::Vector2f home::getPosition(){
    return homeShape.getPosition();
}

void home::setPosition(float x, float y){
    homeShape.setPosition(x,y);
}

void home::render(sf::RenderTarget & target){
    target.draw(homeShape);
}