#pragma once

#include <stdio.h>

namespace GustyUtils
{
#ifndef DFLOAT
#define DFLOAT double
#endif
	//
	//	Structura de reprezentare a unui punct in cadrul unui bodypart.
	//

	template <class T> struct SPoint
	{
		T x;
		T y;
	};

#ifndef SerPoint
#define SerPoint SPoint<DFLOAT>
#endif

#ifndef DPOINT
#define DPOINT SPoint<DFLOAT>
#endif

#ifndef IPOINT
#define IPOINT SPoint<int>
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(pointer) if(pointer!=NULL){delete pointer;}
#endif


	//
	//	Structura de reprezentare a unui dreptunghi.
	//

	template <class T> struct SRectangle
	{
		T left;
		T right;
		T top;
		T bottom;
	};

#ifndef DRECT
#define DRECT SRectangle<DFLOAT>
#endif

	template <class T> static bool RectanglesCollide( T left1, T right1, T top1, T bottom1, 
											T left2, T right2, T top2, T bottom2 );

	DFLOAT GetSegmentLength( DFLOAT x1, DFLOAT y1, DFLOAT x2, DFLOAT y2 );

	/*bool RectanglesCollideD( DFLOAT left1, DFLOAT right1, DFLOAT top1, DFLOAT bottom1, 
											DFLOAT left2, DFLOAT right2, DFLOAT top2, DFLOAT bottom2 );
*/

	//
	//	Clasa proprie de lucru cu colectii, non-managed code
	//

	template <class T> class GusArray
	{
	public:

		//
		//	Constructor.
		//

		GusArray();

		//
		//	Destructor. Elimina tot sirul.
		//

		~GusArray();

		//
		//	Getter for the length.
		//

		virtual int getLength(){ return length; }

		//
		//	Getter de element al sirului.
		//

		virtual T* operator[]( int index ){ return getElementAt(index); }
		virtual T* getElementAt( int index );

		//
		//	Adaugare element.
		//

		virtual void add( T * elem );

		//
		//	Eliminare element.
		//

		virtual void removeLast();

		virtual void removeAt( int index );

		virtual void removeAll();

	private:

		//
		//	Modifica dimensiunea alocata a sirului. (Creste)
		//

		void increaseSize();

		//
		//	Modifica dimensiunea alocata a sirului. (Scade)
		//

		void decreaseSize();


		int length;
		int allocSize;
		T** elements;
	};


	public class GusUtils
	{
	protected:
		GusUtils(void);
	public:
		~GusUtils(void);

	public:
		template <class T> static bool RectanglesCollide( T left1, T right1, T top1, T bottom1, 
											T left2, T right2, T top2, T bottom2 );
	};



	//
	//	=========================================== GusArray ========================================
	//

	template<class T> GusArray<T>::GusArray()
	{
		this->length = 0;
		this->allocSize = 0;
		elements = new T*[0];
	}


	template<class T> GusArray<T>::~GusArray()
	{
		removeAll();
		delete elements;
	}


	template<class T> void GusArray<T>::increaseSize()
	{
		int newSize = allocSize * 2;
		if( newSize == 0 ) newSize ++;
		if( newSize <= allocSize )
		{
			return;
		}

		T ** extra = new T*[newSize];
		for( int j=0; j< length && j<allocSize; j++)
		{
			extra[j] = elements[j];
		}
		if( length > 0 )
		{
			delete elements;
		}
		elements = extra;
		allocSize = newSize;
	}


	template<class T> void GusArray<T>::decreaseSize()
	{
		if( allocSize > 1 && length >= 0 )
		{
			if( allocSize / 2 > length )
			{
				int newSize = allocSize / 2;

				T ** extra = new T*[newSize];
				for( int j=0; j< length && j<newSize; j++)
				{
					extra[j] = elements[j];
				}
				if( length > 0 )
				{
					delete elements;
				}
				elements = extra;
				allocSize = newSize;
			}
		}
	}


	template<class T> T* GusArray<T>::getElementAt( int index )
	{
		if( index >= length )
		{
			System::Diagnostics::Trace::WriteLine("Exception: getElementAt; requested index="+ index +"; length=" + length);
			index = length-1;
		}
		if( index < 0 || allocSize == 0 )
		{
			System::Diagnostics::Trace::WriteLine("Exception: getElementAt; requested index="+ index +"; allocSize=" + allocSize);
			return NULL;
		}
		return elements[index];
	}


	template<class T> void GusArray<T>::add( T * elem )
	{
		if( length >= allocSize )
		{
			increaseSize();
		}
		elements[length] = elem;
		length ++;
	}


	template<class T> void  GusArray<T>::removeLast()
	{
		if( length > 0 )
		{
			delete elements[length-1];
			length--;
		}
	}


	template<class T> void  GusArray<T>::removeAt( int index )
	{
		if( index < length && index >= 0 )
		{
			delete elements[index];

			for( int i= index; i<length-1; i++ )
			{
				elements[i] = elements[i+1];
			}
			length--;
		}
	}


	template<class T> void  GusArray<T>::removeAll()
	{
		for( int i=0; i<length; i++ )
		{
			delete elements[i];
		}
		length = 0;
		allocSize = 0;
	}
}