#pragma once
#include "Mesh.h"
#include "PS4MemoryAware.h"

#include <gnm.h>

#include <gnmx\context.h>
#include <..\samples\sample_code\graphics\api_gnm\toolkit\allocators.h>
#include <..\samples\sample_code\graphics\api_gnm\toolkit\stack_allocator.h>
#include <gnm\dataformats.h>

using namespace sce;

class PS4Mesh :
	public Mesh, public PS4MemoryAware
{
	friend class PS4RendererBase;
	friend class ChildMeshInterface;
public:
	static PS4Mesh* GenerateTriangle();
	static PS4Mesh* GenerateQuad();
	static PS4Mesh* GenerateSinglePoint();

	virtual void	SubmitDraw(Gnmx::GnmxGfxContext& cmdList, Gnm::ShaderStage stage);
protected:
	virtual void	SubmitPreDraw(Gnmx::GnmxGfxContext& cmdList, Gnm::ShaderStage stage) {};
	

	void	BufferData();

	//fill in a GNM buffer with vertex attribute data
	void	InitAttributeBuffer(sce::Gnm::Buffer &buffer, Gnm::DataFormat format, void*offset);

protected:
	//Generates normals for all facets. Assumes geometry type is GL_TRIANGLES...
	void	GenerateNormals();

	//Generates tangents for all facets. Assumes geometry type is GL_TRIANGLES...
	void	GenerateTangents();
	Vector3 GenerateTangent(const Vector3 &a, const Vector3 &b, const Vector3 &c,
		const Vector2 &ta, const Vector2 &tb, const Vector2 &tc);


protected:
	PS4Mesh();
	~PS4Mesh();

protected:
	//Gpu simply has a 4 byte alignment!
	struct MeshVertex
	{
		float position[3];
		float textureCoord[2];
		float normal[3];
		float tangent[3];
	};

	//how many bytes an index takes up
	sce::Gnm::IndexSize		indexType;
	//the primiteve type
	sce::Gnm::PrimitiveType primitiveType;

	int*		indexBuffer;
	MeshVertex*	vertexBuffer;

	int	vertexDataSize;
	int indexDataSize;

	sce::Gnm::Buffer*	attributeBuffers;
	int					attributeCount;
};

