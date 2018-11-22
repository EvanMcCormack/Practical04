#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <GameObject.h>
#include <Player.h>
#include <NPC.h>
#include <Input.h>
#include <Debug.h>

using namespace std;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Load a NPC's sprites to display
	sf::Texture npc_texture;
	if (!npc_texture.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Load a mouse texture to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile("assets\\player.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Setup NPC's Default Animated Sprite
	AnimatedSprite npc_animated_sprite(npc_texture);
	npc_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	// Setup NPC's Default Animated Sprite
	AnimatedSprite npc_animated_circle(npc_texture);
	npc_animated_circle.addFrame(sf::IntRect(3, 88, 84, 84));
	npc_animated_circle.addFrame(sf::IntRect(88, 88, 84, 84));
	npc_animated_circle.addFrame(sf::IntRect(173, 88, 84, 84));
	npc_animated_circle.addFrame(sf::IntRect(258, 88, 84, 84));
	npc_animated_circle.addFrame(sf::IntRect(343, 88, 84, 84));
	npc_animated_circle.addFrame(sf::IntRect(428, 88, 84, 84));

	AnimatedSprite npc_animated_cap(npc_texture);
	npc_animated_cap.addFrame(sf::IntRect(3, 173, 84, 84));
	npc_animated_cap.addFrame(sf::IntRect(88, 173, 84, 84));
	npc_animated_cap.addFrame(sf::IntRect(173, 173, 84, 84));
	npc_animated_cap.addFrame(sf::IntRect(258, 173, 84, 84));
	npc_animated_cap.addFrame(sf::IntRect(343, 173, 84, 84));
	npc_animated_cap.addFrame(sf::IntRect(428, 173, 84, 84));

	AnimatedSprite npc_animated_poly(npc_texture);
	npc_animated_poly.addFrame(sf::IntRect(3, 258, 84, 84));
	npc_animated_poly.addFrame(sf::IntRect(88, 258, 84, 84));
	npc_animated_poly.addFrame(sf::IntRect(173, 258, 84, 84));
	npc_animated_poly.addFrame(sf::IntRect(258, 258, 84, 84));
	npc_animated_poly.addFrame(sf::IntRect(343, 258, 84, 84));
	npc_animated_poly.addFrame(sf::IntRect(428, 258, 84, 84));

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);
	player_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	AnimatedSprite player_animated_circle(player_texture);
	player_animated_circle.addFrame(sf::IntRect(3, 88, 84, 84));
	player_animated_circle.addFrame(sf::IntRect(88, 88, 84, 84));
	player_animated_circle.addFrame(sf::IntRect(173, 88, 84, 84));
	player_animated_circle.addFrame(sf::IntRect(258, 88, 84, 84));
	player_animated_circle.addFrame(sf::IntRect(343, 88, 84, 84));
	player_animated_circle.addFrame(sf::IntRect(428, 88, 84, 84));

	// Setup the NPC
	GameObject &npc = NPC(npc_animated_sprite);

	// Setup the Player
	GameObject &player = Player(player_animated_sprite);

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(npc.getAnimatedSprite().getPosition().x, npc.getAnimatedSprite().getPosition().y);
	aabb_npc.max = c2V(
		npc.getAnimatedSprite().getPosition().x +
		npc.getAnimatedSprite().getGlobalBounds().width, 
		npc.getAnimatedSprite().getPosition().y +
		npc.getAnimatedSprite().getGlobalBounds().height);

	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);

	c2Circle circle_npc;
	circle_npc.r = 42;
	circle_npc.p = c2V(npc.getAnimatedSprite().getPosition().x + circle_npc.r, npc.getAnimatedSprite().getPosition().y + circle_npc.r );

	c2Capsule cap_npc;
	cap_npc.r = 16;
	cap_npc.a = c2V(npc.getAnimatedSprite().getPosition().x + cap_npc.r, npc.getAnimatedSprite().getPosition().y + cap_npc.r);
	cap_npc.b = c2V(npc.getAnimatedSprite().getPosition().x + 84, npc.getAnimatedSprite().getPosition().y + cap_npc.r);

	c2Circle circle_player;
	circle_player.r = 42;
	circle_player.p = c2V(player.getAnimatedSprite().getPosition().x + circle_player.r, player.getAnimatedSprite().getPosition().y + circle_player.r);

	// Initialize Input
	Input currentInput;
	Input previousInput;

	// Collision result
	int result = 0;

	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);
	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		
		// Move The NPC
		sf::Vector2f move_to(npc.getAnimatedSprite().getPosition().x + direction.x, npc.getAnimatedSprite().getPosition().y + direction.y);

		if (move_to.x < 0) {
			direction.x *= -1;
			move_to.x = 0;
		}
		else if (move_to.x + npc.getAnimatedSprite().getGlobalBounds().width >= 800) { 
			direction.x *= -1;
			move_to.x = 800 - npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.y < 0) { 
			direction.y *= -1;
			move_to.y = 0;
		}
		else if (move_to.y + npc.getAnimatedSprite().getGlobalBounds().height >= 600) {
			direction.y *= -1;
			move_to.y = 600 - npc.getAnimatedSprite().getGlobalBounds().height;
		}
		
		npc.getAnimatedSprite().setPosition(move_to);

		// Update NPC AABB set x and y
		aabb_npc.min = c2V(
			npc.getAnimatedSprite().getPosition().x, 
			npc.getAnimatedSprite().getPosition().y
		);

		aabb_npc.max = c2V(
			npc.getAnimatedSprite().getPosition().x +
			npc.getAnimatedSprite().getGlobalBounds().width,
			npc.getAnimatedSprite().getPosition().y +
			npc.getAnimatedSprite().getGlobalBounds().height
		);
		//update NPC circle
		circle_npc.p = c2V(npc.getAnimatedSprite().getPosition().x + circle_npc.r, npc.getAnimatedSprite().getPosition().y + circle_npc.r);
		//Update NCP Capsule
		cap_npc.a = c2V(npc.getAnimatedSprite().getPosition().x + cap_npc.r, npc.getAnimatedSprite().getPosition().y + 
			(84 - cap_npc.r) );
		cap_npc.b = c2V(npc.getAnimatedSprite().getPosition().x + (84 - cap_npc.r), npc.getAnimatedSprite().getPosition().y + cap_npc.r);
		// Update Player AABB
		aabb_player.min = c2V(
			player.getAnimatedSprite().getPosition().x, 
			player.getAnimatedSprite().getPosition().y
		);
		aabb_player.max = c2V(
			player.getAnimatedSprite().getPosition().x +
			player.getAnimatedSprite().getGlobalBounds().width, 
			player.getAnimatedSprite().getPosition().y + 
			player.getAnimatedSprite().getGlobalBounds().height
		);
		//Update Player as circle
		circle_player.p = c2V(player.getAnimatedSprite().getPosition().x + circle_player.r, player.getAnimatedSprite().getPosition().y + circle_player.r);

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
			case sf::Keyboard::Escape:
				//Closes Window
					window.close();
					break;
			default:
				break;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				//npc.setSprite(npc_animated_sprite);
				currentInput.setCurrent(Input::AABBToAABB);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				//npc.setSprite(npc_animated_circle);
				currentInput.setCurrent(Input::CircleToAABB);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				//npc.setSprite(npc_animated_cap);
				currentInput.setCurrent(Input::AABBToCap);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				currentInput.setCurrent(Input::CircleToAABB);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			{
				currentInput.setCurrent(Input::CircleToCap);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
			{
				currentInput.setCurrent(Input::CircleToCircle);
			}	
		}
		
		if (currentInput.getCurrent() != previousInput.getCurrent())
		{
			if (currentInput.getCurrent() == Input::AABBToAABB)
			{
				player.setSprite(player_animated_sprite);
				npc.setSprite(npc_animated_sprite);
			}
			else if (currentInput.getCurrent() == Input::AABBToCap)
			{
				player.setSprite(player_animated_sprite);
				npc.setSprite(npc_animated_cap);
			}
			else if (currentInput.getCurrent() == Input::CircleToAABB)
			{
				player.setSprite(player_animated_circle);
				npc.setSprite(npc_animated_sprite);
			}
			else if (currentInput.getCurrent() == Input::CircleToCap)
			{
				player.setSprite(player_animated_circle);
				npc.setSprite(npc_animated_cap);
			}
			else if (currentInput.getCurrent() == Input::CircleToCircle)
			{
				player.setSprite(player_animated_circle);
				npc.setSprite(npc_animated_circle);
			}
		}

		previousInput = currentInput;
		// Handle input to Player
		player.handleInput(currentInput);

		// Update the Player
		player.update();

		// Update the Player
		npc.update();

		// Check for collisions
		if (currentInput.getCurrent() == Input::AABBToAABB)
		{
			result = c2AABBtoAABB(aabb_player, aabb_npc);
		}
		else if (currentInput.getCurrent() == Input::AABBToCap)
		{
			result = c2AABBtoCapsule(aabb_player, cap_npc);
		}
		else if (currentInput.getCurrent() == Input::CircleToAABB)
		{
			result = c2CircletoAABB(circle_player, aabb_npc);
		}
		else if (currentInput.getCurrent() == Input::CircleToCap)
		{
			result = c2CircletoCapsule(circle_player, cap_npc);
		}
		else if (currentInput.getCurrent() == Input::CircleToCircle)
		{
			result = c2CircletoCircle(circle_player, circle_npc);
		}

		cout << ((result != 0) ? ("Collision") : "") << endl;
		if (result){
			player.getAnimatedSprite().setColor(sf::Color(255,0,0));
			//input.setCurrent(1);
		}
		else {
			player.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
			//input.setCurrent(0);
		}

		// Clear screen
		window.clear();

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSprite());

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};