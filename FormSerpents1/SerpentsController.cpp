#include "StdAfx.h"
#include "SerpentsController.h"

namespace Serpents
{
	SerpentsController::SerpentsController( KeyDefiner &kd )
		: KeyController(kd)
	{
		this->menu.keyBinding = keyDefiner->getIndexOf("Escape");
		this->menu.pressed = false;
		this->pause.keyBinding = keyDefiner->getIndexOf("Break");
		this->pause.pressed = false;
		this->accelerate.keyBinding = keyDefiner->getIndexOf("Up");
		this->accelerate.alternateKeyBinding = keyDefiner->getIndexOf("W");
		this->accelerate.pressed = false;
		this->decelerate.keyBinding = keyDefiner->getIndexOf("Down");
		this->decelerate.alternateKeyBinding = keyDefiner->getIndexOf("S");
		this->decelerate.pressed = false;
		this->left.keyBinding = keyDefiner->getIndexOf("Left");
		this->left.alternateKeyBinding = keyDefiner->getIndexOf("A");
		this->left.pressed = false;
		this->right.keyBinding = keyDefiner->getIndexOf("Right");
		this->right.alternateKeyBinding = keyDefiner->getIndexOf("D");
		this->right.pressed = false;
	}
}