#pragma once
#include "Data Organizers/Buffer/VertexBuffer.h"
#include "Data Organizers/Buffer/Layout/VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int rendererID;
	std::vector<VertexBuffer*> vertexBuffers;
	std::vector<VertexBufferLayout> layouts;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer* vb, const VertexBufferLayout& layout);
	void SetBuffer(unsigned int bufferID);

	void Bind() const;
	void UnBind() const;
};
