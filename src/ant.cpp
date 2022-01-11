#include "../include/ant.hpp"
#include <iostream>
#include <cmath>
// setting up static methods and variables 
float ant::posX = 400.f;
float ant::posY = 400.f;
void ant::set_srand(){
    srand(time(NULL));
}
std::vector<float> ant:: generated_points = std::vector<float>();
std::vector<pheromon> * ant::pheromones_storage = new std::vector<pheromon>;

//constructor
ant::ant(sf::Texture * textureptr) : distribution(-30.f, 30.f) 
{
    init_variables(); 

    this->sprite.setTexture(*textureptr);
    sprite.scale(sf::Vector2f(0.12f,0.12f));
    generate_position(); 
    this->sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2));
    boundingShape.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height ));
    boundingShape.setFillColor(sf::Color::White);
    boundingShape.setOrigin(sf::Vector2f(boundingShape.getLocalBounds().width/2,boundingShape.getLocalBounds().height));
}

ant::~ant()
{
    
}
void ant::init_variables(){
    this->generator = std::default_random_engine();
    turn_cooldown = 0;
    drop_time = 50;
    has_food = false;
    ants_food = nullptr;

}
void ant::movement(){
    move_around(); 
   update_phereamon();

}
sf::FloatRect ant::getGlobalBounds(){
    return boundingShape.getGlobalBounds();
}
sf::Vector2f ant::getPos(){
    return boundingShape.getPosition();
}
void ant::setPos(sf::Vector2f position){
    boundingShape.setPosition(position);
    sprite.setPosition(position);
    if(has_food){
        ants_food->setPos(position.x, position.y);
    }
}
sf::FloatRect ant::getlocalBounds(){
    return boundingShape.getLocalBounds();
}
void ant::render(sf::RenderTarget &target){
    target.draw(this->boundingShape);
    target.draw(this->sprite);
    for(int i =0; i < pheromones_storage->size(); i++){
        pheromones_storage->at(i).render(target);
    }
}

/*
    @pre: collisions are not handled by this function 
    This function moves the ant rondomly in the screen
        a random able is gnererated between -30 degree and 30 degree
        this is done every 10 frames 
        between those 10 frames the ant moves along the same angle with a certain speed 
*/
void ant::move_around(){
    // generating new angle of to which the ant has to be rotated
    if(turn_cooldown == 25){ 
        float angle = distribution(generator);
        sprite.rotate(angle);
        boundingShape.rotate(angle);
        turn_cooldown = 0;
    }else{
        turn_cooldown++;
    }

    float angle = sprite.getRotation();
    double sprite_angle = angle*((M_PI)/180); // converting to raidians

    if(angle > 0 && angle <=90){
        this->posY = - cos(sprite_angle) * 1.5f;
        this->posX = sin(sprite_angle) * 1.5f;
    }
    else if( angle > 90 && angle <= 180) {
        angle = 180- angle;
        sprite_angle = angle *(M_PI/180);
        this->posX = sin(sprite_angle) * 1.5f;
        posY = cos(sprite_angle) * 1.5f;

    }else if (angle > 180 && angle <= 270){
        angle =  angle - 180;
        sprite_angle = angle * (M_PI/180);
        posX = -sin(sprite_angle) * 1.5f;
        posY = cos(sprite_angle) * 1.5f;
    }else if(angle > 270 && angle <= 360)
    {
        angle = angle -270;
        sprite_angle = angle *(M_PI /180);
        posX = -cos(sprite_angle) * 1.5f;
        posY = -sin(sprite_angle) * 1.5f;

    }
    // moving the ant obj
    sprite.move(this->posX,this->posY);
    boundingShape.move(this->posX,this->posY);
    // moving food if ant has any;
    if(has_food){
        ants_food->update_pos(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().top);
    }
    drop_pheromon();
}

void ant::keyboard_rotate(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        sprite.rotate(2.f);
        boundingShape.rotate(2.f);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        sprite.rotate(-2.f);
        boundingShape.rotate(-2.f);
    }
    
    
}

void ant::keyBoard_movement(){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        sprite.move(-5.f, 0);
        boundingShape.move(-5.f,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        sprite.move(5.f, 0);
        boundingShape.move(5.f,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        sprite.move(0.f, -.5f);
        boundingShape.move(0,-.5f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        sprite.move(0.f, .5f);
        boundingShape.move(0,.5f);
    }
}

/* 
    this creates new phereomons and add to the pheromon storage vector 
*/
void ant::drop_pheromon(){
    if(drop_time ==0){
        if (has_food){
            pheromones_storage->push_back(pheromon(pheromon_types::foods, this->getPos().x,this->getPos().y));
        
        }else{
            pheromones_storage->push_back(pheromon(pheromon_types::home, this->getPos().x,this->getPos().y));
        }
        drop_time = 50;
    }
    drop_time--;
}

/*
    updates the ant object every frame
*/
void ant::update(){
    movement();
    update_phereamon();
    keyBoard_movement();
    keyboard_rotate();
    
    //std::cout << "angle " << sprite.getRotation()<< std::endl;
    //std::cout << "top " << sprite.getGlobalBounds().top << std::endl;
    //std::cout << "left "  << sprite.getGlobalBounds().left<< std::endl;
    //std::cout << "pos x " << sprite.getPosition().x<< std::endl;
    //std::cout << "pos y " << sprite.getPosition().y<< std::endl;
    //std::cout << "height " << sprite.getGlobalBounds().height<< std::endl;
    //std::cout << "width " << sprite.getGlobalBounds().width<< std::endl;
    //std::cout << "/////////////" <<std::endl; 
}

/* provides with the angle at which the ant object is rotated in degrees
*/
float ant::get_rotation(){
    return sprite.getRotation();
}

/*
    updates the the pheromons strength and removes the pheramon if the it has a strength of 0
*/
void ant::update_phereamon(){
    for(unsigned int i =0 ; i < pheromones_storage->size(); i++){
        if( pheromones_storage->at(i).get_strength() <= 0){
            pheromones_storage->erase(pheromones_storage->begin() + i);
            break;
        }
        pheromones_storage->at(i).strength_update();
    }
}

/*
    lets the ant know that it has found food 
    and also the ant carries the food 
*/
void ant::found_food(food * food){
    has_food = true; 
    ants_food = food;
    ants_food->setPos(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().top);
}



void ant::rotate_obj(float angle){
    sprite.setRotation(angle);
    boundingShape.setRotation(angle);
}

bool ant::get_has_food(){
    return has_food;
}

void ant::generate_position(){
    int radius = 50;
    float theta = (rand()%200)/(float)100;
    while(std::find(generated_points.begin(), generated_points.end(), theta) != generated_points.end() && !generated_points.empty()){
        float theta = (rand()%200)/(float)100;
    }
    generated_points.push_back(theta);
    theta*= (2*M_PI);
    float y = posY - sin(theta) * radius + 40.f;
    float x = posX + cos(theta) * radius + 40.f;
    setPos(sf::Vector2f(x,y));
    rotate_obj(theta * 360);
}


/*
    provieds acces to the pheromoon_storage of type vector
*/
std::vector<pheromon> * ant::get_pheromon_storage(){
    return ant::pheromones_storage;
}

