#pragma once

#include <SFML/Graphics.hpp>
#include "entityx/System.h"
#include "systems/Events.h"
#include "components/Position.h"
#include "components/Background.h"
#include "components/Ai.h"
#include "Ai\TankAi.h"
#include "ScreenSize.h"
#include "ResourcePath.hpp"
#include "entityx/Entity.h"
#include "WayPoint.h"
using namespace entityx;


class  HUDSystem
	: public entityx::System<HUDSystem>
	, public entityx::Receiver<HUDSystem>
{
public:
	HUDSystem(sf::RenderWindow& window, const std::shared_ptr<sf::Font>& font);

	/// <summary>
	/// updates and renders pathpoints to the screen
	/// </summary>
	/// <param name="entities">The EntityX entity manager</param>
	/// <param name="events">The EntityX event manager</param>
	/// <param name="dt">The time between frames</param>
	void update(entityx::EntityManager &entities, entityx::EventManager &events, double dt);

	/// <summary>
	/// configure used to subscribe to an event 
	/// </summary>
	/// <param name="events"></param>
	void configure(entityx::EventManager& events);

	void receive(const EvNextWayPoint& e);

	~HUDSystem();

private:

	/// <summary>
	/// Reference to render window in the game
	/// </summary>
	sf::RenderWindow& m_window;

	/// <summary>
	/// font used for text
	/// </summary>
	std::shared_ptr<sf::Font> m_font;

	/// <summary>
	/// text instance used to display current path point
	/// </summary>
	sf::Text m_pointT;

	/// <summary>
	/// text instance used to display the timer
	/// </summary>
	sf::Text m_timerT;

	/// <summary>
	/// instance of the ai tank id
	/// used to get the id of the next path point
	/// </summary>
	int m_currentPathPoint;


	double m_timer;
	float m_accumulatedTime;
	sf::Time m_elapsed;
	sf::Clock m_clock;

};
