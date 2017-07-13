#pragma once

namespace GustyUtils
{
	class RandomInterface
	{
	public:
		virtual long random( long maxValue ) = 0;
	};
}