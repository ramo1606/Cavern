#pragma once
#include "CollideActor.h"

using namespace Common;

constexpr int BOLT_SPEED = 7;

class Bolt : public CollideActor
{
public:
	Bolt(Vector2 pos, float dirX);
	Bolt(const Bolt&) = default;
	Bolt& operator=(const Bolt&) = default;
	virtual ~Bolt() = default;

	void update() override;
	bool isActive() const { return m_Active; };

private:
	bool m_Active{ true };
};
