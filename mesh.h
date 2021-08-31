#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
//#include<algorithm>

//OpenGL Math libs
#include "Vec3.h"
#include "Vec2.h"
#include "triangles.h"

struct mesh
{
	std::vector<triangle> tris;

	bool LoadFromObjectFile(const char* file_name)
	{
		std::vector<Vec3f> vertex_pos;
		std::vector<Vec2f> vertex_tex;
		std::vector<Vec3f> vertex_norms;

		//Face vectors
		std::vector<size_t> pos_indices;
		std::vector<size_t> tex_indices;
		std::vector<size_t> norm_indices;

		std::stringstream ss;
		std::ifstream in_file(file_name);
		std::string line = "";
		std::string prefix = "";
		Vec3f temp_vec3;
		Vec2f temp_vec2;
		size_t temp_index = 0;

		//File open error check
		if (!in_file.is_open())
		{
			exit(0);
			throw "ERROR::OBJLOADER::Could not open file.";
		}

		//Read one line at a time
		while (std::getline(in_file, line))
		{
			//Get the prefix of the line
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "#" || prefix == "o" || prefix == "use_mtl" || prefix == "s")
			{

			}
			else if (prefix == "v") //Vertex position
			{
				ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
				vertex_pos.push_back(temp_vec3);
			}
			else if (prefix == "vt")
			{
				ss >> temp_vec2.x >> temp_vec2.y;
				vertex_tex.push_back(temp_vec2);

			}
			else if (prefix == "vn")
			{
				ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
				vertex_norms.push_back(temp_vec3);
			}
			else if (prefix == "f")
			{
				int counter = 0;
				while (ss >> temp_index)
				{
					//Pushing indices into correct arrays
					if (counter == 0)
						pos_indices.push_back(temp_index);
					else if (counter == 1)
						tex_indices.push_back(temp_index);
					else if (counter == 2)
						norm_indices.push_back(temp_index);

					//Handling characters
					if (ss.peek() == '/')
					{
						++counter;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' ')
					{
						++counter;
						ss.ignore(1, ' ');
					}

					//Reset the counter
					if (counter > 2)
						counter = 0;
				}
			}
			else
			{

			}
		}
		for (size_t i = 0; i < pos_indices.size(); i = i + 3)
		{
			Vec3f v1 = vertex_pos[pos_indices[i] - 1];
			Vec3f v2 = vertex_pos[pos_indices[i + 1] - 1];
			Vec3f v3 = vertex_pos[pos_indices[i + 2] - 1];
			Vec2f t1 = vertex_tex[tex_indices[i] - 1];
			Vec2f t2 = vertex_tex[tex_indices[i + 1] - 1];
			Vec2f t3 = vertex_tex[tex_indices[i + 2] - 1];
			Vec3f n1 = vertex_norms[norm_indices[i] - 1];
			Vec3f n2 = vertex_norms[norm_indices[i + 1] - 1];
			Vec3f n3 = vertex_norms[norm_indices[i + 2] - 1];
			tris.push_back({ v1, v2, v3,
							 t1, t2, t3,
							 n1, n2, n3 });
		}
		std::cout << tris.size() <<  std::endl;
		return true;	
	}
};

