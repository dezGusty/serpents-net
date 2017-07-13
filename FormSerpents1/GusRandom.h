#pragma once

#include "RandomInterface.h"

namespace GustyUtils
{
	class GusRandom : public RandomInterface
	{
	public:
		GusRandom( long seed = -1 );
		~GusRandom();

		void initialize( long seed = -1 );
		long random( long maxValue );
	};
}