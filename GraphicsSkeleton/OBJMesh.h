#include "common.h"

#ifdef WEEK_2_CODE
#define OBJ_USE_NORMALS
#define OBJ_USE_TANGENTS_BUMPMAPS

//New! 

#define OBJ_FIX_TEXTURES


#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#include "PS4Mesh.h"
#include "Mesh.h"
#include "ChildMeshInterface.h"

#define OBJOBJECT		"object"	//the current line of the obj file defines the start of a new material
#define OBJMTLLIB		"mtllib"
#define OBJUSEMTL		"usemtl"	//the current line of the obj file defines the start of a new material
#define OBJMESH			"g"			//the current line of the obj file defines the start of a new face
#define OBJCOMMENT		"#"			//The current line of the obj file is a comment
#define OBJVERT			"v"			//the current line of the obj file defines a vertex
#define OBJTEX			"vt"		//the current line of the obj file defines texture coordinates
#define OBJNORM			"vn"		//the current line of the obj file defines a normal
#define OBJFACE			"f"			//the current line of the obj file defines a face

#define MTLNEW			"newmtl"
#define MTLDIFFUSE		"Kd"
#define MTLSPEC			"Ks"
#define MTLSPECWT		"Ns"
#define MTLTRANS		"d"
#define MTLTRANSALT		"Tr"
#define MTLILLUM		"illum"
#define MTLDIFFUSEMAP	"map_Kd"
#define MTLBUMPMAP		"map_bump"
#define MTLBUMPMAPALT	"bump"



/*
OBJSubMesh structs are used to temporarily keep the data loaded 
in from the OBJ files, before being parsed into a series of
Meshes
*/
struct OBJSubMesh {
	std::vector<int> texIndices;
	std::vector<int> vertIndices;
	std::vector<int> normIndices;

	int indexOffset;

	//the texture info
	std::string mtlType;
	std::string mtlSrc;
};

struct MTLInfo {
	std::string bump;
	std::string diffuse;

	int bumpNum;
	int	diffuseNum;

	MTLInfo() {
		bumpNum		= 0;
		diffuseNum	= 0;
	}
	//this is all we care about...
};

class OBJMesh : public PS4Mesh, public ChildMeshInterface	{
	friend class PS4Mesh;
public:
	OBJMesh(void){};
	OBJMesh(std::string filename){	
		
		bool init = LoadOBJMesh(filename);	

		if (init) std::cout << "OBJTexture Loaded In" << std::endl;
		else std::cout << "OBJTexture Loading Failed" << std::endl;
	}

	virtual ~OBJMesh(void){};

	//fill in all the needed stuff
	virtual bool	LoadOBJMesh(std::string filename);

protected:
	//virtual void	SubmitPreDraw(Gnmx::GnmxGfxContext& cmdList, Gnm::ShaderStage stage);
	virtual void	SubmitDraw(Gnmx::GnmxGfxContext& cmdList, Gnm::ShaderStage stage);

	///////////////For Texture
	
	//void	SetTexturesFromMTL(string &mtlFile, string &mtlType);
	//void	FixTextures(MTLInfo &info);

	//map <string, MTLInfo> materials;
};

#endif