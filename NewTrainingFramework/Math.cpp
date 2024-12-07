#include "stdafx.h"
#include "../Utilities/Math.h"

// Constructor Vector3 din Vector4
Vector3::Vector3(Vector4& vector) : x(vector.x), y(vector.y), z(vector.z) {}

// Constructor Vector4 din Vector3
Vector4::Vector4(Vector3& vector) : x(vector.x), y(vector.y), z(vector.z), w(1.0f) {}

Vector4::Vector4(Vector3& vector, GLfloat _w) : x(vector.x), y(vector.y), z(vector.z), w(_w) {}
