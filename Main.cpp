#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "PerlinNoise.h"

int screanWidth = 500;
int screanHeight = 500;


sf::Texture CreateTexture(int sizeX, int sizeY,PerlinNoise noise) 
{
    sf::Texture texture;
 
    texture.create(sizeX, sizeY);
    sf::Uint8* pixels = new sf::Uint8[sizeX * sizeY * 4];

    for (int x = 0; x < sizeX; x++)
    {
        for (int y = 0; y < sizeY; y++)
        {
            float value = noise.ValueNoise2D(x,y);

            pixels[(x + y * sizeX) * 4]     = value;   // R
            pixels[(x + y * sizeX) * 4 + 1] = value;   // G
            pixels[(x + y * sizeX) * 4 + 2] = value;   // B
            pixels[(x + y * sizeX) * 4 + 3] = value;   // A
        }
    }

    texture.update(pixels);

    delete[] pixels;

    return texture;
}

int main()
{
    int sizeX = 400;
    int sizeY = 400;
    PerlinNoise noise(40,sizeX,sizeY);

    //Open window
    sf::RenderWindow window(sf::VideoMode(screanWidth, screanHeight), "Perlin Noise");
    
    sf::RectangleShape rect;
    sf::Texture texture;

    texture = CreateTexture(sizeX, sizeY,noise);

    //Create Canvas
    rect.setFillColor(sf::Color::White);
    rect.setPosition(sf::Vector2f(screanWidth / 2 - sizeX / 2, screanHeight / 2 - sizeY / 2));
    rect.setSize(sf::Vector2f(sizeX, sizeY));
    rect.setTexture(&texture);


    while (window.isOpen())
    {
        window.clear();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.draw(rect);
        window.display();
    }

    return 0;
}