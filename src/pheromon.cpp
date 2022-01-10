#include "../include/pheromon.hpp" 
int pheromon::PHEROMON_COUNT = 1; 
int pheromon::PHEROMON_STRENGTH =200;
pheromon::pheromon(pheromon_types type, float posX, float posY){
    this->shape = sf::CircleShape(4);
    this->type = type;
    strength = (PHEROMON_COUNT) * (PHEROMON_STRENGTH - 50);
    PHEROMON_COUNT ++;
    shape.setPosition(posX,posY);
    set_color(type);

}
pheromon::pheromon(){
}
pheromon::~pheromon(){
    
}

void pheromon::set_color(pheromon_types type){

    if(type == pheromon_types::foods){
        shape.setFillColor(sf::Color::White);
        return;
    }
    shape.setFillColor(sf::Color::Cyan);
}

void pheromon::strength_update(){
    strength--;

}
sf::Vector2f pheromon::get_position(){
    return this->shape.getPosition();
}

int pheromon::get_strength(){
    return this->strength;
}

void pheromon::render(sf::RenderTarget &target){

    target.draw(shape);
}