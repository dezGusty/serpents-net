#pragma once

class SerpentsEngine;
#include "SerpentsEngine.h"
using namespace Serpents;

//ref class PlayForm;
#include "PlayForm.h"
#include "idrawablearea.h"

namespace FormSerpents1
{
	//
	//	Clasa de legatura intre background-logic si prezentare.
	//

	ref class VisualEngine 
	{
	public:

		//
		//	Constructorul. (default)
		//

		VisualEngine();

		//
		//	Destructor.
		//

		virtual ~VisualEngine(void);

		//
		//	Functia de (re)desenare a scenei.
		//

		virtual void renderScene();

		//
		//	Initializeaza jocul.
		//

		virtual void startGame();

		//
		//	Reactioneaza la apasarea unei taste. (Mapping catre SerpentsEngine)
		//

		virtual void onKeyDown( int keyCode );
		virtual void onKeyUp( int keyCode );

		//
		//	Gettet pentru engine-ul din partea logica.
		//

		virtual Serpents::SerpentsEngine &getEngine(){ return *engine; }

		//
		//	Reactioneaza la trecerea timpului. (Mapping catre SerpentsEngine)
		//

		virtual void onTimeGoesBy( double timeUnits );

		//
		//	Getter pentru form-ul legat de engine.
		//

		virtual void setFormToUse( FormSerpents1::PlayForm ^formToUse ){ this->form = formToUse; }

		//
		//	Desenarea apelata din exterior.
		//

		virtual void onPaint( Object ^sender, PaintEventArgs ^e );
		virtual void onPaintAlt(IDrawableArea* drawable);

	protected: 
		Serpents::SerpentsEngine * engine;
		System::Collections::ArrayList widgetsList;
		PlayForm ^form;

		System::Windows::Forms::Label ^ debugLabel;
	private:
		Bitmap ^backBuffer;
	};
}