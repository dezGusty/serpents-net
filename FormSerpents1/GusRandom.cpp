#include "StdAfx.h"
#include "GusRandom.h"
#include <stdlib.h>

namespace GustyUtils
{

	GusRandom::GusRandom( long seed )
	{
		initialize( seed );
	}


	GusRandom::~GusRandom()
	{
	}


	void GusRandom::initialize( long seed )
	{
		if( seed <= 0 )
			seed = -seed;
		srand( seed );
	}

	long GusRandom::random(long maxValue)
	{
		return rand() % maxValue;
	}
}