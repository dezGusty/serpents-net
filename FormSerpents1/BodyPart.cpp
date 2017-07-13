#include "StdAfx.h"
#include "BodyPart.h"
#include "GusUtils.h"
using namespace GustyUtils;

namespace Serpents
{

	BodyPart::BodyPart(void)
	{
		this->setPivot(CenterPivot);
		this->speed = SPEED_INHERITED;
		this->angleInRads = 0.0 ;
		DRECT myRect={0,0,0,0};
		this->setBounds(myRect);
		DPOINT mySize = {1,1};
		this->setSize(mySize);
		this->spawned = false;
		this->setShape(MapObject::ObjectShapeCircular);
	}


	BodyPart::BodyPart(BodyPart & copy)
	{
		this->speed = copy.speed;
		this->spawned = copy.spawned;
	}


	BodyPart::~BodyPart()
	{
	}


	bool BodyPart::collidesWith( BodyPart & rhs )
	{
		//	Coliziune circulara.

		double len1 = GustyUtils::GetSegmentLength( getLocation().x, getLocation().y, rhs.getLocation().x, rhs.getLocation().y );
		double len2 = this->getSizeFromCenter() + rhs.getSizeFromCenter();
		System::Diagnostics::Trace::WriteLine( "BP:collideswith(), len1 (dist)=" + len1.ToString("F") + " ... len2 (sumrad)=" + len2.ToString("F") );

		if( len1 < len2 )
		{
			return true;
		}
		return false;
	}

	//
	double BodyPart::getAngleInDegrees()
	{
		return this->getAngleInRadians() * 180/ System::Math::PI ;	
	}

	//
	double BodyPart::getAngleInRadians()
	{
		return this->angleInRads;
	}


	//
	double BodyPart::getSpeed()
	{
		return this->speed;
	}

	//
	bool BodyPart::isSpawned()
	{
		return this->spawned;
	}


}