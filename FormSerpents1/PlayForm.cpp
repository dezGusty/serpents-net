#include "StdAfx.h"
#include "PlayForm.h"

#include "VisualEngine.h"
#include "Tester.h"

using namespace System::Diagnostics;

namespace FormSerpents1
{

	void PlayForm::startTracing( String ^ filename )
	{
		TextWriterTraceListener ^ mytwtl = gcnew TextWriterTraceListener(System::IO::File::CreateText( filename ));
		Debug::Listeners->Add(mytwtl);
		Trace::WriteLine("Trace Started, on" + System::DateTime::Now.ToLocalTime().ToString());
		Trace::Indent();
		System::Diagnostics::Trace::WriteLine("--------------------");
		Trace::Flush();
	}


	void PlayForm::startJoc()
	{
		jocCreat = true;
		this->engineJoc = gcnew VisualEngine();
		engineJoc->setFormToUse(this);
		engineJoc->startGame();
		this->gameActionTimer->Enabled = true;
	}


	void PlayForm::startTest()
	{
		testerCreat = true;
		testerJoc = gcnew Tester();
		testerJoc->setFormToUse(this);
	}


	void PlayForm::postInit()
	{
		this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &PlayForm::PlayFormKeyDown);
		this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &PlayForm::PlayFormKeyUp);
			this->SetStyle(ControlStyles::ResizeRedraw, true);
		this->SetStyle(ControlStyles::ResizeRedraw | ControlStyles::Opaque, true);
		//overlordPanel->ClientSize = System::Drawing::Size(800, 600);
		startTracing("ztrace.txt");

		SetStyle( ControlStyles::AllPaintingInWmPaint | ControlStyles::DoubleBuffer | ControlStyles::ResizeRedraw | ControlStyles::UserPaint, true );
		this->Focus();

	}


	void PlayForm::actiuneActionTimer()
	{
		if( jocCreat )
		{
			engineJoc->onTimeGoesBy( gameActionTimer->Interval);
			engineJoc->renderScene();
		}
	}




	void PlayForm::OnPaint( PaintEventArgs^ e )
	{
		if( jocCreat )
		{
			engineJoc->onPaint( this, e );
		}
		else
		{
			//in meniu
			Graphics ^g = e->Graphics;
			Pen ^p = gcnew Pen(Color::Red);

			int width = this->ClientRectangle.Width;
			int height= this->ClientRectangle.Height;
			Bitmap ^ localBitmap = gcnew Bitmap(width, height);
			Graphics ^ bitmapGraphics = Graphics::FromImage( localBitmap );
			bitmapGraphics->Clear(Color::Navy);
			Brush ^ myBrush = System::Drawing::Brushes::Beige;
			System::Drawing::Font ^myfont = gcnew System::Drawing::Font(System::Drawing::FontFamily::GenericSansSerif, 10);
			bitmapGraphics->DrawString("press <ENTER> to start gaming test", myfont , myBrush, 220, 350);

			bitmapGraphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			g->DrawImage( localBitmap, 0, 0 );
		}
	}
	
	void PlayForm::OnPaintBackground( PaintEventArgs^ e )
	{
	}


	void PlayForm::actiuneKeyboardTimer()
	{
	}


	System::Void PlayForm::PlayFormKeyDown( System::Object ^ , System::Windows::Forms::KeyEventArgs ^ e)
	{
		if( e->KeyValue == 13 )
		{
			if(!jocCreat && ! testerCreat)
				startJoc(); 
		}
		else
		{
			if( e->KeyValue == 27 || e->KeyValue == 7 )
			{
				if( !jocCreat && ! testerCreat )
					startTest();
			}
			else
			{
				if( jocCreat )
				{
					engineJoc->onKeyDown( e->KeyValue );
				}
				if( testerCreat )
				{
					testerJoc->onKeyDown( e->KeyValue );
				}
			}
		}
	}


	System::Void PlayForm::PlayFormKeyUp( System::Object ^ , System::Windows::Forms::KeyEventArgs ^ e)
	{
		if( jocCreat )
		{
			engineJoc->onKeyUp( e->KeyValue );
		}
	}

}