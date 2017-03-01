#include "HUDSystem.h"


HUDSystem::HUDSystem(sf::RenderWindow & window, const std::shared_ptr<sf::Font>& font)
	: m_window(window)
	, m_font(font)
	, m_timer(0)
{
	m_pointT.setFont(*m_font);
	m_pointT.setCharacterSize(20);
	m_pointT.setColor(sf::Color::Black);
	m_pointT.setString("Going to Node:" + std::to_string(0));
	m_pointT.setPosition(sf::Vector2f(1200 / 2, 30));

	m_timerT.setFont(*m_font);
	m_timerT.setCharacterSize(50);
	m_timerT.setColor(sf::Color::Black);
	m_timerT.setPosition(sf::Vector2f(1250/2, 60));
	m_timerT.setString(std::to_string(m_timer));
}

/// <summary>
/// update the hud system
/// </summary>
/// <param name="entities"></param>
/// <param name="events"></param>
/// <param name="dt"></param>
void HUDSystem::update(entityx::EntityManager & entities, entityx::EventManager & events, double dt)
{

	//m_timer += (1.f / 60.f);
	m_window.draw(m_pointT);

	m_timerT.setString("Time " + std::to_string(m_timer));
	m_window.draw(m_timerT);
}

/// <summary>
/// configure method that subsribes an event to the hud system
/// </summary>
/// <param name="events"></param>
void HUDSystem::configure(entityx::EventManager& events)
{
	events.subscribe<EvNextWayPoint>(*this);
}

/// <summary>
/// reciver method for hud system
/// </summary>
/// <param name="e"></param>
void HUDSystem::receive(const EvNextWayPoint & e)
{
	m_currentPathPoint = e.m_nextWayPoint;
	m_timer = e.m_timer;

	m_pointT.setString("Going to Node:" + std::to_string(m_currentPathPoint + 1));
	if (m_currentPathPoint == 0)
	{
		//m_timer = 0;
	}
}


HUDSystem::~HUDSystem()
{
}