#include "../../STDInclude.hpp"

Resources::Entitys::GameObject::GameObject()
{
	m_modelMatrix = glm::mat4(1.0f);
}

Resources::Entitys::GameObject::GameObject(const std::string& _name)
{
	m_Name = _name;
	m_modelMatrix = glm::mat4(1.0f);
}

Resources::Entitys::GameObject::~GameObject()
{
	if (m_vertexBufferObject != 0) {
		glDeleteBuffers(1, &m_vertexBufferObject);
		m_vertexBufferObject = 0;
	}

	if (m_vertexArrayObject != 0) {
		glDeleteVertexArrays(1, &m_vertexArrayObject);
		m_vertexArrayObject = 0;
	}

	m_vertexData.clear();
}


void Resources::Entitys::GameObject::AddData(Utils::vertexData_t _data)
{
	m_vertexData.push_back(_data);
}

void Resources::Entitys::GameObject::CopyData(std::vector<Utils::vertexData_t> _data)
{
	if (!_data.empty())
	{
		m_vertexData.clear();
		m_vertexData = _data;
	}
}

void Resources::Entitys::GameObject::CopyData(Utils::vertexData_t* _data, size_t _size)
{
	if (_data != nullptr && _size > 0) // Controllo validità del puntatore e dimensione
	{
		m_vertexData.clear(); // Svuoto il vettore precedente

		for (size_t i = 0; i < _size; ++i) // Itero sul numero di elementi
		{
			m_vertexData.push_back(_data[i]); // Copio ogni elemento
		}
	}
}

int Resources::Entitys::GameObject::GetVertexSize()
{
	return m_vertexData.size();
}

GLuint Resources::Entitys::GameObject::GetVertexArray()
{
	return m_vertexArrayObject;
}

GLuint Resources::Entitys::GameObject::GetVertexBuffer()
{
	return m_vertexBufferObject;
}

bool Resources::Entitys::GameObject::BuildVertex()
{

	if (m_vertexData.empty())
		return false;

	glGenBuffers(1, &m_vertexBufferObject);

	if (m_vertexBufferObject == 0)
		return false;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(Utils::vertexData_t), m_vertexData.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vertexArrayObject);
	if (m_vertexArrayObject == 0)
	{
		glDeleteBuffers(1, &m_vertexBufferObject);
		return false;
	}

	glBindVertexArray(m_vertexArrayObject);

	//0 layout shader, 3 grandezza array float, 0 init position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Utils::vertexData_t), (void*)0); //Posizione
	glEnableVertexAttribArray(0);

	//1 layout shader, 4 grandezza array float, (void*)(3 * sizeof(float)) posizione buffer
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Utils::vertexData_t), (void*)(3 * sizeof(float))); //COLORE
	glEnableVertexAttribArray(1);

	//UNBINDING VBO E VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return true;
}

const std::string& Resources::Entitys::GameObject::GetName()
{
	return m_Name;
}

const glm::mat4& Resources::Entitys::GameObject::GetModelMatrix()
{
	return m_modelMatrix;
}

