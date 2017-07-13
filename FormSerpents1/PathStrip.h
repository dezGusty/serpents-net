#pragma once

#include "GusUtils.h"
using namespace GustyUtils;

namespace Serpents
{

	class BodyPart;

	//
	//	Clasa ce va defini bucatelele de traiectorie pe care va merge serpentul.
	//

	class PathStrip
	{
	public:

		//
		//	Constructor default.
		//

		PathStrip();

		//
		//	Constructor uzual.
		//

		PathStrip( double xhead, double yhead, double xtail, double ytail );

		//
		//	Copy constr.
		//

		PathStrip( PathStrip & );

		//
		//	Destructor. Nu se folosesc pointeri, deci nu are nimic de facut.
		//

		~PathStrip(void);

		//
		//	Calculeaza dimensiunea segmentului indicat. (Se aplica t. lui Pitagora)
		//

		double getLength();

		//
		//	Obtine coordonatele unui sub-segment. Trebuie neaparat ca partialSegmentSize sa fie mai mica decat 
		//	valoarea intoarsa de getLength(), altfel locatia maxima permisa va fi returnata. Pentru a intoarce
		//	punctul de pe dreapta, fara limitarea la dimensiunea lui getLength, se specifica true la allowGreaterSize
		//

		DPOINT getLocationFromHead( double partialSegmentSize, bool allowGreaterSize = false );

		DPOINT getHeadLocation(){ return headLocation; }
		DPOINT getTailLocation(){ return tailLocation; }

	protected:
		DPOINT headLocation;
		DPOINT tailLocation;

		friend class SerpentPath;
	};


	//
	//	Clasa ce va controla traiectoria unui Serpent
	//

	class SerpentPath
	{
	public:

		SerpentPath();

		//
		//	Calculeaza coordonatele unde vor fi pozitionate bodypart-urile (toate). Rezultatul intors e un sir de elemente.
		//	Sirul de coordonate ale bodyparts se specifica ca parametru. Aici se elimina si bucatile suplimentare din path.
		//

		virtual void getAndSetPositionOfAllParts( GusArray<BodyPart> &parts/*, int len */);

		//
		//	Adauga un strip la finalul pathului. Aceasta functie se va folosi in general pentru generarea de noi bodyparts, care
		//	vor fi nespawned
		//

		virtual void addStrip( int numParts = 1 );

		//
		//	Relocalizeaza capul listei. Se adauga un pathstrip (se lungeste lista automat). Se va elimina la repozitionarea 
		//	bodyparts
		//

		virtual void moveHeadStrip( double x, double y, double minLength = -1 );

		//
		//	Elimina un strip de la finalul path-ului.
		//

		virtual void removeStrip();

		//
		//	Obtine coordonatele de la un anumit index.
		//

		virtual DPOINT getCoords( int index );

		//
		//	Obtine un segment.
		//

		virtual PathStrip* getStrip( int index ){ return pathStrips[index];}

		//
		//	Getter pt. lungimea sirului de stripuri
		//

		virtual int getLength(){ return pathStrips.getLength(); }

	protected:
		bool partArrangementWasCompleted;

		GusArray<PathStrip> pathStrips;
		DPOINT absoluteTail;
	};
}