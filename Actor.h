#pragma once
#include <stdio.h>
#include "TVector2D.h"
#include <stdint.h>

class Actor
{
public:
	virtual void Update(float fElapsedTime) {};

protected:
	// The world position
	TVector2D<float>* TLocation = new TVector2D<float>(0, 0);

	// Hitbox for actor initilised to 0
	TVector2D<uint8_t>* THitBot = new TVector2D<uint8_t>(0, 0);
};

