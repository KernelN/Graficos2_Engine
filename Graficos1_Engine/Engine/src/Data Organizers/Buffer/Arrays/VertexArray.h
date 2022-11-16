#pragma once
#include "Data Organizers/Buffer/VertexBuffer.h"
#include "Data Organizers/Buffer/Layout/VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int rendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void SetBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};
