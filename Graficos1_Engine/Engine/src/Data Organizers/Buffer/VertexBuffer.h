#pragma once

class VertexBuffer
{
private:
	unsigned int rendererID;
public:
	VertexBuffer(const void* data, unsigned int size, bool dataIsStatic);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

};


