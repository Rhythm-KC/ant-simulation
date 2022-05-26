#include "../include/ant.hpp"
#include <iostream>
#include <cmath>
// setting up static methods and variables 
void ant::set_srand(){
    srand(time(NULL));
}
std::vector<float> ant:: generated_points = std::vector<float>();
std::vector<pheromon> * ant::pheromones_storage = new std::vector<pheromon>;

//constructor
ant::ant(sf::Texture * textureptr): distribution(-1.f,1.f) 
{
    desiredDirection = sf::Vector2f(0.f,0.f);
    init_variables(); 
    this->sprite.setTexture(*textureptr);
    sprite.scale(sf::Vector2f(0.12f,0.12f));
    generate_position(); 
    this->sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2));
    setPos(sf::Vector2f(400,400));
    antSensor = new sensor(getPos(), get_rotation());
}

ant::~ant()
{}    

sf::Vector2f ant::getDesiredDirection(){
    return desiredDirection;
}
void ant::setDesiredDirection(sf::Vector2f position){
    desiredDirection = position;
}
void ant::init_variables(){
    velocity = sf::Vector2f(0,0);
    drop_time = 50;
    has_food = false;
    ants_food = nullptr;

}
void ant::movement(){
    move_around(); 
    update_phereamon();
    antSensor->update(getPos(), get_rotation());

}
sf::FloatRect ant::getGlobalBounds(){
    return sprite.getGlobalBounds();
}
sf::Vector2f ant::getPos(){
    return sprite.getPosition();
}
void ant::setPos(sf::Vector2f position){
    sprite.setPosition(position);
    if(has_food){
        ants_food->setPos(position.x, position.y);
    }
}
sf::FloatRect ant::getlocalBounds(){
    return sprite.getLocalBounds();
}
void ant::render(sf::RenderTarget &target){
    target.draw(this->sprite);
    for(int i =0; i < pheromones_storage->size(); i++){
        pheromones_storage->at(i).render(target);
    }
    antSensor->render(target);
}

/* 
    this creates new phereomons and add to the pheromon storage vector 
*/
void ant::drop_pheromon(){
    if(drop_time ==0){
        if (has_food){
            pheromones_storage->push_back(pheromon(pheromon_types::food_pheromon, this->getPos().x,this->getPos().y));
        
        }else{
            pheromones_storage->push_back(pheromon(pheromon_types::home_pheromon, this->getPos().x,this->getPos().y));
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
}

bool ant::get_has_food(){
    return has_food;
}

void ant::generate_position(){
}


/*
    provieds acces to the pheromoon_storage of type vector
*/
std::vector<pheromon> * ant::get_pheromon_storage(){
    return ant::pheromones_storage;
}


void ant::move_around(){
    float time = 1/60.f*100;
    float steerStrength = 2.f;
    float wanderStrength = 0.15f;
    float x = distribution(generator); 
    float y = distribution(generator);

    desiredDirection =  desiredDirection +(sf::Vector2f(x,y) * wanderStrength) ;
    float magnitude = sqrt((desiredDirection.x* desiredDirection.x) + (desiredDirection.y* desiredDirection.y));
    desiredDirection/= magnitude;
    float angle = atan2(-desiredDirection.y,desiredDirection.x) *(180/M_PI);
    sf:: Vector2f desiredVelocity = desiredDirection* 1.5f;
    sf::Vector2f steeringForce = (desiredVelocity - velocity) * steerStrength;
    sf::Vector2f acceleration = clampVector(steeringForce,steerStrength); 
    velocity = clampVector(velocity+acceleration* time, 2.f); 
    rotate_obj(90.f - angle);
    setPos(getPos()+ velocity * time);
}

sf::Vector2f  ant::clampVector(sf::Vector2f  vector, float maxMag){
    float mag = sqrt(vector.x * vector.x + (vector.y * vector.y));
    if (mag <= maxMag){
        return vector;
    }
    vector/= maxMag;
    return vector;
}