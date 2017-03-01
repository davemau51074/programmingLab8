#pragma once


#include "entityx/Entity.h"

enum class WayPointType
{
	WT_Small,
};

struct WayPoint : public entityx::Component<WayPoint>
{
	WayPoint(WayPointType type = WayPointType::WT_Small);

	WayPointType m_type;
};

