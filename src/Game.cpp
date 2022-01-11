#include "../include/Game.hpp"
#include <iostream>
Game::Game(){ 
    init_variables();
    init_window();
    add_texture("ant", "../textures/ant.png");
    spawn_ants();
    init_food();
}

Game::~Game(){
    delete window;
}

void Game::init_variables(){
    Game::event = sf::Event();
    Game::window = nullptr;
    antArray = std::vector<ant *>();
    foodArray= std::vector<food*>();
    max_ant_count = 10;
    max_food_count = 30;

    
    
}

void Game::init_window(){
    Game::window = new sf::RenderWindow(sf::VideoMode(1920,1080), "ant Sim");
    window->setFramerateLimit(144);
}

void Game::init_object(sf::Texture * texture){
    Game::antArray.push_back(new ant(texture));
}

void Game::user_events(){
    if(window->pollEvent(event)){
        switch (event.type)
        {
        case sf::Event::Closed: 
            window->close(); 
            break;
        
        }
    }
    
}

void Game::init_food(){
    Game::foodObj = new food();
}
void Game::windowCollision(ant * simobj){
    bool top = false;
    bool bottom = false;
    bool left = false;
    bool right = false;
    float compare  = simobj->getGlobalBounds().top + (3 *simobj->getGlobalBounds().height )/2;
    if(simobj->getGlobalBounds().left  <=0){
        left = true;
        simobj->rotate_obj(simobj->get_rotation() + 180);
        simobj->setPos(sf::Vector2f(simobj->getGlobalBounds().width/2,simobj->getPos().y));
    }
    // right collison
    else if(simobj->getGlobalBounds().left + simobj->getGlobalBounds().width >= window->getSize().x){
        right = true;
        simobj->rotate_obj(simobj->get_rotation() + 180);
        simobj->setPos(sf::Vector2f(window->getSize().x- simobj-> getGlobalBounds().width/2, simobj->getPos().y));

        
    }
    // top collison
    if(simobj->getGlobalBounds().top <=0){
        top = true;
        simobj->rotate_obj(simobj->get_rotation() + 180);
        if(simobj->getGlobalBounds().top + simobj->getGlobalBounds().height/2 <= 0 ){
            simobj->setPos(sf::Vector2f(simobj->getPos().x,simobj->getGlobalBounds().height/2));
        }
    }
    // bottom collision
    else if(compare >= window->getSize().y){
        bottom = true;
        simobj->rotate_obj(simobj->get_rotation() + 180);
        simobj->setPos(sf::Vector2f(simobj->getPos().x, simobj->getPos().y -(compare - window->getSize().y ) ));
    }
    collision::collision which_collision;
    if(top = true){
       which_collision = collision::top; 
    }else if(bottom= true){
       which_collision = collision::bottom; 
    }
    if(left= true){
       which_collision = collision::left; 
       if(top == true){
           which_collision = collision::top_left;
       }
       if(bottom== true){
           which_collision = collision::bottom_left;
       }
    }
    if(right= true){
       which_collision = collision::right; 
       if(top == true){
           which_collision = collision::top_right;
       }
       if(bottom== true){
           which_collision = collision::bottom_right;
       }
    }
    //std::cout << which_collision << std::endl;
    //simobj->handle_collision(which_collision);
    
}

void Game::finding_food(ant* simobj){
    if(!simobj->get_has_food())
    {
    if(simobj->getGlobalBounds().intersects(foodObj->getGlobalBounds())){
        simobj->found_food(foodObj);
    }
    } 
}

void Game::update(){
    for(auto & simobj: antArray){
        simobj->update();
        windowCollision(simobj);
        finding_food(simobj);
        std::cout << "object at "<<  simobj->getPos().x << " "<< simobj->getPos().y<< std::endl;
        
    }
    
}

void Game::render(){
    window->clear();
    for(int i=0; i < antArray.size(); i++){
        antArray.at(i)->render(*window);
        std::cout << "rendering ant at "<< i <<std::endl;
    }
    foodObj->render(*window);

    window->display();
}

void Game::run_game(){
    while (window->isOpen())
    {
        user_events();
        update();
        render();
        std::cout << "?????????????????"<< std::endl;
    }
}

void Game::spawn_ants(){
    for(int i =0; i < max_ant_count; i++){
        init_object(textureMap["ant"]);
        std::cout<< i <<std::endl;
    }
}

void Game::add_texture(std::string id, std::string pathToTexture){
    textureMap[id] = new sf::Texture();
    if(!textureMap[id]->loadFromFile(pathToTexture)){
        std::cout<< "error loading texture"<<std::endl;
    }
}