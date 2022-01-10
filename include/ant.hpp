#ifndef ANT_H
#define ANT_H
#include <SFML/Graphics.hpp>
#include "CollisionType.hpp"
#include "pheromon.hpp"
#include "food.hpp"
#include <random>
class ant 
{
private:
    typedef struct Orientation{
        float top;
        float bottom;
        float left;
        float rigth;
    } orientation;

    orientation * ant_orientation;
    int drop_time;
    bool has_food;
    food * ants_food; 
    static float posX;
    static float posY;
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
    void calculate_orientation();
    void top_collision();
    void bottom_collision();
    void left_collision();
    void right_collision();
    void topRight_collision();
    void topLeft_collision();
    void bottomLeft_collision();
    void bottomRight_collision();
public:
    ant(sf::Texture * textureptr);
    ~ant();

    //methods 
    void update();
    void render(sf::RenderTarget &target);
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPos();
    sf::FloatRect getlocalBounds();
    void setPos(sf::Vector2f position);
    float get_rotation();
    void rotate();
    void found_food(food * food);
    bool get_has_food();
    void rotate_obj(float angle);
    void handle_collision(collision::collision which);
    
    // static 
    static std::vector<pheromon >  * pheromones_storage;
    static std::vector<pheromon > * get_pheromon_storage();
     
};
#endif
