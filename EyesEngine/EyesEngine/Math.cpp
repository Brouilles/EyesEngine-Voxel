#ifndef MATH_CPP_INCLUDED
#define MATH_CPP_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <string>
#include <iostream>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>
/////////////////////////////////////////////////////////////

#define Z_VECTOR = 1.0f;

/////////////////////////////////////////////////////////////
/// <summary> 
///		2D Vector. Composed of 2 float (x, y)
/// </summary>
/////////////////////////////////////////////////////////////
struct Vector2D
{
	float x, y;
};

/////////////////////////////////////////////////////////////
/// <summary> 
///		2D Vector more Height, Width. Composed of 4 float (x, y, h, w)
/// </summary>
/////////////////////////////////////////////////////////////
struct Vector2DHW
{
	float x, y, h, w;
};

/////////////////////////////////////////////////////////////
/// <summary> 
///		Model vector for 3D model. Scale, rotation and position value.
/// </summary>
/////////////////////////////////////////////////////////////
struct ModelVector3D {
	D3DXVECTOR3 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 position;
};

/////////////////////////////////////////////////////////////
/// <summary> 
///		Split string, array
/// </summary>
/////////////////////////////////////////////////////////////
inline std::vector<std::string> split(std::string basicLine, std::string separator)
{
	std::vector<std::string> resultArray;
	std::string value;

	for (int loop = 0; loop < basicLine.length(); loop++)
	{
		char character = basicLine.at(loop);
		if (character != *separator.c_str())
			value += basicLine[loop];
		else
		{
			resultArray.push_back(value);
			value.clear();
		}
	}
	resultArray.push_back(value);

	return resultArray;
}
#endif