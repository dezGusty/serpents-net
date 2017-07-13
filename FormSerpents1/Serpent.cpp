#include "StdAfx.h"
#include "Serpent.h"

#include <stdio.h>
#include <math.h>

namespace Serpents
{
	//
	//	constructor
	//
	Serpent::Serpent( int initialLength )
	{
		path = new SerpentPath();
		maxlength = 100;
		minlength = 0;
		spawnBodyPartSize.x = 15;
		spawnBodyPartSize.y = 15;
		this->addParts(initialLength);
		if( bodyParts.getLength()> 0 )
		{
			DPOINT hsz = {20,20};
			this->bodyParts[0]->setSize( hsz );
		}

		minSpeed = DEFAULT_MIN_SPEED;
		maxSpeed = DEFAULT_MAX_SPEED;
		setSpeed(1);
		setSpeedInfluenceOnTurn(0);
		setSpeedStep(0.001);
	}

	//
	//	std destructor.
	//
	Serpent::~Serpent(void)
	{
		bodyParts.removeAll();
	}


	//
	//	add a number of parts
	//
	void Serpent::addParts(int numParts )
	{
		int partsToAdd = numParts;
		if( partsToAdd <= 0 )
		{
			return;
		}

		//	se adauga parti pana la limita maxima

		if( getLength() + numParts > maxlength )
		{
			partsToAdd = maxlength - getLength();
		}

		for( int i=0; i<partsToAdd; i++ )
		{
			BodyPart * myBodyPart = new BodyPart();
			myBodyPart->setSize( spawnBodyPartSize );
			System::Diagnostics::Trace::WriteLine("Adding bodypart; size=" + spawnBodyPartSize.x + "," + spawnBodyPartSize.y );

			bodyParts.add( myBodyPart );

			this->onAddedBodyPart();
		}
	}


	void Serpent::onAddedBodyPart()
	{
		path->addStrip();
	}


	void Serpent::onRemovedBodyPart()
	{
		path->removeStrip();
	}


	void Serpent::removeParts( int numParts )
	{
		int partsToRemove = numParts;
		if( partsToRemove <= 0 )
		{
			return;
		}

		if( this->getLength() - partsToRemove <= this->minlength )
		{
			partsToRemove = this->getLength() - this->minlength;
		}

		for( int i=0; i< partsToRemove; i++ )
		{
			bodyParts.removeLast();
			this->onRemovedBodyPart();
		}

	}


	void Serpent::setBodyPartSpawnSize( double width, double height )
	{
		this->spawnBodyPartSize.x = width;
		this->spawnBodyPartSize.y = height;
	}


	void Serpent::setSpawnPosition(double x, double y)
	{
		this->spawnPosition.x = x;
		this->spawnPosition.y = y;
	}


	void Serpent::spawn(double x, double y)
	{
		for( int i = 0; i< this->getLength(); i++ )
		{
			this->bodyParts[i]->setLocation(x,y);
			if( i==0)
			{
				bodyParts[i]->spawned = true;
			}
			else
			{
				bodyParts[i]->spawned = false;
			}
		}
	}


	void Serpent::spawn()
	{
		this->spawn( spawnPosition.x, spawnPosition.y );
	}


	
	//
	//	set tje angle of the head
	//
	void Serpent::setAngleInRadians(double angle, bool affectAll )
	{
		int maxIter = (affectAll ? 1 : this->getLength() );

		for( int i=0; i< maxIter && i< this->getLength(); i++  )
		{
			this->bodyParts[i]->angleInRads = angle;
		}
	}




	//
	//	 set the general speed of the serpent
	//
	void Serpent::setSpeed( double  newSpeed )
	{
		this->speed = newSpeed;
		if( newSpeed < minSpeed )
		{
			this->speed = minSpeed;
		}
		if( newSpeed > maxSpeed )
		{
			this->speed = maxSpeed;
		}
	}


	void Serpent::setTurnSpeed(double newTurnSpeed)
	{
		if( newTurnSpeed > MIN_TURN_SPEED && newTurnSpeed < MAX_TURN_SPEED )
		{
			this->turnSpeed = newTurnSpeed;
		}
	}


	//
	// move the serpent for a certain duration
	//
	void Serpent::move( double timeUnits )
	{
		System::Threading::Mutex myMutex;
		myMutex.WaitOne();
		if( timeUnits <=0 )
		{
			timeUnits = 0.1;	//	TODO: ar trebui o constanta in loc de 0.1
		}

		if( getLength() <= minlength )
		{
			return;
		}

		// spawn parti secundare, cand pot sa apara

		int lastNonSpawn = getLength();
		for(int i=getLength()-1;i>=0;i-- )
		{
			if( ! bodyParts[i]->spawned )
			{
				lastNonSpawn = i;
			}
		}

		//System::Diagnostics::Trace::WriteLine( "lastNonSpawn = " + lastNonSpawn );
		

		
		if( lastNonSpawn > 0 )
		{
			for( int i= lastNonSpawn; i < getLength(); i++ )
			{
				if( bodyParts[i]->collidesWith( *bodyParts[i-1] ))
				{
					//System::Diagnostics::Trace::WriteLine( "bodypart[" + i + "] collides with bodypart[" + (i-1) + "]" );
					break;
				}
				else
				{
					bodyParts[i]->spawned = bodyParts[i-1]->spawned;
				}
			}
		}


		SPoint<double> newLocation = bodyParts[0]->getLocation();
		double tempSpeed = this->speed;
		newLocation.x += System::Math::Cos( bodyParts[0]->getAngleInRadians() ) * tempSpeed * timeUnits;
		newLocation.y -= System::Math::Sin( bodyParts[0]->getAngleInRadians() ) * tempSpeed * timeUnits;

		double xsz = bodyParts[0]->getSizeFromCenter() + (bodyParts[1] ? bodyParts[1]->getSizeFromCenter() : 0);

		path->moveHeadStrip( newLocation.x, newLocation.y,  xsz);
		path->getAndSetPositionOfAllParts( bodyParts );

		myMutex.ReleaseMutex();
	}


	//
	//	get the bodypart at a certain index
	//
	BodyPart* Serpent::getBodyPart(int index)
	{
		return bodyParts[index];
	}


	//
	//	turn the snake left or right
	//
	void Serpent::turn( double angle, bool useRadians )
	{
		double angleRad = angle;
		if( ! useRadians )
		{
			angleRad = angle * System::Math::PI / 180 ;
		}

		BodyPart * temp = getBodyPart(0);
		if( temp )
		{
			temp->angleInRads += angleRad * turnSpeed * (1 + speedInfluenceOnTurn * sqrt(speed));
		}
	}
}