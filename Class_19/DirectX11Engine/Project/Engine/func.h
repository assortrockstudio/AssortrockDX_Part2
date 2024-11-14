#pragma once


void DrawDebugRect(Vec3 _WorldPos, Vec3 _WorldScale, Vec3 _WorldRotation, Vec4 _vColor, float _Duration);
void DrawDebugRect(Matrix _matWorld, Vec4 _vColor, float _Duration);

void DrawDebugCircle(Vec3 _WorldPos, float _Radius, Vec4 _vColor, float _Duration);

void DrawDebugLine();







template<typename T, int _Size>
void Safe_Del_Array(T* (&Array)[_Size])
{
	for (int i = 0; i < _Size; ++i)
	{
		if (nullptr != Array[i])
		{
			delete Array[i];
			Array[i] = nullptr;
		}
	}
}

template<typename T>
void Safe_Del_Vector(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}
