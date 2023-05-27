#include "cell.h"

Cell::Cell()
{
    will_be_alive = false;
    is_alive = false;
}

void Cell::set_size(int new_size)
{
    size = new_size;
    rect = sf::RectangleShape(sf::Vector2f(size - 1, size - 1)); // size-1 gives a border around each cell
}

void Cell::set_position(int x, int y)
{
    rect.setPosition(sf::Vector2f(x, y));
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
