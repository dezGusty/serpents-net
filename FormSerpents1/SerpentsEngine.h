#pragma once

//
//	includes
//
#include "Serpent.h"
#include "Map.h"
#include "KeyController.h"
#include "SerpentsController.h"
#include "Bonus.h"
#include "RandomInterface.h"

namespace Serpents
{

	//	Forward class des

	//
	//	Clasa de control al partii de background-logic in sistem.
	//

	class SerpentsEngine
	{
	public:

		//
		//	toate starile in care se poate afla la un moment dat jocul.
		//

		typedef enum
		{
			GSUndefined,
			GSMainMenu,
			GSGameInitialising,
			GSGameRunning,
			GSGamePaused,
			GSGameFinished,
			NumberOfGameStatuses
		}GameStatus;

		//
		//	Constructor.
		//

		SerpentsEngine(void);

		//
		//	Destructor.
		//

		~SerpentsEngine(void);

		//
		//	Functia de generare a unui obiect ce va fi folosit mai departe pentru generarea de numere aleatoare. Se poate supraincarca in descendenti.
		//

		virtual RandomInterface * createRandomObject();

		//
		//	Obtine controllerul de bonusuri
		//

		virtual BonusController & getBonusController(){ return *bonusController; }

		//
		//	Obtine un serpent
		//

		virtual Serpent& getSerpent( int index = 0 );

		//
		//	Reactioneaza la apasarea unei taste. Aici e punctul in care incepe apasarea unei taste
		//

		virtual void onKeyDown( int keyCode );

		//
		//	Reactioneaza la eliberarea unei taste.
		//

		virtual void onKeyUp( int keyCode );

		//
		//	Reactioneaza la trecerea timpului
		//

		virtual void onTimeGoesBy( double timeUnits );

		//
		//	Reactioneaza la trecerea timpului pentru input (tastele & sticky keys apasate, butoanele de mouse apasate)
		//

		virtual void reactToInput( double timeUnits );


		//
		//	Set the default controls.
		//

		virtual void setDefaultKeys();

		//
		//	Initializeaza jocul
		//

		virtual void startGame();

		//
		//	Verifica daca s-a ridicat un bonus.
		//

		virtual void verifyBonusCapture();

		//
		//	Verifica daca vreun obiect de pe harta a intrat in coliziune cu un altul
		//

		virtual void verifyCollisions();

		//
		//	Verifica daca conditiile pt. ca 1 din jucatori sa fie invingator sau invins sunt indeplinite, iar jocul sa se poata termina.
		//

		virtual void verifyVictory();

	protected:
		bool gameOver;
		bool gamePaused;
		bool gameQuitWish;
		bool canExit;

		Serpent * serpent;
		Map * map;
		RandomInterface * randomer;

		SerpentsController *keyController;
		BonusController * bonusController;
	};
}