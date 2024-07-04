#pragma once

#include"FlipbookActor.h"

class Player : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Player ( );
	virtual ~Player ( ) override;

	virtual void BeginPlay ( )override;
	virtual void Tick ( )override;
	virtual void Render ( HDC hdc )override;

protected:

};