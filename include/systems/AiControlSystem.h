#pragma once

#include "entityx/System.h"
#include "entityx/Event.h"
#include "systems/Events.h"
#include "components/Ai.h"
#include "components/Wall.h"
#include "components/Volume.h"
#include "components/Position.h"
#include "components/Display.h"
#include "WayPoint.h"

class AiControlSystem
      : public entityx::System<AiControlSystem>
      , public entityx::Receiver<AiControlSystem>
{
public:

   AiControlSystem();

   void configure(entityx::EventManager& events);

   void receive(const EvReportPlayerId& e);

   //void recieve(const EvReportWayPointId& e);

   void receive(const entityx::ComponentAddedEvent<Ai>& e);

   void receive(const entityx::ComponentAddedEvent<Wall>& e);

   void receive(const entityx::ComponentAddedEvent<WayPoint>& e);

   void update(entityx::EntityManager &entities,
               entityx::EventManager &events,
               double dt);

private:
    // Need some kind of smart pointer to the AI class
	std::unique_ptr<TankAi> m_tankAi;

	entityx::Entity::Id m_playerId;
	entityx::Entity::Id m_wayPoint;

	std::vector<sf::CircleShape> m_obstacles;
	std::vector<sf::CircleShape> m_waypoint;

	std::vector<entityx::Entity::Id> m_ids;
};

