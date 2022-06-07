#pragma once

#include <vector>
#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "/home/night/Documents/GitHub/neural-network-framework/headers/core_neural.h"

using namespace std;

sf::Color random_color()
{
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    return sf::Color(rand() % 255, rand() % 255, rand() % 255);
}

sf::Color random_dark_color()
{
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    return sf::Color(rand() % 100 + 100, rand() % 100 + 100, rand() % 100 + 100);
}

struct Graphic_Neuron
{
    sf::CircleShape shape;
    sf::Text text;
    double value;

    Graphic_Neuron(sf::Font &font, double x = 0, double y = 0, double radius = 0, double value = 0)
    {

        shape.setPosition(x, y);
        shape.setRadius(radius);
        shape.setFillColor(random_dark_color());

        text.setFont(font);

        text.setFillColor(sf::Color::White);
        text.setCharacterSize(radius);
        text.setString(to_string(value));
        text.setPosition(x + radius, y);
        this->value = value;
    }
};

void draw_graphic_neurons(sf::RenderWindow &window, vector<Graphic_Neuron> &layer)
{
    for (long unsigned int i = 0; i < layer.size(); i++)
    {
        window.draw(layer[i].shape);
        window.draw(layer[i].text);
    }
}

vector<Graphic_Neuron> generate_graphic_neurons(Layer &layer, sf::Font &font, double x = 0, double y = 0, double radius = 0)
{
    vector<Graphic_Neuron> graphic_neurons;
    for (long unsigned int i = 0; i < layer.neurons.size(); i++)
    {
        graphic_neurons.push_back(Graphic_Neuron(font, x, y, radius, layer.neurons[i]));
        y += radius * 2;
    }
    return graphic_neurons;
}