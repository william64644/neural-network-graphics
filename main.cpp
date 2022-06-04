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
    sf::Font font;

    Graphic_Neuron(double x, double y, double radius, double value)
    {
        shape.setPosition(x, y);
        shape.setRadius(radius);
        shape.setFillColor(random_dark_color());

        font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
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

// get a graphicable neuron from a Layer
Graphic_Neuron get_graphic_neuron(Layer &layer, unsigned int index, double x = 0, double y_spacing = 70, double radius = 30)
{
    double y = index * y_spacing;
    return Graphic_Neuron(x, y, radius, layer.neurons[index]);
}

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(900, 500), "My window");

    // create a Layer
    Layer layer(3, 4);
    Layer layer2(4, 3);
    Layer layer3(3, 2);

    Graphic_Neuron g_neuron1 = get_graphic_neuron(layer, 0);
    Graphic_Neuron g_neuron2 = get_graphic_neuron(layer, 1);
    Graphic_Neuron g_neuron3 = get_graphic_neuron(layer, 2);

    Graphic_Neuron g_neuron4 = get_graphic_neuron(layer2, 0.5, 200);
    Graphic_Neuron g_neuron5 = get_graphic_neuron(layer2, 1.5, 200);

    Graphic_Neuron g_neuron6 = get_graphic_neuron(layer3, 0, 400);
    Graphic_Neuron g_neuron7 = get_graphic_neuron(layer3, 1, 400);
    Graphic_Neuron g_neuron8 = get_graphic_neuron(layer3, 2, 400);

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

        // draw everything here...
        window.draw(g_neuron1.shape);
        window.draw(g_neuron1.text);

        window.draw(g_neuron2.shape);
        window.draw(g_neuron2.text);

        window.draw(g_neuron3.shape);
        window.draw(g_neuron3.text);

        window.draw(g_neuron4.shape);
        window.draw(g_neuron4.text);

        window.draw(g_neuron5.shape);
        window.draw(g_neuron5.text);

        window.draw(g_neuron6.shape);
        window.draw(g_neuron6.text);

        window.draw(g_neuron7.shape);
        window.draw(g_neuron7.text);

        window.draw(g_neuron8.shape);
        window.draw(g_neuron8.text);

        window.display();
    }

    return 0;
}