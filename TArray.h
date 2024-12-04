#pragma once

template<typename T>
class TArray
{
public:
	TArray()
	{
		Capacity = 5;
		Size = 0;

		Data = new T[Capacity];
	}


	~TArray()
	{
		for (int Index = 0; Index < Size; Index++) {

			
			delete Data[Index];
		}
	}

	void AddElement(T& NewElement)
	{
		if (Size >= Capacity) {
			Capacity *= 2;
			T* NewData = new T[Capacity];
			for (int Index = 0; Index < Size; Index++) {
				T* CopiedData;
				CopiedData = &Data[Index];
				NewData[Index] = *CopiedData;
			}

			delete[] Data;

			Data = NewData;
		}
		
		Data[Size] = NewElement;
		
		Size++;
	}

	T& GetElement(int Index)
	{
		return Data[Index];
	}

	void RemoveElement(int Index)
	{
		// Check index is valid
		if (!(Index < Size && Size > 0)) {
			return;
		}
		
		// Create new data array
		T* NewData;
		// Check if capacity needs to shrink
		if (Capacity > 5 && (Size * 2 == Capacity)) {
			NewData = new T * [Capacity/2];
			Capacity /= 2;
		}
		else {
			NewData = new T * [Capacity];
		}

		// Add the array objects from the old array to the new array while skipping the deleted
		for (int NewIndex = 0; NewIndex < Index; NewIndex++) {
			NewData[NewIndex] = Data[NewIndex];
		}
		for (int NewIndex = Index; NewIndex < Size - 1; NewIndex++) {
			NewData[NewIndex] = Data[NewIndex + 1];
		}

		// Delete the old data and copy over the new data
		delete[] Data;
		Data = NewData;
		delete[] NewData;
		Size--;
	}

	bool IsValidIndex(int Index)
	{
		return Index < Size&& Size > 0;
	}

	bool Contains(T& Element)
	{
		for (int Index = 0; Index < Size; Index++) {
			if (Data[Index] == &Element) {
				return true;
			}
		}

		return false;
	}

	int Num()
	{
		return Size;
	}

private:
	int Capacity;
	int Size;

	T* Data = nullptr;
};