#include "Renderer.h"

#include <GLCore.h>
#include <array>
#include <glad\glad.h>

const size_t MaxQuadCount = 7000;
const size_t MaxVertexCount = MaxQuadCount * 4;
const size_t MaxIndexCount = MaxQuadCount * 6;

//Use openGL code to Query the driver, find how many Texture slots the GPU have
static const size_t MaxTextures = 32;

struct Vertex
{
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoords;
	float TexIndex;
};

struct RendererData
{
	GLuint QuadVA = 0, QuadVB = 0, QuadIB = 0;

	GLuint WhiteTexture = 0;
	uint32_t WhiteTextureSlot = 0;

	//Indices to draw when flushed
	uint32_t IndexCount = 0;

	//Points beginning of the buffer. This is in CPU
	Vertex* QuadBuffer = nullptr;
	//Where we are up to
	Vertex* QuadBufferPtr = nullptr;

	//Which Texture slot holds to what OpenGL ID
	std::array<uint32_t, MaxTextures> TextureSlots;
	uint32_t TextureSlotIndex = 1;
	
	Renderer::Stats RenderStats;
};

//static inside translation unit
static RendererData s_Data;

void Renderer::Init()
{
	//Add check to make sure Init is not call twice
	//if(QuadBufferPtr != nullptr) return;
	s_Data.QuadBuffer = new Vertex[MaxVertexCount];

	glCreateVertexArrays(1, &s_Data.QuadVA);
	glBindVertexArray(s_Data.QuadVA);

	glCreateBuffers(1, &s_Data.QuadVB);
	glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB);
	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexArrayAttrib(s_Data.QuadVA, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

	glEnableVertexArrayAttrib(s_Data.QuadVA, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

	glEnableVertexArrayAttrib(s_Data.QuadVA, 2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));

	glEnableVertexArrayAttrib(s_Data.QuadVA, 3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexIndex));

	/*uint32_t indices[] = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};*/

	uint32_t indices[MaxIndexCount];
	uint32_t offset = 0;
	for (size_t i = 0; i < MaxIndexCount; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	//Sending to GPU
	glCreateBuffers(1, &s_Data.QuadIB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.QuadIB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//1 x 1 white texture
	glCreateTextures(GL_TEXTURE_2D, 1, &s_Data.WhiteTexture);
	glBindTexture(GL_TEXTURE_2D, s_Data.WhiteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	uint32_t color = 0xffffffff;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, &color);

	s_Data.TextureSlots[0] = s_Data.WhiteTexture;
	//memory clear, alternatively use memset
	for (size_t i = 1; i < MaxTextures; i++)
		s_Data.TextureSlots[i] = 0;
}

void Renderer::Shutdown()
{
	glDeleteVertexArrays(1, &s_Data.QuadVA);
	glDeleteBuffers(1, &s_Data.QuadVB);
	glDeleteBuffers(1, &s_Data.QuadIB);

	glDeleteTextures(1, &s_Data.WhiteTexture);

	delete[] s_Data.QuadBuffer;
}

void Renderer::BeginBatch()
{
	// Resets point to the begining
	// pointer keeps traks of where we copying the data to 
	// in the cpu side vertex buffer
	s_Data.QuadBufferPtr = s_Data.QuadBuffer;
}

void Renderer::EndBatch()
{
	GLsizeiptr size = (uint8_t*)s_Data.QuadBufferPtr - (uint8_t*)s_Data.QuadBuffer;
	glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.QuadBuffer);
}

void Renderer::Flush()
{
	for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		glBindTextureUnit(i, s_Data.TextureSlots[i]);

	glBindVertexArray(s_Data.QuadVA);
	glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, nullptr);
	s_Data.RenderStats.DrawCount++;

	s_Data.IndexCount = 0;
	s_Data.TextureSlotIndex = 1;
}

void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	if (s_Data.IndexCount >= MaxIndexCount)
	{
		EndBatch();
		Flush();
		BeginBatch();
	}
	float textureIndex = 0.0f;

	s_Data.QuadBufferPtr->Position = { position.x, position.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
	s_Data.QuadBufferPtr->TexIndex = textureIndex;
	s_Data.QuadBufferPtr++;

	s_Data.QuadBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 1.0f, 0.0f };
	s_Data.QuadBufferPtr->TexIndex = textureIndex;
	s_Data.QuadBufferPtr++;

	s_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 1.0f, 1.0f };
	s_Data.QuadBufferPtr->TexIndex = textureIndex;
	s_Data.QuadBufferPtr++;

	s_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 0.0f, 1.0f };
	s_Data.QuadBufferPtr->TexIndex = textureIndex;
	s_Data.QuadBufferPtr++;

	s_Data.IndexCount += 6;
	s_Data.RenderStats.QuadCount++;
	
}

void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, uint32_t textureID)
{
	if (s_Data.IndexCount >= MaxIndexCount || s_Data.TextureSlotIndex > 31)
	{
		EndBatch();
		Flush();
		BeginBatch();
	}

	constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	float textureIndex = 0.0f;

	// You can use Hashset
	for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
	{
		if (s_Data.TextureSlots[i] == textureID)
		{
			textureIndex = (float)i;
			break;
		}
	}

	//White texture
	if (textureIndex == 0.0f)
	{
		//Assign to next available free texture slot index
		textureIndex = (float)s_Data.TextureSlotIndex;
		s_Data.TextureSlots[s_Data.TextureSlotIndex] = textureID;
		s_Data.TextureSlotIndex++;
	}

	s_Data.QuadBufferPtr->Position = { position.x, position.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
	s_Data.QuadBufferPtr->TexIndex = textureIndex;
	s_Data.QuadBufferPtr++;

	s_Data.QuadBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 1.0f, 0.0f };
	s_Data.QuadBufferPtr->TexIndex = textureIndex;
	s_Data.QuadBufferPtr++;

	s_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 1.0f, 1.0f };
	s_Data.QuadBufferPtr->TexIndex = textureIndex;
	s_Data.QuadBufferPtr++;

	s_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 0.0f, 1.0f };
	s_Data.QuadBufferPtr->TexIndex = textureIndex;
	s_Data.QuadBufferPtr++;

	s_Data.IndexCount += 6;
	s_Data.RenderStats.QuadCount++;
	
}

const Renderer::Stats& Renderer::GetStats()
{
	return s_Data.RenderStats;
}

void Renderer::ResetStats()
{
	memset(&s_Data.RenderStats, 0, sizeof(Stats));
}