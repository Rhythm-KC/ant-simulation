#include "../include/Game.hpp"
#include <iostream>
Game::Game(){ 
    srand(time(NULL));
    init_variables();
    init_window();
    add_texture("ant", "../textures/ant.png");
    init_home();
    spawn_foods();
    spawn_ants();
    
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
    max_food_count = 10;
    
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

void Game::init_food(float x, float y){
    foodArray.push_back( new food(x , y));
}

void Game::init_home(){
    homeObj = new home(100.f , 300.f, 400.f);
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
    for(int i =0; i < foodArray.size(); i++){
        food * foodObj = foodArray.at(i);
        if(!simobj->get_has_food() && !foodObj->get_isTaken())
        {
        if(simobj->getGlobalBounds().intersects(foodObj->getGlobalBounds())){
            simobj->found_food(foodObj);
            foodObj->set_isTake(true); 
        }
    } 
        
    }
}

void Game::update(){
    for(auto & simobj: antArray){
        simobj->update();
        windowCollision(simobj);
        finding_food(simobj);
        
    }
    
}

void Game::render(){
    window->clear();
    homeObj->render(*window);
    for(int i=0; i < antArray.size(); i++){
        antArray.at(i)->render(*window);
    }
    for(int i=0; i < foodArray.size(); i++){
        foodArray.at(i)->render(*window);
    }
    window->display();
}

void Game::run_game(){
    while (window->isOpen())
    {
        user_events();
        update();
        render();
    }
}

void Game::spawn_ants(){
    for(int i =0; i < max_ant_count; i++){
        init_object(textureMap["ant"]);
    }
}

void Game::spawn_foods(){
    for(int i =0; i< max_food_count; i++){
        float x = ((rand()%100)/((float) 100))*1920;
        float y=((rand()%100)/((float) 100))*1080;
        init_food(x, y);
    }
}

void Game::add_texture(std::string id, std::string pathToTexture){
    textureMap[id] = new sf::Texture();
    if(!textureMap[id]->loadFromFile(pathToTexture)){
        std::cout<< "error loading texture"<<std::endl;
    }
}