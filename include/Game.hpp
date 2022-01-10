#ifndef GAME_H
#define GAME_H
#include "CollisionType.hpp"
#include "ant.hpp"
class Game
{
private:
    
    // texture map
    std::map<std::string, sf::Texture *> textureMap; 
    // window and event
    sf::RenderWindow * window; 
    sf::Event event;
    // object vector
    std::vector<ant * > antArray;
    std::vector<food *> foodArray;
    ant * simobj;
    food * foodObj;

    // methods 
    void init_food();
    void init_object(sf::Texture * texturePtr);
    void init_variables();
    void init_window();
    void user_events();
    void update();
    void render();
    void windowCollision();
    void finding_food();
public:
    Game();
    ~Game();
    void run_game();
    void add_texture(std::string id, std::string pathToTexture);

};
#endif
