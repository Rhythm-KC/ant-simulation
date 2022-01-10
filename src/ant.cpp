#include "../include/ant.hpp"
#include <iostream>
#include <cmath>
std::vector<pheromon> * ant::pheromones_storage = new std::vector<pheromon>;
ant::ant(sf::Texture * textureptr) : distribution(-30.f, 30.f) 
{
    init_variables(); 
    this->sprite.setTexture(*textureptr);
    sprite.scale(sf::Vector2f(0.12f,0.12f));
    this->sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2));
    boundingShape.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height ));
    boundingShape.setFillColor(sf::Color::White);
    boundingShape.setOrigin(sf::Vector2f(boundingShape.getLocalBounds().width/2,boundingShape.getLocalBounds().height));

    sprite.setPosition(sf::Vector2f(posX, posY));
    boundingShape.setPosition(sf::Vector2f(posX, posY));
    
}

ant::~ant()
{
    
}
void ant::init_variables(){
    this->generator = std::default_random_engine();
    turn_cooldown = 0;
    drop_time = 50;
    posX = 400.f;
    posY = 400.f;
    has_food = false;
    ants_food = nullptr;
    orientation * ant_orientation = (orientation *) calloc(sizeof(orientation), 1);

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
    if(turn_cooldown == 50){ 
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
        this->posY = - cos(sprite_angle) * 2.0f;
        this->posX = sin(sprite_angle) * 2.0f;
    }
    else if( angle > 90 && angle <= 180) {
        angle = 180- angle;
        sprite_angle = angle *(M_PI/180);
        this->posX = sin(sprite_angle) * 2.0f;
        posY = cos(sprite_angle) * 2.f;

    }else if (angle > 180 && angle <= 270){
        angle =  angle - 180;
        sprite_angle = angle * (M_PI/180);
        posX = -sin(sprite_angle) * 2.f;
        posY = cos(sprite_angle) * 2.f;
    }else if(angle > 270 && angle <= 360)
    {
        angle = angle -270;
        sprite_angle = angle *(M_PI /180);
        posX = -cos(sprite_angle) * 2.f;
        posY = -sin(sprite_angle) * 2.f;

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

/*
    rotates the ant object 5 degrees relative to its current angle 
    if the current angle is between 270 to 360 and 0 to 90 than the rotaion is clockwise
    else ant-clock wise
*/
void ant::rotate(){
    float current_angle = sprite.getRotation();

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
    
    std::cout << "angle " << sprite.getRotation()<< std::endl;
    std::cout << "top " << sprite.getGlobalBounds().top << std::endl;
    std::cout << "left "  << sprite.getGlobalBounds().left<< std::endl;
    std::cout << "pos x " << sprite.getPosition().x<< std::endl;
    std::cout << "pos y " << sprite.getPosition().y<< std::endl;
    std::cout << "height " << sprite.getGlobalBounds().height<< std::endl;
    std::cout << "width " << sprite.getGlobalBounds().width<< std::endl;
    std::cout << "/////////////" <<std::endl; 
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


void ant::calculate_orientation(){
    float angle = sprite.getRotation();

}

void ant::rotate_obj(float angle){
    sprite.rotate(angle);
    boundingShape.rotate(angle);
}

bool ant::get_has_food(){
    return has_food;
}

void ant::top_collision(){
    float angle = sprite.getRotation();
    if(angle >= 0 && angle <90){
       rotate_obj(30); 
    }
    if(angle > 270 && angle < 360){
        rotate_obj(-30);
    }

}

void ant::bottom_collision(){
    float angle = sprite.getRotation();
    if(angle > 90 && angle < 180){
       rotate_obj(-30); 
    }
    if(angle >= 180&& angle < 270){
       rotate_obj(30);
    }

}

void ant::left_collision(){
    float angle = sprite.getRotation();
    if(angle > 180 && angle <=270){
       rotate_obj(-30); 
    }
    if(angle > 270 && angle <360){
        rotate_obj(30);
    }
}

void ant::right_collision(){
    float angle = sprite.getRotation();
    if(angle > 0 && angle <=90){
       rotate_obj(-30); 
    }
    if(angle > 90 && angle < 180){
        rotate_obj(30);
    }

}

void ant::topRight_collision(){
    float angle = sprite.getRotation();
    if(angle == 0 || (angle >270 && angle < 360)){
        rotate_obj(-30);

    }
    if(angle > 0 && angle <180){
       rotate_obj(30); 
    }

}

void ant::topLeft_collision(){
    float angle = sprite.getRotation();
    if(angle > 0 && angle <90){
       rotate_obj(30);
    }
    if(angle > 180 && angle < 360){
        rotate_obj(-30);
    }

}

void ant::bottomLeft_collision(){
    float angle = sprite.getRotation();
    if(angle > 180 && angle <=270){
       rotate_obj(-30); 
    }
    if(angle > 270 && angle < 360){
        rotate_obj(30);
    }

}

void ant::bottomRight_collision(){
    float angle = sprite.getRotation();
    if(angle > 0 && angle <=90){
       rotate_obj(-30); 
    }
    if(angle > 90 && angle < 270){
        rotate_obj(30);
    }


}

void ant::handle_collision(collision::collision which){
    if(which = collision::top){
        top_collision();
    }
    if(which = collision::bottom){
        bottom_collision();
    }
    if(which = collision::right){
        right_collision();
    }
    if(which = collision::left){
        left_collision();
    }
    if(which = collision::bottom_left){
        bottomLeft_collision();
    }
    if(which = collision::bottom_right){
        bottomRight_collision();
    }
    if(which = collision::top_right){
        topRight_collision();
        
    }
    if(which = collision::top_left){
        topLeft_collision();
    }
}


/*
    provieds acces to the pheromoon_storage of type vector
*/
std::vector<pheromon> * ant::get_pheromon_storage(){
    return ant::pheromones_storage;
}

