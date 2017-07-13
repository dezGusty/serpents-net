#pragma once

#include "BodyPart.h"
#include "PathStrip.h"

using namespace System::Collections;
using namespace GustyUtils;

namespace Serpents
{

#define MIN_TURN_SPEED 0
#define MAX_TURN_SPEED 5
#define DEFAULT_MIN_SPEED 0
#define DEFAULT_MAX_SPEED 9999


	//
	//	Clasa de reprezentare a unui serpent.
	//

	class Serpent
	{
	public:

		//
		//	Constructor.
		//

		Serpent( int initialLength = 5 );

		//
		//	Destructor. Trebuie sterse toate bodyparts-urile alocate.
		//

		~Serpent(void);

		//
		//	Adauga un numar de bodyparts la serpent. Adaugarea se face la coada.
		//

		virtual void addParts( int numParts = 1 );

		//
		//	Elimina un numar de bodyparts din serpent. Eliminarea se face incepand cu elementul cel mai din coada.
		//

		virtual void removeParts( int numParts = 1 );

		//
		//	Seteaza pozitia de unde apare serpentul. Toate bodyparts vor fi creeate la aceeasi pozitie, dar numai capul va fi vizibil si
		//	spawned. Restul partilor vor fi "spawned" imediat ce va fi loc pentru ele.
		//

		virtual void setSpawnPosition( double x, double y );

		//
		//	Initiaza procesul de spawn la o anumita locatie.
		//

		virtual void spawn( double x, double y );

		//
		//	Initiaza procesul de spawn la locatia presetata cu setSpawnPosition.
		//

		virtual void spawn();

		//
		//	Seteaza directia serpentului, modificand directia capului serpentului. In mod normal se seteaza si directia restului
		//	componentelor corpului (bodyparts), deoarece aceasta functie se va folosi la spawning in principal.
		//

		virtual void setAngleInRadians( double angle, bool affectAll = true );

		//
		//	Muta serpentul, simuland miscarea lui (prin teleportare) la pozitia pe care ar ocupa-o dupa un numar de unitati de timp.
		//

		virtual void move( double timeUnits );

		//
		//	Seteaza viteza pentru serpent. Valoarea este exprimata in unitati de viteza ale jocului (game speed units).
		//	1 speed unit = 1 distance unit / 1 time unit.
		//

		virtual void setSpeed( double speedUnits );

		//
		//	Intoarce serpentul catre stanga sau dreapta cu un anumit unghi. Valoarea specificata poate fi exprimata fie in radiani
		//	(default), fie in grade 0-360, caz in care trebuie setat flagul useRadians pe false.
		//

		virtual void turn( double anAngle, bool useRadians = true );

		//
		//	Getter pentru viteza serpentului (exprimata in bodyparts).
		//

		virtual double getSpeed(){ return speed;}

		//
		//	Getter pentru lungimea serpentului. (Viteza de miscare a serpentului masurata in game speed units.)
		//

		int getLength(){ return bodyParts.getLength(); }

		//
		//	Functie de convenienta ce returneaza al index-lea bodypart din cadrul unui serpent. Pointerul returnat este NULL daca indexul
		//	specificat este invalid.
		//

		virtual BodyPart* getBodyPart(int index);

		//
		//	Functie de convenienta de generare a unui bodypart. Bodypart-ul nu se adauga automat la sirul de elemente al serpentului.
		//

		virtual BodyPart* CreateBodyPart(){return new BodyPart();}

		//
		//	Seteaza viteza de virare (cu care serpentul poate coti stanga/dreapta). 
		//

		void setTurnSpeed( double newTurnSpeed );

		//
		//	Seteaza dimensiunile bodypart-urilor care apar.
		//

		virtual void setBodyPartSpawnSize( double width, double height );

		//
		//	Callback la adaugarea unui bodypart.
		//

		virtual void onAddedBodyPart();

		//
		//	Callback la eliminarea unui bodypart.
		//

		virtual void onRemovedBodyPart();

		//
		//	Getter pt. influenta vitezei de miscare asupra vitezei de cotire
		//

		virtual double getSpeedInfluenceOnTurn(){ return speedInfluenceOnTurn; }
		virtual void setSpeedInfluenceOnTurn( double value ){ speedInfluenceOnTurn = value; }

		virtual double getMaxAllowedSpeed(){ return maxSpeed; }
		virtual double getMinAllowedSpeed(){ return minSpeed; }
		virtual double getSpeedStep(){ return speedStep; }
		virtual void setMinAllowedSpeed( double value ){ minSpeed = value; setSpeed(getSpeed()); }
		virtual void setMaxAllowedSpeed( double value ){ maxSpeed = value; setSpeed(getSpeed()); }
		virtual void setSpeedStep( double value ){ speedStep = value; }

	protected:

		//	Pozitia care se poate salva pt. identificarea locului la care trebuie sa apara (prin "spawn") serpentul.
		SPoint<double> spawnPosition;

		//	Dimensiunile cu care va fi generat un nou bodypart.
		SPoint<double> spawnBodyPartSize;

		//	Lungimea maxima (masurata in numar de bodyparts) permisa serpentului.
		int maxlength;

		//	Lungimea minima (masurata in numar de bodyparts) permisa serpentului.
		int minlength;

		double minSpeed;
		double maxSpeed;
		//	Cand creste/descreste viteza, creste cu aceasta valoare.
		double speedStep;

		//	Viteza de miscare a serpentului masurata in game speed units.
		double speed;

		//	Viteza de virare (cu care serpentul poate coti stanga/dreapta). 
		double turnSpeed;

		//	Influenta pe care o are viteza de miscare asupra vitezei de cotire
		double speedInfluenceOnTurn;

		//	Colectia de bodyparts aferenta serpentului. Sir de pointeri de trebuie dealocat in destructor.
		GusArray<BodyPart> bodyParts;

		//	Colectia de segmente care indica path-ul serpentului

		public:
		SerpentPath * path;
	};
}