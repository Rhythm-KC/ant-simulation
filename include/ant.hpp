#ifndef ANT_H
#define ANT_H
#include <ctime>
#include <SFML/Graphics.hpp>
#include "CollisionType.hpp"
#include "pheromon.hpp"
#include "food.hpp"
#include <random>
class ant 
{
private:
    // static variables 
    
    static float posX;
    static float posY;
    static std::vector<float> generated_points;
    // non static variables
    int drop_time;
    sf::Vector2f desiredDirection;
    sf::Vector2f velocity;
    bool has_food;
    food * ants_food; 
    std::default_random_engine generator; 
    std:: uniform_real_distribution<float> distribution;
    sf::Sprite sprite;
    unsigned turn_cooldown;
    sf::RectangleShape boundingShape;
    // methods
    void init_variables();
    void init_sprite(sf::Texture * texture);
    void drop_pheromon();
    void find_food();
    void update_phereamon();
    void movement();
    void move_around();
    void keyBoard_movement();
    void keyboard_rotate();
    void generate_position();
    /// static methods
    static void set_srand();

public:
    ant(sf::Texture * textureptr);
    ~ant();

    //methods 
    sf::Vector2f clampVector(sf::Vector2f vector, float maxMag);
    void update();
    void render(sf::RenderTarget &target);
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPos();
    sf::FloatRect getlocalBounds();
    void setPos(sf::Vector2f position);
    float get_rotation();
    void found_food(food * food);
    bool get_has_food();
    void rotate_obj(float angle);
    void followMouse(sf::Vector2i mousePos);
    
    // static 
    static std::vector<pheromon >  * pheromones_storage;
    static std::vector<pheromon > * get_pheromon_storage();
     
};
#endif
