#include "StdAfx.h"
#include "PathStrip.h"
#include "BodyPart.h"
#include <math.h>
#include <stdio.h>

namespace Serpents
{

	PathStrip::PathStrip()
	{
		headLocation.x = 0;
		headLocation.y = 0;

		tailLocation.x = 0;
		tailLocation.y = 0;
	}


	PathStrip::PathStrip( double xhead, double yhead, double xtail, double ytail )
	{
		this->headLocation.x = xhead;
		this->headLocation.y = yhead;

		this->tailLocation.x = xtail;
		this->tailLocation.y = ytail;
	}


	PathStrip::PathStrip( PathStrip & rhs )
	{
		this->headLocation.x = rhs.headLocation.x;
		this->headLocation.y = rhs.headLocation.y;

		this->tailLocation.x = rhs.tailLocation.x;
		this->tailLocation.y = rhs.tailLocation.y;
	}


	PathStrip::~PathStrip(void)
	{
	}


	double PathStrip::getLength()
	{
		return GustyUtils::GetSegmentLength( tailLocation.x, tailLocation.y, headLocation.x, headLocation.y );
	}


	DPOINT PathStrip::getLocationFromHead( double partialSegmentSize, bool allowGreaterSize )
	{
		DPOINT ret = this->headLocation;

		double len = getLength();
		if( len > 0 )
		{
			if( partialSegmentSize > len && !allowGreaterSize )
			{
				partialSegmentSize = len;
			}
			double ratio = partialSegmentSize / len;
			ret.x = headLocation.x - (headLocation.x - tailLocation.x) * ratio;
			ret.y = headLocation.y - (headLocation.y - tailLocation.y) * ratio;

			if( ratio >= 1 )
			{
				//System::Diagnostics::Trace::WriteLine("getLocationFromHead, came with ratio=" + ratio );
				//System::Diagnostics::Trace::Flush();
			}
		}
		return ret;
	}



	//
	// ------------------------------------------------------------------------------
	//


	SerpentPath::SerpentPath()
	{
		partArrangementWasCompleted = true;
	}


	void SerpentPath::addStrip( int numParts )
	{
		int partsToAdd = numParts;
		if( partsToAdd <= 0 )
		{
			return;
		}
		for( int i=0; i<partsToAdd; i++ )
		{
			PathStrip * strip = new PathStrip();

			//	daca nu mai este loc in sir, aloca un alt sir, copiaza elementele si muta referinta

			if( getLength() > 0 )
			{
				strip->headLocation.x = pathStrips[ getLength() - 1 ]->tailLocation.x;
				strip->headLocation.y = pathStrips[ getLength() - 1 ]->tailLocation.y;
			}

			pathStrips.add( strip );
		}
	}


	//
	//	Calculeaza coordonatele unde vor fi pozitionate bodypart-urile (toate). Rezultatul intors e un sir de elemente.
	//	Sirul de coordonate ale bodyparts se specifica ca parametru. Aici se elimina si bucatile suplimentare din path.
	//

	void SerpentPath::getAndSetPositionOfAllParts( GusArray<BodyPart> &parts/*, int len*/ )
	{
		double extraDistance = 0;
		int tempIndex = 0;
		int latestSetIndex = 0;

		//	parcurge toate bodyparts

		//System::Diagnostics::Trace::WriteLine("---------------------------");
		//System::Diagnostics::Trace::WriteLine("getAndSetPositionOfAllParts; len=" + parts.getLength());

		int lastSpawned = 0;
		parts[0]->setLocation( pathStrips[0]->headLocation );
		for( int i=1; i < parts.getLength() && tempIndex < getLength() ; i++ )
		{
			if( parts[i]->isSpawned() )
			{
				//double tempLen = pathStrips[ tempIndex ]->getLength();
				//extraDistance += GustyUtils::GetSegmentLength( parts[i]->getLocation().x, parts[i]->getLocation().y, parts[i-1]->getLocation().x, parts[i-1]->getLocation().y );
				extraDistance += parts[i]->getSizeFromCenter() + parts[i-1]->getSizeFromCenter() ;

				while( extraDistance >= pathStrips[ tempIndex ]->getLength() && tempIndex < getLength() )
				{
					extraDistance -= pathStrips[ tempIndex ]->getLength();
					tempIndex ++;
				}

				//{
				//	System::Diagnostics::Trace::WriteLine("i=" + i);
				//	System::Diagnostics::Trace::WriteLine("tempIndex=" + tempIndex);
				//	System::Diagnostics::Trace::WriteLine("extraDist=" + extraDistance);
				//}

				parts[i]->setLocation( pathStrips[ tempIndex ]->getLocationFromHead( extraDistance ) );
				latestSetIndex = i;

				

				lastSpawned = i;
			}
			else
			{
				break;
			}
			//System::Diagnostics::Trace::WriteLine("parts[" + i + "] (x,y)= (" + parts[i]->getLocation().x + "," 
			//	+ parts[i]->getLocation().y + ")" );
			//System::Diagnostics::Trace::WriteLine("strips[" + tempIndex + "].head=(" + pathStrips[tempIndex]->headLocation.x
			//	+"," + pathStrips[tempIndex]->headLocation.y + "), tail=(" + pathStrips[tempIndex]->tailLocation.x + "," + pathStrips[tempIndex]->tailLocation.y + ")" );
		}

		//System::Diagnostics::Trace::Flush();

		//partArrangementWasCompleted = true;
		//if( latestSetIndex < getLength()-1 )
		//{
		//	partArrangementWasCompleted = false;
		//}
		//System::Diagnostics::Trace::WriteLine("PartArrangementCompleted=" + partArrangementWasCompleted );
	}



	DPOINT SerpentPath::getCoords(int index)
	{
		DPOINT ret = {0,0};
		if( index < getLength() )
		{
			ret.x = pathStrips[index]->headLocation.x;
			ret.y = pathStrips[index]->headLocation.y;
		}
		return ret;
	}


	//
	//	Relocalizeaza capul listei. Se adauga un pathstrip (se lungeste lista automat). Se va elimina la repozitionarea 
	//	bodyparts
	//

	void SerpentPath::moveHeadStrip( double x, double y, double minLength )
	{
		if( getLength() > 0  )
		{
			if( pathStrips[0]->getLength() > minLength && minLength != -1 )
			{
				for( int i = getLength()-1 ; i>0 ; i-- )
				{
					pathStrips[i]->headLocation.x = pathStrips[i-1]->headLocation.x;
					pathStrips[i]->headLocation.y = pathStrips[i-1]->headLocation.y;
					pathStrips[i]->tailLocation.x = pathStrips[i-1]->tailLocation.x;
					pathStrips[i]->tailLocation.y = pathStrips[i-1]->tailLocation.y;
				}
				if( getLength() >= 1 )
				{
					pathStrips[0]->headLocation.x = x;
					pathStrips[0]->headLocation.y = y;
					if( getLength() > 1 )
					{
						pathStrips[0]->tailLocation.x = pathStrips[1]->headLocation.x;
						pathStrips[0]->tailLocation.y = pathStrips[1]->headLocation.y;
					}
				}
			}
			else
			{
					pathStrips[0]->headLocation.x = x;
					pathStrips[0]->headLocation.y = y;
			}
		}

		/*if( partArrangementWasCompleted )
		{
			if( getLength() > 0 )
			{
				this->absoluteTail = pathStrips[getLength()-1]->tailLocation;
			}

			for( int i = getLength()-1 ; i>0 ; i-- )
			{
				pathStrips[i]->headLocation.x = pathStrips[i-1]->headLocation.x;
				pathStrips[i]->headLocation.y = pathStrips[i-1]->headLocation.y;
				pathStrips[i]->tailLocation.x = pathStrips[i-1]->tailLocation.x;
				pathStrips[i]->tailLocation.y = pathStrips[i-1]->tailLocation.y;
			}
			if( getLength() >= 1 )
			{
				pathStrips[0]->headLocation.x = x;
				pathStrips[0]->headLocation.y = y;
				if( getLength() > 1 )
				{
					pathStrips[0]->tailLocation.x = pathStrips[1]->headLocation.x;
					pathStrips[0]->tailLocation.y = pathStrips[1]->headLocation.y;
				}
			}
		}
		else
		{
			if( getLength() > 0 )
			{
				pathStrips[0]->headLocation.x = x;
				pathStrips[0]->headLocation.y = y;
			}
		}*/

		//System::Diagnostics::Trace::WriteLine("PathStrips.........");
		//for( int i=0; i<getLength(); i++ )
		//{
		//	System::Diagnostics::Trace::WriteLine( i + ") x=" + pathStrips[i]->headLocation.x + ", y=" + pathStrips[i]->headLocation.y );
		//}
	}


	void SerpentPath::removeStrip()
	{
		pathStrips.removeLast();
	}


}