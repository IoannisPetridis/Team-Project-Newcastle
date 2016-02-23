#include "PS4Mesh.h"

PS4Mesh::PS4Mesh()
{
	//two pointer set to 0
	indexBuffer		= 0;
	vertexBuffer	= 0;
	attributeCount	= 0;
}


PS4Mesh::~PS4Mesh()
{
	delete[] attributeBuffers;
}

PS4Mesh* PS4Mesh::GenerateQuad() {
	//Generate new mesh to push back
	PS4Mesh* mesh = new PS4Mesh();

	mesh->numVertices	= 4;
	mesh->numIndices	= 4;
	mesh->indexType		= sce::Gnm::IndexSize::kIndexSize32;
	mesh->primitiveType = sce::Gnm::PrimitiveType::kPrimitiveTypeTriStrip;

	mesh->vertices  = new Vector3[mesh->numVertices];
	mesh->texCoords = new Vector2[mesh->numVertices];
	mesh->normals   = new Vector3[mesh->numVertices];
	mesh->tangents  = new Vector3[mesh->numVertices];
	mesh->indices   = new int[mesh->numIndices];

	mesh->vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
	mesh->vertices[1] = Vector3(-1.0f,  1.0f, 0.0f);
	mesh->vertices[2] = Vector3( 1.0f, -1.0f, 0.0f);
	mesh->vertices[3] = Vector3( 1.0f,  1.0f, 0.0f);

	for (int i = 0; i < mesh->numVertices; ++i) {
		mesh->normals[i]  = Vector3(0, 0, 1);
		mesh->tangents[i] = Vector3(1, 0, 0);
		mesh->indices[i]  = i;
	}

	mesh->BufferData();
	return mesh;
}

PS4Mesh* PS4Mesh::GenerateSinglePoint() {
	PS4Mesh* mesh = new PS4Mesh();

	mesh->numVertices	= 1;
	mesh->numIndices	= 1;
	mesh->indexType		= sce::Gnm::IndexSize::kIndexSize32;
	mesh->primitiveType = sce::Gnm::PrimitiveType::kPrimitiveTypePointList;

	mesh->vertices	= new Vector3[mesh->numVertices];
	mesh->texCoords = new Vector2[mesh->numVertices];
	mesh->normals	= new Vector3[mesh->numVertices];
	mesh->tangents	= new Vector3[mesh->numVertices];
	mesh->indices	= new int[mesh->numIndices];

	mesh->vertices[0] = Vector3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < mesh->numVertices; ++i) {
		mesh->normals[i]	= Vector3(0, 0, 1);
		mesh->tangents[i]	= Vector3(1, 0, 0);
		mesh->indices[i]	= i;
	}

	mesh->BufferData();
	return mesh;
}

PS4Mesh* PS4Mesh::GenerateTriangle() {
	PS4Mesh* mesh = new PS4Mesh();

	mesh->numVertices	= 3;
	mesh->numIndices	= 3;
	mesh->indexType		= sce::Gnm::IndexSize::kIndexSize32;
	mesh->primitiveType = sce::Gnm::PrimitiveType::kPrimitiveTypeTriList;

	mesh->vertices = new Vector3[mesh->numVertices];
	mesh->texCoords = new Vector2[mesh->numVertices];
	mesh->normals = new Vector3[mesh->numVertices];
	mesh->tangents = new Vector3[mesh->numVertices];
	mesh->indices = new int[mesh->numIndices];

	mesh->vertices[0] = Vector3(0.0f, 0.5f, 0.0f); 
	mesh->vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
	mesh->vertices[2] = Vector3(-0.5f, -0.5f, 0.0f);

	mesh->texCoords[0] = Vector2(0.5f, 0.0f);
	mesh->texCoords[1] = Vector2(1.0f, 1.0f);
	mesh->texCoords[2] = Vector2(0.0f, 1.0f);

	for (int i = 0; i < mesh->numVertices; ++i) {
		mesh->normals[i] = Vector3(0, 0, 1);
		mesh->tangents[i] = Vector3(1, 0, 0);
		mesh->indices[i] = i;
	}

	mesh->BufferData();
	return mesh;
}

void	PS4Mesh::BufferData() {
	vertexDataSize = numVertices * sizeof(MeshVertex);
	indexDataSize  = numIndices * sizeof(int);

	indexBuffer = static_cast<int*>			(garlicAllocator.allocate(indexDataSize, Gnm::kAlignmentOfBufferInBytes));
	vertexBuffer = static_cast<MeshVertex*>	(garlicAllocator.allocate(vertexDataSize, Gnm::kAlignmentOfBufferInBytes));

	Gnm::registerResource(nullptr, ownerHandle, indexBuffer , indexDataSize , "IndexData" , Gnm::kResourceTypeIndexBufferBaseAddress, 0);
	Gnm::registerResource(nullptr, ownerHandle, vertexBuffer, vertexDataSize, "VertexData", Gnm::kResourceTypeIndexBufferBaseAddress, 0);


	//int vAt = 0;
	for (int i = 0; i < numVertices; ++i) {
		memcpy(&vertexBuffer[i].position,	  &vertices[i],	 sizeof(float) * 3);
		memcpy(&vertexBuffer[i].textureCoord, &texCoords[i], sizeof(float) * 2);
		memcpy(&vertexBuffer[i].normal,		  &normals[i],   sizeof(float) * 3);
		memcpy(&vertexBuffer[i].tangent,	  &tangents[i],  sizeof(float) * 3);
	}

	for (int i = 0; i < numIndices; ++i) { //Our index buffer might not have the same data size as the source indices?
		indexBuffer[i] = indices[i];
	}	

	attributeCount		= 4;
	attributeBuffers	= new sce::Gnm::Buffer[4];

	InitAttributeBuffer(attributeBuffers[0], Gnm::kDataFormatR32G32B32Float, &(vertexBuffer[0].position));
	InitAttributeBuffer(attributeBuffers[1], Gnm::kDataFormatR32G32Float	, &(vertexBuffer[0].textureCoord));
	InitAttributeBuffer(attributeBuffers[2], Gnm::kDataFormatR32G32B32Float, &(vertexBuffer[0].normal));
	InitAttributeBuffer(attributeBuffers[3], Gnm::kDataFormatR32G32B32Float, &(vertexBuffer[0].tangent));
}

void	PS4Mesh::InitAttributeBuffer(sce::Gnm::Buffer &buffer, Gnm::DataFormat format, void*offset) {
	int lolz = sizeof(MeshVertex);
	buffer.initAsVertexBuffer(offset, format, sizeof(MeshVertex), numVertices);
	buffer.setResourceMemoryType(Gnm::kResourceMemoryTypeRO);
}

//void	PS4Mesh::SubmitPreDraw(Gnmx::GnmxGfxContext& cmdList, Gnm::ShaderStage stage) {
//	
//}

void PS4Mesh::SubmitDraw(Gnmx::GnmxGfxContext& cmdList, Gnm::ShaderStage stage) {
	cmdList.setVertexBuffers(stage, 0, attributeCount, attributeBuffers);
	cmdList.setPrimitiveType(primitiveType);
	cmdList.setIndexSize(indexType);
	cmdList.drawIndex(numIndices, indexBuffer);
} 

//need numVertices
void	PS4Mesh::GenerateNormals()	{
	if (!normals) {
		normals = new Vector3[numVertices];
	}
	for (int i = 0; i < numVertices; ++i){
		normals[i] = Vector3();
	}

	if (indices) {
		int i = 0;

		int test = 0;
		for (i = 0; i < numIndices; i += 3){
			int a = indices[i];
			int b = indices[i + 1];
			int c = indices[i + 2];

			
			Vector3 normal = cross((vertices[b] - vertices[a]), (vertices[c] - vertices[a]));
			
			normals[a] += normal;
			normals[b] += normal;
			normals[c] += normal;

			test += 3;
		}
		bool asdf = true;
	}
	else{
		//It's just a list of triangles, so generate face normals
		for (int i = 0; i < numVertices; i += 3){
			Vector3 &a = vertices[i];
			Vector3 &b = vertices[i + 1];
			Vector3 &c = vertices[i + 2];

			Vector3 normal = cross(b - a, c - a);

			normals[i] = normal;
			normals[i + 1] = normal;
			normals[i + 2] = normal;
		}
	}

	for (int i = 0; i < numVertices; ++i){
		normalize(normals[i]);
	}
}

void PS4Mesh::GenerateTangents() {
	//Extra! stops rare occurrence of this function being called
	//on a mesh without tex coords, which would break quite badly!
	if (!texCoords) {
		return;
	}

	if (!tangents) {
		tangents = new Vector3[numVertices];
	}
	for (int i = 0; i < numVertices; ++i){
		tangents[i] = Vector3();
	}

	if (indices) {
		for (int i = 0; i < numIndices; i += 3){
			int a = indices[i];
			int b = indices[i + 1];
			int c = indices[i + 2];

			Vector3 tangent = GenerateTangent(vertices[a], vertices[b], vertices[c], texCoords[a], texCoords[b], texCoords[c]);

			tangents[a] += tangent;
			tangents[b] += tangent;
			tangents[c] += tangent;
		}
	}
	else{
		for (int i = 0; i < numVertices; i += 3){
			Vector3 tangent = GenerateTangent(vertices[i], vertices[i + 1], vertices[i + 2], texCoords[i], texCoords[i + 1], texCoords[i + 2]);

			tangents[i] += tangent;
			tangents[i + 1] += tangent;
			tangents[i + 2] += tangent;
		}
	}
	for (int i = 0; i < numVertices; ++i){
		normalize(tangents[i]);
	}
}

Vector3 PS4Mesh::GenerateTangent(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Vector2 &ta, const Vector2 &tb, const Vector2 &tc)	 {
	Vector2 coord1 = tb - ta;
	Vector2 coord2 = tc - ta;

	Vector3 vertex1 = b - a;
	Vector3 vertex2 = c - a;

	Vector3 axis = Vector3(vertex1*coord2.getY() - vertex2*coord1.getY());

	float factor = 1.0f / (coord1.getX() * coord2.getY() - coord2.getX() * coord1.getY());

	return axis * factor;
}