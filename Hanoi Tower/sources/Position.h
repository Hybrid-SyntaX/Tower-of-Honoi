#pragma once
#include "headers.h"
class _Position
{
public :
		_Position(void);
		~_Position(void);

		float X;
		float Y;
		float Z;
		float Offset;
		float Angle;

		void MoveTo(float X,float Y,float Z);
		void RotateAround(float Angle,char Direction);
		void Set(float X,float Y,float Z);
};

