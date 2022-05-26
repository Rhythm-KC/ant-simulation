#include "../include/pheromon.hpp" 
int pheromon::PHEROMON_COUNT = 1; 
int pheromon::PHEROMON_STRENGTH =200;
pheromon::pheromon(pheromon_types type, sf::Vector2f postition, float createdTime, sf::Clock * antsClock){
    this->shape = sf::CircleShape(4);
    this->type = type;
    dropTime = createdTime;
    this->antsClock = antsClock;
    shape.setPosition(postition);
    set_color(type);

}
pheromon::pheromon(){
}
pheromon::~pheromon(){
    
}

void pheromon::set_color(pheromon_types type){

    if(type == pheromon_types::food_pheromon){
        shape.setFillColor(sf::Color::White);
        return;
    }
    shape.setFillColor(sf::Color::Cyan);
}

double pheromon::get_strength(){
    return dropTime/antsClock->getElapsedTime().asSeconds(); 
}
sf::Vector2f pheromon::get_position(){
    return this->shape.getPosition();
    
}

sf::FloatRect pheromon::get_globalBounds(){
    return shape.getGlobalBounds();
}


void pheromon::render(sf::RenderTarget &target){
    target.draw(shape);
}