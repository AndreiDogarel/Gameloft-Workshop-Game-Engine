#pragma once
#include "Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv;

	Vertex() : pos(), norm(), binorm(), tgt(), uv() {}

	Vertex(const Vertex& other)
		: pos(other.pos), norm(other.norm), binorm(other.binorm), tgt(other.tgt), uv(other.uv) {}

};