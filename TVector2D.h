#pragma once
#include <math.h>

template<typename T>
class TVector2D
{
public:
	T X;
	T Y;

	TVector2D(T inX, T inY)
	{
		X = inX;
		Y = inY;
	}

	/// <summary>
	/// Normalises a float type vector
	/// </summary>
	void Normalize()
	{
		if (typeid(T) == typeid(float))
		{
			// Get the dot product
			float DotProduct = sqrt((X*X) + (Y*Y));
			// Check if magnitude isn't 0 then normalise 
			if (DotProduct != 0) {
				X /= DotProduct;
				Y /= DotProduct;
			}
			else { // set to 0 if DotProduct is 0
				X = 0;
				Y = 0;
			}
		}
	}

	float Distance(TVector2D<T>& InVector)
	{

		return static_cast<float>(sqrt(((this->X - InVector.X) * (this->X - InVector.X)) + ((this->Y - InVector.Y) * (this->Y - InVector.Y))));
	}

	TVector2D<T> operator+(const TVector2D<T>& InVector)
	{
		return TVector2D(X + InVector.X, Y + InVector.Y);
	}

	TVector2D<T> operator-(const TVector2D<T>& InVector)
	{
		return TVector2D(X - InVector.X, Y - InVector.Y);
	}

	bool operator==(const TVector2D<T>& InVector)
	{
		return X == InVector.X && Y == InVector.Y;
	}

	void operator+=(const TVector2D<T>& InVector)
	{
		X += InVector.X;
		Y += InVector.Y;
	}

	void operator-=(const TVector2D<T>& InVector)
	{
		X -= InVector.X;
		Y -= InVector.Y;
	}
};