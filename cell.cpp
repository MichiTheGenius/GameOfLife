#include "cell.h"

Cell::Cell()
{
    is_alive = false;
}

void Cell::set_size(int new_size)
{
    size = new_size;
    rect = sf::RectangleShape(sf::Vector2f(size - 1, size - 1)); // size-1 gives a border around each cell
}

void Cell::set_position(int col, int row)
{
    rect.setPosition(sf::Vector2f(col, row));
}

void Cell::draw(sf::RenderWindow &window)
{
    if (is_alive)
    {
        rect.setFillColor(sf::Color::White);
    }
    else
    {
        rect.setFillColor(sf::Color::Black);
    }
    window.draw(rect);
}
