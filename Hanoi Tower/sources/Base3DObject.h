#pragma once
#include "headers.h"
#include "Texture.h"

class _Position
{
public :

		float X;
		float Y;
		float Z;
		float Offset;
		float Angle;

		void MoveTo(float X,float Y,float Z);
		void RotateAround(float Angle,char Direction);
		void Set(float X,float Y,float Z);
};

class _Size
{
public :
		float Width;
		float Height;
		float Depth;

		void ScaleBy(float size)
		{
			Width+=size;
			Height+=size;
			Depth+=size;
			glScalef(Width,Height,Depth);
		}
};
class _Color
{
public :
	 
		 GLubyte Red;
		 GLubyte Green;
		 GLubyte Blue;
		 GLubyte Alpha;

		 _Color();
		 ~_Color();
		 _Color(const _Color& color);
		 _Color& operator=(const _Color & color);

		void set(GLubyte Red,GLubyte Green,GLubyte Blue);
		void set(GLubyte Red,GLubyte Green,GLubyte Blue,GLubyte Alpha);
		void Render();
};
class Base3DObject 
{

	
	public:
		~Base3DObject(void);
		Base3DObject(void);


		auto_ptr<_Position>  Position;
		auto_ptr<_Size> Size;
		_Color *  Color;
		_Texture Texture;

	
};

