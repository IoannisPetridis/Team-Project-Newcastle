#include "OBJMesh.h"

#ifdef WEEK_2_CODE
/*
OBJ files look generally something like this:

v xpos ypos zpos
..more vertices

vt xtex ytex
...more texcoords

vn xnorm ynorm znorm
...more normals

f vert index / tex index / norm index  vert index / tex index / norm index  vert index / tex index / norm index
...more faces

(i.e there's a set of float/float/float for each vertex of a face)

OBJ files can also be split up into a number of submeshes, making loading them
in even more annoying. 
*/

bool	OBJMesh::LoadOBJMesh(std::string filename)	{	
	std::ifstream f(filename.c_str(),std::ios::in);

	if(!f) {//Oh dear, it can't find the file :(
		return false;
	}

	/*
	Stores the loaded in vertex attributes
	*/
	std::vector<Vector2>inputTexCoords;
	std::vector<Vector3>inputVertices;
	std::vector<Vector3>inputNormals;
	/*
	SubMeshes temporarily get kept in here
	*/
	std::vector<OBJSubMesh*> inputSubMeshes;

	//It's safe to assume our OBJ will have a mesh in it ;)
	//to check if the submesh is empty, just check 
	//currentMesh->vertIndices.size() == 0
	OBJSubMesh* currentMesh = new OBJSubMesh();
	inputSubMeshes.push_back(currentMesh);	
	//just for safe sake

	std::string currentMtlLib;
	std::string currentMtlType;

	while(!f.eof()) {
		std::string currentLine;
		f >> currentLine;

		if(currentLine == OBJCOMMENT) {		//This line is a comment, ignore it
			continue;
		}
		else if (currentLine == "0") {
			continue;
		}

		//fill in the submesh
		//this two works together
		else if(currentLine == OBJMTLLIB) {
			f >> currentMtlLib;	//pass it to the new objsubmesh
		}
		else if(currentLine == OBJUSEMTL) {
			currentMesh = new OBJSubMesh();
			inputSubMeshes.push_back(currentMesh);

			currentMesh->mtlSrc = currentMtlLib;

			f >> currentMtlType;

			currentMesh->mtlType = currentMtlType;
		}
		//end

		else if(currentLine == OBJMESH || currentLine == OBJOBJECT) {	//This line is a submesh!
			currentMesh = new OBJSubMesh();
			inputSubMeshes.push_back(currentMesh);

			currentMesh->mtlSrc = currentMtlLib;
			currentMesh->mtlType = currentMtlType;
		}
		//end

		//fill in the three intermediate vector
		else if(currentLine == OBJVERT) {	//This line is a vertex
			Vector3 vertex;
			std::string temp;
			f >> temp;
			vertex.setX(std::stof(temp)); 
			f >> temp;
			vertex.setY(std::stof(temp));
			f >> temp;
			vertex.setZ(std::stof(temp));
			inputVertices.push_back(vertex);
		}
		else if(currentLine == OBJNORM) {	//This line is a Normal!
			Vector3 normal;
			std::string temp;
			f >> temp;
			normal.setX(std::stof(temp));
			f >> temp;
			normal.setY(std::stof(temp));
			f >> temp;
			normal.setZ(std::stof(temp));
			inputNormals.push_back(normal);
		}
		else if(currentLine == OBJTEX) {	//This line is a texture coordinate!
			Vector2 texCoord;
			std::string temp;
			f >> temp;
			texCoord.setX(std::stof(temp));
			f >> temp;
			texCoord.setY(std::stof(temp));
			inputTexCoords.push_back(texCoord);
		}
		//complete 

		else if(currentLine == OBJFACE) {	//This is an object face!
			//push_back new OBJsubMesh
			if(!currentMesh) {
				inputSubMeshes.push_back(new OBJSubMesh());
				currentMesh = inputSubMeshes[inputSubMeshes.size()-1];
			}

			std::string			faceData;		//Keep the entire line in this!
			std::vector<int>	faceIndices;	//Keep the extracted indices in here!
		
			getline(f,faceData);		//Use a string helper function to read in the entire face line

			/*
			It's possible an OBJ might have normals defined, but not tex coords!
			Such files should then have a face which looks like this:

				f <vertex index>//<normal index>

				instead of <vertex index>/<tex coord>/<normal index>

				you can be some OBJ files will have "/ /" instead of "//" though... :(
			*/
			bool	skipTex = false;
			if(faceData.find("//") != std::string::npos) {	
				skipTex = true;
			}

			/*
			Count the number of slashes, but also convert the slashes to spaces
			so that string streaming of ints doesn't fail on the slash

				"f  0/0/0" becomes "f 0 0 0" etc
			*/
			for(size_t i = 0; i < faceData.length(); ++i) {
				if(faceData[i] == '/') {
					faceData[i] = ' ';
				}
			}

			/*
			Now string stream the indices from the string into a temporary
			vector.
			*/
			int tempIndex;
			std::stringstream	ss(faceData);
			//if not replace the slash with space, the slash will be read in using this ss
			while(ss >> tempIndex) {
				faceIndices.push_back(tempIndex);
			}

			//If the face indices vector is a multiple of 3, we're looking at triangles
			//with some combination of vertices, normals, texCoords
			if (faceIndices.size() % 3 == 0) {		//This face is a triangle (probably)!
				if (faceIndices.size() == 3) {	//This face has only vertex information;
					currentMesh->vertIndices.push_back(faceIndices.at(0));
					currentMesh->vertIndices.push_back(faceIndices.at(1));
					currentMesh->vertIndices.push_back(faceIndices.at(2));
				}
				else if (faceIndices.size() == 9) {	//This face has vertex, texcoord and normal information!
					for (int i = 0; i < 9; i += 3) {
						currentMesh->vertIndices.push_back(faceIndices.at(i));
						currentMesh->texIndices.push_back(faceIndices.at(i + 1));
						currentMesh->normIndices.push_back(faceIndices.at(i + 2));
					}
				}
				else if (faceIndices.size() == 6) {	//This face has vertex, and one other index...
					for (int i = 0; i < 6; i += 2) {
						currentMesh->vertIndices.push_back(faceIndices.at(i));
						if (!skipTex) {		// a double slash means it's skipping tex info...
							currentMesh->texIndices.push_back(faceIndices.at(i + 1));
						}
						else{
							currentMesh->normIndices.push_back(faceIndices.at(i + 1));
						}
					}
				}
			}
			//the format is not triangle based 
			else{	
				bool a = true;
			}
			
			//currentMesh = NULL;
		}

		//all the unrecognized line
		else{
			//std::cout << "OBJMesh::LoadOBJMesh Unknown file data:" << currentLine << std::endl;
		}
	}
	//end of while loop 

	f.close();

	//fill in the mesh according to inputdata and submesh indices 
	for(unsigned int i = 0; i < inputSubMeshes.size(); ) {
		OBJSubMesh*	sm = inputSubMeshes[i];

		//check if the submesh is empty, if it is then erase it
		if(sm->vertIndices.empty()) {
			delete sm;
			inputSubMeshes.erase(inputSubMeshes.begin() + i);
			continue;
		}
		else	{
			OBJMesh* m;
			
			if(i == 0) {
				m = this;
			}
			else{
				m = new OBJMesh();
			}

			///////////////////NOT YET!
			
			//m->SetTexturesFromMTL(sm->mtlSrc, sm->mtlType);
			
			///////////////////

			//It is triangle, so both of them should be 3
			//m->numVertices	= 3;
			//m->numIndices	= 3;
			
			m->numVertices = sm->vertIndices.size();
			m->numIndices = sm->vertIndices.size();

			m->indexType	= sce::Gnm::IndexSize::kIndexSize32;
			m->primitiveType = sce::Gnm::PrimitiveType::kPrimitiveTypeTriStrip;
			
			//indices 
			m->indices = new int[m->numIndices];
			for (unsigned int j = 0; j < m->numVertices; ++j) {
				m->indices[j] = j;
			}

			//fill in the vertices vector
			m->vertices		= new Vector3[m->numVertices];
			for(unsigned int j = 0; j < sm->vertIndices.size(); ++j) {
				m->vertices[j] = inputVertices[sm->vertIndices[j] - 1];
			}

			//fill in the uv vector
			if(!sm->texIndices.empty())	{
				m->texCoords	= new Vector2[m->numVertices];
				for(unsigned int j = 0; j < sm->texIndices.size(); ++j) {
					m->texCoords[j] = inputTexCoords[sm->texIndices[j] - 1];
				}
			}
			//use the default uv vector
			else{
				m->texCoords = new Vector2[m->numVertices];
				m->texCoords[0] = Vector2(0.5f, 0.0f);
				m->texCoords[1] = Vector2(1.0f, 1.0f);
				m->texCoords[2] = Vector2(0.0f, 1.0f);
			}

#ifdef OBJ_USE_NORMALS
			if(sm->normIndices.empty()) {
				m->GenerateNormals();
			}
			else{
				m->normals		= new Vector3[m->numVertices];

				for(unsigned int j = 0; j < sm->normIndices.size(); ++j) {
					m->normals[j] = inputNormals[sm->normIndices[j]-1];
				}
			}
#endif
#ifdef OBJ_USE_TANGENTS_BUMPMAPS
			m->GenerateTangents();
#endif
		
			m->BufferData();

			if(i != 0) {
				AddChild(m);
			}	
		}
		//end of filling in OBJMesh and its children if there is any

		delete inputSubMeshes[i];
		++i;
	}

	return true;
}

void	OBJMesh::SubmitDraw(Gnmx::GnmxGfxContext& cmdList, Gnm::ShaderStage stage) {
	PS4Mesh::SubmitDraw(cmdList, stage);
	for(unsigned int i = 0; i < children.size(); ++i) {
		children.at(i)->SubmitDraw(cmdList, stage);
	}
};


/*
void	OBJMesh::SetTexturesFromMTL(string &mtlFile, string &mtlType) {
	if(mtlType.empty() || mtlFile.empty()) {
		return;
	}

	map <string, MTLInfo>::iterator i = materials.find(mtlType);

	if(i != materials.end()) {
		if(!i->second.diffuse.empty())	{
			//texture should be a field in PS4Mesh class 
			texture = i->second.diffuseNum;
		}

		if(!i->second.bump.empty())	{
			//so is bumpTexture
			bumpTexture = i->second.bumpNum;
		}

		return;
	}

	std::ifstream f(string(MESHDIR + mtlFile).c_str(),std::ios::in);

	if(!f) {//Oh dear, it can't find the file :(
		return;
	}

	MTLInfo currentMTL;
	string  currentMTLName;
	
	int mtlCount = 0;

	while(!f.eof()) {
		std::string currentLine;
		f >> currentLine;
		
		if(currentLine == MTLNEW) {
			if(mtlCount > 0) {

#ifdef OBJ_FIX_TEXTURES
				FixTextures(currentMTL);
#endif

				materials.insert(std::make_pair(currentMTLName,currentMTL));
			}
			currentMTL.diffuse = "";
			currentMTL.bump = "";

			f >> currentMTLName;

			mtlCount++;		
		}
		else if(currentLine == MTLDIFFUSEMAP) {
			f >> currentMTL.diffuse;

			if(currentMTL.diffuse.find_last_of('/') != string::npos) {
				int at = currentMTL.diffuse.find_last_of('/');
				currentMTL.diffuse = currentMTL.diffuse.substr(at+1);
			}
			else if(currentMTL.diffuse.find_last_of('\\') != string::npos) {
				int at = currentMTL.diffuse.find_last_of('\\');
				currentMTL.diffuse = currentMTL.diffuse.substr(at+1);
			}

			if(!currentMTL.diffuse.empty()) {
				currentMTL.diffuseNum = SOIL_load_OGL_texture(string(TEXTUREDIR + currentMTL.diffuse).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
			}
		}
		else if(currentLine == MTLBUMPMAP || currentLine == MTLBUMPMAPALT) {
			f >> currentMTL.bump;

			if(currentMTL.bump.find_last_of('/') != string::npos) {
				int at = currentMTL.bump.find_last_of('/');
				currentMTL.bump = currentMTL.bump.substr(at+1);
			}
			else if(currentMTL.bump.find_last_of('\\') != string::npos) {
				int at = currentMTL.bump.find_last_of('\\');
				currentMTL.bump = currentMTL.bump.substr(at+1);
			}

			if(!currentMTL.bump.empty()) {
				currentMTL.bumpNum = SOIL_load_OGL_texture(string(TEXTUREDIR + currentMTL.bump).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
			}
		}
	}

#ifdef OBJ_FIX_TEXTURES
	FixTextures(currentMTL);
#endif

	materials.insert(std::make_pair(currentMTLName,currentMTL));

	
	SetTexturesFromMTL(mtlFile,mtlType);
}

void	OBJMesh::FixTextures(MTLInfo &info) {
	if(!info.bumpNum) {

		string temp = info.diffuse;

		if(temp[temp.size() - 5] == 'd') {
			temp[temp.size() - 5] = 'n';
		}
		else {
			temp.insert(temp.size() - 4, "_n");
		}

		info.bump = temp;

		//will return "this" bumpNum a GLuint texture index 
		info.bumpNum = SOIL_load_OGL_texture(string(TEXTUREDIR + info.bump).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |  SOIL_FLAG_TEXTURE_REPEATS);
	}
}*/
#endif
