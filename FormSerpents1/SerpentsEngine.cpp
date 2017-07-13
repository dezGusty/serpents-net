#include "StdAfx.h"
#include "SerpentsEngine.h"

#include "Serpent.h"
#include "Map.h"
#include "GusRandom.h"

#include <stdio.h>

namespace Serpents
{

	SerpentsEngine::SerpentsEngine(void)
	{
		serpent = NULL;
		map = NULL;

		KeyDefiner *keyDefiner = new KeyDefiner();
		keyController = new SerpentsController(*keyDefiner);

		setDefaultKeys();

		bonusController = new BonusController();
		bonusController->setMaximumAllowerBonuses(10);

		gameOver=false;
		gamePaused=false;
		gameQuitWish=false;
		canExit=false;

		randomer = createRandomObject();
	}


	SerpentsEngine::~SerpentsEngine(void)
	{
		SAFE_DELETE( serpent );
		SAFE_DELETE( map );
		SAFE_DELETE( keyController );
		SAFE_DELETE( bonusController );
	}


	RandomInterface * SerpentsEngine::createRandomObject()
	{
		return new GusRandom();
	}


	Serpent& SerpentsEngine::getSerpent( int /*index */)
	{
		if( ! serpent )
		{
			serpent = new Serpent();
		}

		return *serpent;
	}


	void SerpentsEngine::onKeyDown(int keyCode)
	{
		if(keyCode==keyController->menu.keyBinding)
		{
			gameQuitWish=true;
			gamePaused=true;
		}
		if(keyCode==keyController->pause.keyBinding)
		{
			gamePaused=!gamePaused;
			//TODO: daca sunt ceva taste apasate, anuleaza-le starea apasata.
		}
		if(!gamePaused)
		{
			if( keyCode==keyController->left.keyBinding || keyCode == keyController->left.alternateKeyBinding )
			{
				keyController->left.pressed = true;
			}
			if( keyCode==keyController->right.keyBinding || keyCode == keyController->right.alternateKeyBinding )
			{
				keyController->right.pressed = true;
			}
			if( keyCode==keyController->accelerate.keyBinding || keyCode == keyController->accelerate.alternateKeyBinding )
			{
				keyController->accelerate.pressed = true;
			}
			if( keyCode==keyController->decelerate.keyBinding || keyCode == keyController->decelerate.alternateKeyBinding )
			{
				keyController->decelerate.pressed = true;
			}
		}
	}


	void SerpentsEngine::onKeyUp(int keyCode)
	{
		if(!gamePaused)
		{
			if( keyCode==keyController->left.keyBinding || keyCode == keyController->left.alternateKeyBinding )
			{
				keyController->left.pressed = false;
			}
			if( keyCode==keyController->right.keyBinding || keyCode == keyController->right.alternateKeyBinding )
			{
				keyController->right.pressed = false;
			}
			if( keyCode==keyController->accelerate.keyBinding || keyCode == keyController->accelerate.alternateKeyBinding )
			{
				keyController->accelerate.pressed = false;
			}
			if( keyCode==keyController->decelerate.keyBinding || keyCode == keyController->decelerate.alternateKeyBinding )
			{
				keyController->decelerate.pressed = false;
			}
		}
	}


	void SerpentsEngine::onTimeGoesBy(double timeUnits)
	{
		reactToInput(timeUnits);
		//	muta serpentul cat trebuie, in functie de trecerea timpului.

		if( serpent )
		{
			serpent->move( timeUnits );

			//	TODO: fa un update la collision matrix
			//this->map->
		}

		if( bonusController )
		{
			bonusController->onTimeGoesBy( timeUnits );
			//
			long r= randomer->random(10000);
			if( r < 50 && bonusController->getNumberOfItems() < bonusController->getMaximumAllowedBonuses() )
			{
				DPOINT point;
				point.x = randomer->random(800);
				point.y = randomer->random(600);
				bonusController->spawnNewBonus( point );
				//TODO: FUTURE USE
				//	DPOINT sz = bonusController->getDefaultSize();
				//	DPOINT loc = map->getFreeSpotForSize( sz );
				//	bonusController->spawnNewBonus( loc );
				

				//System::Diagnostics::Trace::WriteLine("XXXXXX = " + point.x + "," + point.y );
				//System::Diagnostics::Trace::WriteLine("XXXXXX items=" + bonusController->getNumberOfItems() );
			}
			//System::Diagnostics::Trace::WriteLine("Random = " + r );
			//System::Diagnostics::Trace::Flush();
		}

		// verifica coliziuni serpents cu self

		//	verifica coliziuni intre diferiti serpents

		//	verifica coliziuni intre serpents si bonusuri statice

		verifyBonusCapture();

		//	verifica conditii victorie/infrangere si modifica starea jocului

	}


	void SerpentsEngine::reactToInput(double timeUnits)
	{
		if( keyController->left.pressed )
		{
			serpent->turn( + 1, false );
		}
		if( keyController->right.pressed )
		{
			serpent->turn( -1, false );
		}
		if( keyController->accelerate.pressed )
		{
			serpent->setSpeed( serpent->getSpeed() + serpent->getSpeedStep() );
		}
		if( keyController->decelerate.pressed )
		{
			serpent->setSpeed( serpent->getSpeed() - serpent->getSpeedStep() );
		}
	}


	void SerpentsEngine::setDefaultKeys()
	{
	}


	void SerpentsEngine::startGame()
	{
		SAFE_DELETE( serpent );
		SAFE_DELETE( map );

		map = new Map(800,600);
		serpent = new Serpent();
		serpent->setSpawnPosition(100,100);
		serpent->setAngleInRadians(0);
		serpent->setTurnSpeed(1.7);
		serpent->setSpeedInfluenceOnTurn(1);
		serpent->setMinAllowedSpeed( 0.1 );
		serpent->setSpeed( 0.01 );// TODO: testing value; ideea e sa fie 10 pixeli pe secunda ( 0.01 * 1000 millis );
		serpent->setMaxAllowedSpeed(9999);
	}


	void SerpentsEngine::verifyBonusCapture()
	{
		if( serpent )
		{
			for( int i=0; i< this->bonusController->getNumberOfItems(); i++ )
			{
				if( bonusController->getItemAt(i)->intersectsWith( * serpent->getBodyPart(0) ) )
				{
					//TODO: adauga puncte

					bonusController->getItemAt(i)->setTimeToLive( -1 );
					serpent->addParts(1);
				}
			}
		}
	}


	void SerpentsEngine::verifyCollisions()
	{
	}


	void SerpentsEngine::verifyVictory()
	{
	}
}