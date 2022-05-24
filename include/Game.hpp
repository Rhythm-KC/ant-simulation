#ifndef GAME_H
#define GAME_H
#include "CollisionType.hpp"
#include "ant.hpp"
#include "home.hpp"
#include "food.hpp"
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
    int max_ant_count;
    int max_food_count;
    // home object
    home * homeObj;
    // methods 
    void init_food(float x, float y );
    void init_object(sf::Texture * texturePtr);
    void init_variables();
    void init_window();
    void user_events();
    void init_home();
    void update();
    void render();
    void windowCollision(ant * simobj);
    void finding_food(ant* simobj);
    void spawn_ants();
    void spawn_foods();
public:
    Game();
    ~Game();
    void run_game();
    void add_texture(std::string id, std::string pathToTexture);

};
#endif
