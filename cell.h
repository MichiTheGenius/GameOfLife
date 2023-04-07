#pragma once
#include <SFML/Graphics.hpp>

class Cell
{
public:
    bool is_alive;
    int size;
    sf::RectangleShape rect;

    Cell();

    void set_size(int new_size);
    void set_position(int col, int row);
    void draw(sf::RenderWindow &window);
};