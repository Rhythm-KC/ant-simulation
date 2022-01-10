#include "../include/food.hpp"
food::food(){
    food_shape = sf::CircleShape(5);
    food_shape.setFillColor(sf::Color::Green);
    food_shape.setPosition(500,300);
}
sf::FloatRect food::getGlobalBounds(){
    return food_shape.getGlobalBounds();
}
void food::setPos(float x, float y){
    food_shape.setPosition(x,y);
}
void food::update_pos(float x, float y){

    food_shape.setPosition(x,y);
}
void food::render(sf:: RenderTarget & target){
    target.draw(food_shape);
}