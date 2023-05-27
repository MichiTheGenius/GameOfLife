#pragma once
#include <SFML/Graphics.hpp>

class Cell
{
public:
    bool will_be_alive;
    bool is_alive;
    int size;
    sf::RectangleShape rect;

    Cell();

    void set_size(int new_size);
    void set_position(int x, int y);
    void draw(sf::RenderWindow &window);
};