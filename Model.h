#pragma once

#include "Vec3.h"
#include <vector>
#include "VertexIndexBuf.h"
#include "Vertex.h"
#include "OBJLoader.h"

class Model
{
private:
	std::vector<Vec3f> vertices;
	std::vector<Vec3f> normals;
	//std::vector<size_t> indices;
public:
	Model()
	{
		std::vector<Vertex> model;
		model = loadOBJ("OBJFiles/untitled.obj");
		for (size_t i = 0;
			i < model.size(); i++)
		{
			vertices.emplace_back(model[i].pos);
			normals.emplace_back(model[i].normal);
		}
	}
	VertexIndexBuf GetTriangle() const
	{
		/*return{				//for wire framed
			vertices,{
				0,1,  1,3,  3,2,  2,0,
				0,4,  1,5,  3,7,  2,6,
				4,5,  5,7,  7,6,  6,4 }
		};*/
		return{ vertices, normals };
	}
};
