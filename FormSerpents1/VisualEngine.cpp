#include "StdAfx.h"
//#include "SerpentsEngine.h"
#include "VisualEngine.h"

#include "PlayForm.h"

#include <stdio.h>

//using namespace Serpents;
//using namespace FormSerpents1;

namespace FormSerpents1
{
	VisualEngine::VisualEngine()
	{
		backBuffer = nullptr;
		this->engine = new Serpents::SerpentsEngine();
	}

	
	VisualEngine::~VisualEngine(void)
	{
		delete engine;
	}


	void VisualEngine::renderScene()
	{
		this->form->Invalidate();
	}


	void VisualEngine::startGame()
	{
		this->getEngine().startGame();

		Serpents::Serpent &serpent = this->getEngine().getSerpent();
		
		serpent.setSpawnPosition(210,310);
		//serpent.addParts(1);
		serpent.spawn();
		serpent.setSpeed(0.1);
		//serpent.setBodyPartSpawnSize(5, 5);
	}


	void VisualEngine::onKeyDown( int keyCode )
	{
		getEngine().onKeyDown( keyCode );
	}


	void VisualEngine::onKeyUp( int keyCode )
	{
		getEngine().onKeyUp( keyCode );
	}

	void VisualEngine::onPaintAlt(IDrawableArea* drawable)
	{
#if 0
		Graphics ^g = e->Graphics;
		Pen ^p = gcnew Pen(Color::Red);

		int width = form->ClientRectangle.Width;
		int height = form->ClientRectangle.Height;
		if (backBuffer == nullptr)
		{
			backBuffer = gcnew Bitmap(width, height);
		}
		//Bitmap ^ localBitmap = gcnew Bitmap(width, height);
		//Graphics ^ bitmapGraphics = Graphics::FromImage( localBitmap );
		Graphics ^ bitmapGraphics = Graphics::FromImage(backBuffer);
		bitmapGraphics->Clear(Color::Black);

		//	Begin drawing of scene
		Serpents::Serpent &serpent = engine->getSerpent();
		for (int i = 0; i<serpent.getLength(); i++)
		{
			BodyPart * bodyPart = serpent.getBodyPart(i);
			if (bodyPart != NULL)
			{
				bool vis = serpent.getBodyPart(i)->isSpawned();
				double x = (int)(serpent.getBodyPart(i)->getLocation().x - serpent.getBodyPart(i)->getSizeFromCenter());
				double y = (int)(serpent.getBodyPart(i)->getLocation().y - serpent.getBodyPart(i)->getSizeFromCenter());
				double w = (int)serpent.getBodyPart(i)->getSize().x;
				double h = (int)serpent.getBodyPart(i)->getSize().y;

				//System::Diagnostics::Trace::WriteLine("index=" + i + "; pos="
				//	+ x + ","
				//	+ y + ","
				//	+ w + ","
				//	+ h + ";"
				//	+ " visible=" + vis
				//	);
				if (vis)
				{
					bitmapGraphics->DrawEllipse(p, (float)x, (float)y, (float)w, (float)h);
					//bitmapGraphics->DrawRectangle(p, (float)x, (float)y, (float)w, (float)h);
				}
			}
		}

		for (int i = 0; i< serpent.path->getLength(); i++)
		{
			PathStrip *myStrip = serpent.path->getStrip(i);

			p->Color = Color::Gray;
			bitmapGraphics->DrawLine(p, (float)myStrip->getHeadLocation().x, (float)myStrip->getHeadLocation().y,
				(float)myStrip->getTailLocation().x, (float)myStrip->getTailLocation().y);

			p->Color = Color::GreenYellow;
			DPOINT myPoint = serpent.path->getCoords(i);
			float x = (float)myPoint.x;
			float y = (float)myPoint.y;

			bitmapGraphics->DrawLine(p, x - 1, y - 1, x + 1, y + 1);
			bitmapGraphics->DrawLine(p, x - 1, y + 1, x + 1, y - 1);
		}

		for (int i = 0; i<engine->getBonusController().getNumberOfItems(); i++)
		{
			Bonus * myBonus = engine->getBonusController().getItemAt(i);
			double x = (int)(myBonus->getLocation().x - myBonus->getSizeFromCenter());
			double y = (int)(myBonus->getLocation().y - myBonus->getSizeFromCenter());
			double w = (int)myBonus->getSize().x;
			double h = (int)myBonus->getSize().y;

			//System::Diagnostics::Trace::WriteLine("bonus, index=" + i + "; pos="
			//	+ x + ","
			//	+ y + ","
			//	+ w + ","
			//	+ h + ";"
			//	);
			p->Color = Color::YellowGreen;
			bitmapGraphics->DrawRectangle(p, (float)x, (float)y, (float)w, (float)h);
		}

		//	End drawing of scene

		Brush ^ myBrush = System::Drawing::Brushes::Beige;
		System::Drawing::Font ^myfont = gcnew Font(System::Drawing::FontFamily::GenericSansSerif, 10);
		drawable->drawText("up/down = increase/decrease speed; left/right = turn left/right", ColorRgb(0.5, 0.5, 0.5), 0, 0);
		bitmapGraphics->DrawString("up/down = increase/decrease speed; left/right = turn left/right", myfont, myBrush, 0, 0);

		bitmapGraphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

		//g->DrawImage( localBitmap, 0, 0 );
		e->Graphics->DrawImageUnscaled(backBuffer, 0, 0);
#endif
	}

	void VisualEngine::onPaint( Object ^sender, PaintEventArgs ^e )
	{
		Graphics ^g = e->Graphics;
		Pen ^p = gcnew Pen(Color::Red);

		int width = form->ClientRectangle.Width;
		int height= form->ClientRectangle.Height;
		if( backBuffer == nullptr )
		{
			backBuffer = gcnew Bitmap(width, height);
		}
		//Bitmap ^ localBitmap = gcnew Bitmap(width, height);
		//Graphics ^ bitmapGraphics = Graphics::FromImage( localBitmap );
		Graphics ^ bitmapGraphics = Graphics::FromImage( backBuffer );
		bitmapGraphics->Clear(Color::Black);

		//	Begin drawing of scene
		Serpents::Serpent &serpent = engine->getSerpent();
		for( int i=0; i<serpent.getLength(); i++ )
		{
			BodyPart * bodyPart = serpent.getBodyPart(i);
			if( bodyPart != NULL )
			{
				bool vis = serpent.getBodyPart(i)->isSpawned();
				double x = (int)(serpent.getBodyPart(i)->getLocation().x - serpent.getBodyPart(i)->getSizeFromCenter());
				double y = (int)(serpent.getBodyPart(i)->getLocation().y - serpent.getBodyPart(i)->getSizeFromCenter());
				double w = (int)serpent.getBodyPart(i)->getSize().x;
				double h = (int)serpent.getBodyPart(i)->getSize().y;

				//System::Diagnostics::Trace::WriteLine("index=" + i + "; pos="
				//	+ x + ","
				//	+ y + ","
				//	+ w + ","
				//	+ h + ";"
				//	+ " visible=" + vis
				//	);
				if( vis )
				{
					bitmapGraphics->DrawEllipse( p, (float)x, (float)y, (float)w, (float)h);
					//bitmapGraphics->DrawRectangle(p, (float)x, (float)y, (float)w, (float)h);
				}
			}
		}

		for( int i=0; i< serpent.path->getLength(); i++)
		{
			PathStrip *myStrip = serpent.path->getStrip(i);

			p->Color = Color::Gray;
			bitmapGraphics->DrawLine(p, (float)myStrip->getHeadLocation().x, (float)myStrip->getHeadLocation().y, 
				(float)myStrip->getTailLocation().x, (float)myStrip->getTailLocation().y);
			
			p->Color = Color::GreenYellow;
			DPOINT myPoint = serpent.path->getCoords(i);
			float x = (float)myPoint.x;
			float y = (float)myPoint.y;

			bitmapGraphics->DrawLine(p, x-1, y-1, x+1, y+1);
			bitmapGraphics->DrawLine(p, x-1, y+1, x+1, y-1);
		}

		for( int i=0; i<engine->getBonusController().getNumberOfItems(); i++ )
		{
			Bonus * myBonus = engine->getBonusController().getItemAt(i);
			double x = (int)(myBonus->getLocation().x - myBonus->getSizeFromCenter());
			double y = (int)(myBonus->getLocation().y - myBonus->getSizeFromCenter());
			double w = (int)myBonus->getSize().x;
			double h = (int)myBonus->getSize().y;

			//System::Diagnostics::Trace::WriteLine("bonus, index=" + i + "; pos="
			//	+ x + ","
			//	+ y + ","
			//	+ w + ","
			//	+ h + ";"
			//	);
			p->Color = Color::YellowGreen;
			bitmapGraphics->DrawRectangle(p, (float)x, (float)y, (float)w, (float)h);
		}

		//	End drawing of scene

		Brush ^ myBrush = System::Drawing::Brushes::Beige;
		System::Drawing::Font ^myfont = gcnew Font(System::Drawing::FontFamily::GenericSansSerif, 10);
		bitmapGraphics->DrawString("up/down = increase/decrease speed; left/right = turn left/right", myfont , myBrush, 0, 0);

		bitmapGraphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

		//g->DrawImage( localBitmap, 0, 0 );
		e->Graphics->DrawImageUnscaled( backBuffer, 0, 0 );
	}


	void VisualEngine::onTimeGoesBy( double timeUnits )
	{
		getEngine().onTimeGoesBy( timeUnits );
	}
}