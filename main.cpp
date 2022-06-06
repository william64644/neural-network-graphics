#include <vector>
#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

using namespace std;

struct Layer // give it the size of the layer and the size of the next layer (0 for the output layer)
{
    vector<double> neurons;
    vector<vector<double>> weights;
    Layer(unsigned int size, unsigned int next_layer_size)
    {
        neurons = vector<double>(size);
        weights = vector<vector<double>>(size, vector<double>(next_layer_size));
    }
};

void matrix_randomizer(vector<vector<double>> &data)
{
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    for (long unsigned int i = 0; i < data.size(); i++)
    {
        for (long unsigned int j = 0; j < data[i].size(); j++)
        {
            data[i][j] = (rand() % 100) / 100.0;
        }
    }
}

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
    }

    void update(double value)
    {
        text.setString(to_string(value));
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

int main()
{
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf");

    // create the window
    sf::RenderWindow window(sf::VideoMode(1400, 800), "My window");

    // create a Layer
    Layer layer(3, 4);
    Layer layer2(4, 3);
    Layer layer3(3, 0);

    vector<Graphic_Neuron> graphic_layer1 = generate_graphic_neurons(layer, font, 0, 0, 30);
    vector<Graphic_Neuron> graphic_layer2 = generate_graphic_neurons(layer2, font, 500, 0, 30);
    vector<Graphic_Neuron> graphic_layer3 = generate_graphic_neurons(layer3, font, 1000, 0, 30);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loopp
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // draw the layer
        draw_graphic_neurons(window, graphic_layer1);
        draw_graphic_neurons(window, graphic_layer2);
        draw_graphic_neurons(window, graphic_layer3);
        window.display();
    }

    return 0;
}