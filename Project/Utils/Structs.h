#pragma once
namespace Resources::Entitys {
	class GameObject;
}
namespace Utils {
	struct vertexData_t {
		glm::vec3 position;
		Color color;
	};

	struct TextureCoord {
		float u, v;
	};

	struct Normal {
		float x, y, z;
	};

	struct Face {
		// Ogni faccia � una lista di indici (vertice, texture, normale)
		std::vector<int> vertexIndices;
		std::vector<int> textureIndices;
		std::vector<int> normalIndices;
		/// <summary>
		/// Serve a mantenere l'informazione del materiale in uso
		/// </summary>
		std::string materialName;
		/// <summary>
		/// Si riferisce alla class Resources::Entitys::Game object, serve a mappare i vertici ecc
		/// </summary>
		Resources::Entitys::GameObject * refGameObject = nullptr;
	};

}