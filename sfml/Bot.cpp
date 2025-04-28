#include "Bot.h"

void Bot::update(Game& game)
{
	const auto& enemies = game.getEnemies();
	if (!enemies.empty()) {
		const sf::Vector2f& pos = sf::Vector2f(enemies[0].getPosition().x, enemies[0].getPosition().y);
		//sf::Mouse::setPosition(sf::Vector2i(static_cast<int>(pos.x + 10), static_cast<int>(pos.y + 10)), *game.getWindow());
		if(enemies[0].getPosition().y > 100)
		game.botClickAt(pos);
	}
}
