#pragma once
namespace Utils {
	struct vec3_t {
		float x, y, z;
	};
	struct vertexData_t {
		vec3_t position;
		Color color;
	};

	struct TextureCoord {
		float u, v;
	};

	struct Normal {
		float x, y, z;
	};

	struct Face {
		// Ogni faccia è una lista di indici (vertice, texture, normale)
		std::vector<int> vertexIndices;
		std::vector<int> textureIndices;
		std::vector<int> normalIndices;
	};
}