// sfml.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"


int main()
{
	//randow
	std::srand(static_cast<unsigned>(time(NULL)));


	Game game;

	//window.setFramerateLimit(60);
	//sf::CircleShape shape(50.0f);
	//sf::RectangleShape shape(sf::Vector2f(100.f, 100.f));
	//shape.setOrigin(50.f, 50.f);

	//shape.setPosition(400.f  /* - shape.getRadius()*/, 300.f  /* - shape.getRadius() */);
	//sf::Texture playerTexture;
	//playerTexture.loadFromFile("Mario.gif");
	//shape.setTexture(&playerTexture);
	
	
	//shape.setFillColor(sf::Color::Blue);
	//dxball
	while (game.running())
	{
		game.Update();

		game.render();
	}
	
	

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file



	//case sf::Event::Resized:
	//		//	std::cout << "width: " << event.size.width << " height: " << event.size.height << std::endl;
	//		//	break;
	//		//case sf::Event::MouseButtonPressed:
	//		//	if (event.mouseButton.button == sf::Mouse::Left)
	//		//	{
	//		//		std::cout << "left button pressed\n";
	//		//		std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	//		//		std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	//		//		//shape.setPosition(event.mouseButton.x /*- shape.getRadius()*/, event.mouseButton.y /*- shape.getRadius()*/);

	//		//	}
	//			
	//			break;
	//		case sf::Event::MouseMoved:
	//			/*std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
	//			std::cout << "new mouse y: " << event.mouseMove.y << std::endl;*/
	//			//shape.setPosition(event.mouseMove.x - shape.getRadius(), event.mouseMove.y - shape.getRadius());
	//			
	//			break;
	//		}
	//		
	//	}

	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
	//		shape.move(-1.0f, 0.0f);
	//	}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
	//		shape.move(1.0f, 0.0f);
	//	}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
	//		shape.move(0.0f, -1.0f);
	//	}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
	//		shape.move(0.0f, 1.0f);
	//	}

	//	//window.setPosition(sf::Vector2i(10, 50));
	//	window.clear(sf::Color::Yellow);
	//	window.draw(shape);
	//	window.display();
	//
	//}
