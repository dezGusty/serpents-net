#pragma once

#include "KeyController.h"
namespace Serpents
{
	class SerpentsController :
		public KeyController
	{
	public:
		SerpentsController( KeyDefiner &kd );

	//protected:
		KeyBinding menu;
		KeyBinding left;
		KeyBinding right;
		KeyBinding accelerate;
		KeyBinding decelerate;
		KeyBinding pause;
	};
}