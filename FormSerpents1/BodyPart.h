#pragma once

//
//	Forward class def. pt. clasa de reprezentare a serpentului.
//

class Serpent;

#include "GusUtils.h"
using namespace GustyUtils;

#include "MapObject.h"

namespace Serpents
{
	class Serpent;

	//
	//	Un bodypart cu acest speed va mosteni viteza de la serpent. Acesta va fi cazul general.
	//
#define SPEED_INHERITED -1

	//
	//	Clasa ce constituie un singur segment din corpul unui serpent.
	//
	class BodyPart : public MapObject
	{
	public:
		//
		//	Constructor.
		//

		BodyPart(void);

		//
		//	Copy constructor. Probabil va fi util.
		//

		BodyPart( BodyPart & );

		//
		//	Destructor.
		//

		~BodyPart();

		//
		//	Obtine unghiul ce indica directia serpentului; valoarea in grade (0-360°)	
		//

		double getAngleInDegrees();

		//
		//	Obtine unghiul ce indica directia serpentului; valoarea in radiani.
		//

		double getAngleInRadians();

		//
		//	Obtine viteza cu care se misca bodypart-ul. Pentru viteza "-1", aceasta se mosteneste de la serpent (e constanta pt. 
		//	toate bodyparts)
		//

		double getSpeed();

		//
		//	Afla daca a fost generat bodypart-ul. Un bodypart care nu e spawned este un bodypart care nu este inca vizibil, deoarece tocmai
		//	a fost adaugat si nu ar trebui sa aiba aceeasi locatie precum alt bodypart.
		//

		bool isSpawned();

		
		//
		//	Verifica daca un bodypart intra in coliziune cu alt bodypart.
		//

		bool collidesWith( BodyPart & rhs );

	protected:

		//	Unghiul (calculat conform cercului trigonometric) corespunzator directiei in care se indreapta serpentul.
		double angleInRads;

		//	Viteza cu care se misca bodypart-ul. In game units.
		double speed;

		//	Arata daca a fost generat (vizibil) bodypart-ul.
		bool spawned;

		friend class Serpents::Serpent;
	};
}