#include "../include/food.hpp"
food::food(float x, float y){
    food_shape = sf::CircleShape(5);
    food_shape.setFillColor(sf::Color::Green);
    food_shape.setPosition(x,y);
    isTake = false;
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

bool food::get_isTaken(){
    return isTake;
} 

void food::set_isTake(bool value){
    isTake = value;
}