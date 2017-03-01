#include "systems/AiControlSystem.h"

AiControlSystem::AiControlSystem()
{
}

void AiControlSystem::configure(entityx::EventManager& events)
{  
   events.subscribe<EvReportPlayerId>(*this);
   events.subscribe<entityx::ComponentAddedEvent<Ai>>(*this);
   events.subscribe<entityx::ComponentAddedEvent<Wall>>(*this);
   events.subscribe<entityx::ComponentAddedEvent<WayPoint>>(*this);
}

void AiControlSystem::receive(const EvReportPlayerId& e)
{
	m_playerId = e.m_playerId;
	
}

void AiControlSystem::receive(const entityx::ComponentAddedEvent<Ai>& e)
{
    Ai::Handle ai = e.component;
    m_tankAi.reset(new TankAi(m_obstacles, ai->m_id, m_waypoint));	// id of turret
}

void AiControlSystem::receive(const entityx::ComponentAddedEvent<Wall>& e)
{
	entityx::Entity ent = e.entity;
	Volume::Handle wallVol = ent.component<Volume>();
	Position::Handle wallPos = ent.component<Position>();
	Display::Handle wallDisplay = ent.component<Display>();
	
	sf::CircleShape circle(wallVol->m_box.getRect().width * 1.5f);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(wallPos->m_position);
	m_obstacles.push_back(circle);	
}

void AiControlSystem::receive(const entityx::ComponentAddedEvent<WayPoint>& e)
{
	entityx::Entity ent = e.entity;
	//Volume::Handle wayVol = ent.component<Volume>();
	Position::Handle wayPos = ent.component<Position>();
	//Display::Handle wayDisplay = ent.component<Display>();

	entityx::Entity::Id id = ent.id();
	m_ids.push_back(id);

	sf::CircleShape circle(40);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(wayPos->m_position);
	m_waypoint.push_back(circle);
}

void AiControlSystem::update(entityx::EntityManager& entities,
                             entityx::EventManager& events,
                             double dt)
{
   Ai::Handle ai;
   for (entityx::Entity entity : entities.entities_with_components(ai))
   {
	   m_tankAi->update(m_playerId, 
		                    entity.id(),
							m_ids.at(m_tankAi->getCurrentNode()),
							events,
							entities, 
							dt);
   }
}
