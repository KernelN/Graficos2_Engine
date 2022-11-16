#include "Data Organizers/Buffer/Arrays/VertexArray.h"
#include <glew/include/GL/glew.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &rendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	
	vb.Bind();

	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		

		//https://docs.gl/gl4/glEnableVertexAttribArray
		glEnableVertexAttribArray(i);

		//SET POS
		//https://docs.gl/gl4/glVertexAttribPointer
		unsigned int stride = layout.GetStride();
		glVertexAttribPointer(i, element.count, element.type, element.normalized, stride, (const void*)offset);

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

void VertexArray::SetBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();

	vb.Bind();

	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];


		//https://docs.gl/gl4/glEnableVertexAttribArray
		glEnableVertexAttribArray(i);

		//SET POS
		//https://docs.gl/gl4/glVertexAttribPointer
		unsigned int stride = layout.GetStride();
		glVertexAttribPointer(i, element.count, element.type, element.normalized, stride, (const void*)offset);

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}


void VertexArray::Bind() const
{
	glBindVertexArray(rendererID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
