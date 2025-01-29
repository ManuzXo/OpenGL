#include "../../../STDInclude.hpp"

Resources::Entitys::GL::VertexBuffer::VertexBuffer()
{
}

Resources::Entitys::GL::VertexBuffer::~VertexBuffer()
{
	if (m_vertexBufferObject != 0) {
		glDeleteBuffers(1, &m_vertexBufferObject);
		m_vertexBufferObject = 0;
	}

	if (m_vertexArrayObject != 0) {
		glDeleteVertexArrays(1, &m_vertexArrayObject);
		m_vertexArrayObject = 0;
	}
	if (m_indexBuffer != 0) {
		glDeleteBuffers(1, &m_indexBuffer);
		m_indexBuffer = 0;
	}

	m_vertexData.clear();
	m_indices.clear();
}

void Resources::Entitys::GL::VertexBuffer::AddData(data_t _data)
{
	m_vertexData.push_back(_data);
}

void Resources::Entitys::GL::VertexBuffer::AddIndex(unsigned int _index)
{
	m_indices.push_back(_index);
}

void Resources::Entitys::GL::VertexBuffer::CopyData(std::vector<data_t> _data)
{
	if (!_data.empty())
	{
		m_vertexData.clear();
		m_vertexData = _data;
	}
}

void Resources::Entitys::GL::VertexBuffer::CopyData(data_t* _data, size_t _size)
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

int Resources::Entitys::GL::VertexBuffer::GetVertexSize()
{
	return m_vertexData.size();
}

int Resources::Entitys::GL::VertexBuffer::GetIndicesSize()
{
	return m_indices.size();;
}

unsigned int* Resources::Entitys::GL::VertexBuffer::GetIndeces()
{
	return m_indices.data();
}

GLuint Resources::Entitys::GL::VertexBuffer::GetIndexBuffer()
{
	return m_indexBuffer;
}

GLuint Resources::Entitys::GL::VertexBuffer::GetVertexArray()
{
	return m_vertexArrayObject;
}

GLuint Resources::Entitys::GL::VertexBuffer::GetVertexBuffer()
{
	return m_vertexBufferObject;
}

bool Resources::Entitys::GL::VertexBuffer::BuildVertex()
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

	if (GetIndicesSize() > 0)
	{
		glGenBuffers(1, &m_indexBuffer);
		if (m_indexBuffer == 0)
		{
			glDeleteBuffers(1, &m_vertexBufferObject);
			glDeleteVertexArrays(1, &m_vertexArrayObject);
			return false;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
	}


	//UNBINDING VBO E VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return true;
}

size_t Resources::Entitys::GL::VertexBuffer::HashFunction_t::operator()(const std::pair<glm::vec3, Utils::Color>& pair) const
{
	std::hash<float> _hashFn;
	size_t _h1 = _hashFn(pair.first.x) ^ _hashFn(pair.first.y) << 1 ^ _hashFn(pair.first.z) << 2;
	size_t _h2 = _hashFn(pair.second.r) ^ _hashFn(pair.second.g) << 1 ^ _hashFn(pair.second.b) << 2 ^ _hashFn(pair.second.a) << 3;
	return _h1 ^ _h2;
}
