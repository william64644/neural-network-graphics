#include <vector>
#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "/home/william/GitHub/homemamde-neural-network/headers/utils.h"
#include "/home/william/GitHub/homemamde-neural-network/headers/core_neural.h"

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

    void update()
    {
        this->text.setString(to_string(this->value));
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
    sf::RenderWindow window(sf::VideoMode(600, 300), "My window");

    // create a Layer
    Layer layer1(3, 4);
    Layer layer2(4, 3);
    Layer layer3(3, 0);

	layer1.neurons = {1, 1, 1};

	matrix_randomizer(layer1.weights);
	matrix_randomizer(layer2.weights);

	layer_parser(layer1, layer2);
	layer_parser(layer2, layer3);

    vector<Graphic_Neuron> graphic_layer1 = generate_graphic_neurons(layer1, font, 0, 0, 30);
    vector<Graphic_Neuron> graphic_layer2 = generate_graphic_neurons(layer2, font, 200, 0, 30);
    vector<Graphic_Neuron> graphic_layer3 = generate_graphic_neurons(layer3, font, 400, 0, 30);

    // run the program as long as the window is open
window.setFramerateLimit(1);
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
        layer_parser(layer1, layer2);
	layer_parser(layer2, layer3);
        draw_graphic_neurons(window, graphic_layer1);
        draw_graphic_neurons(window, graphic_layer2);
        draw_graphic_neurons(window, graphic_layer3);

    graphic_layer1 = generate_graphic_neurons(layer1, font, 0, 0, 30);
    graphic_layer2 = generate_graphic_neurons(layer2, font, 200, 0, 30);
    graphic_layer3 = generate_graphic_neurons(layer3, font, 400, 0, 30);

   	matrix_randomizer(layer1.weights);
	matrix_randomizer(layer2.weights);

	//layer1.neurons[0] +=1;
	//layer1.neurons[1] +=2;
	//layer1.neurons[2] +=3;
        window.display();
    }

    return 0;
}
