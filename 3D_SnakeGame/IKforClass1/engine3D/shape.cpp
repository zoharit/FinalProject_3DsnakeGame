#include "shape.h"

Shape::Shape(const Shape& shape, glm::vec4 amb)
{
	if(shape.mesh)
		mesh = shape.mesh;
	if(shape.lineMesh)
		lineMesh = shape.lineMesh;
	tex = shape.tex;
	isCopy = true;
	//ambient = amb;
	ambient = glm::vec4(1, 1, 1, 1);

}
Shape::Shape(const std::string& fileName, glm::vec4 amb, int maxFaces){
	mesh = new Mesh(fileName,true,maxFaces);
	tex = 0;
	isCopy = false;
//	ambient = amb;
	ambient = glm::vec4(1, 1, 1, 1);
}



Vertex* Shape::initcube(double centerx, double centery, double centerz, double widthx, double highty, double depthz) {

	Vertex* myCube = (Vertex*)malloc(24 * sizeof(Vertex) * 44);
	myCube[0] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(1, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, 1));
	myCube[1] = Vertex(glm::vec3(-widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, 1));
	myCube[2] = Vertex(glm::vec3(widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 1), glm::vec3(0, 0, -1), glm::vec3(0, 0, 1));
	myCube[3] = Vertex(glm::vec3(widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(1, 1), glm::vec3(0, 0, -1), glm::vec3(0, 0, 1));

	myCube[4] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 0), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));
	myCube[5] = Vertex(glm::vec3(-widthx + centerx, highty + centery, depthz + centerz), glm::vec2(0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));
	myCube[6] = Vertex(glm::vec3(widthx + centerx, highty + centery, depthz + centerz), glm::vec2(0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));
	myCube[7] = Vertex(glm::vec3(widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));

	myCube[8] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(0, 1), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));
	myCube[9] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 1), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));
	myCube[10] = Vertex(glm::vec3(widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 0), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));
	myCube[11] = Vertex(glm::vec3(widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(0, 0), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));

	myCube[12] = Vertex(glm::vec3(-widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 1), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	myCube[13] = Vertex(glm::vec3(-widthx + centerx, highty + centery, depthz + centerz), glm::vec2(1, 1), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	myCube[14] = Vertex(glm::vec3(widthx + centerx, highty + centery, depthz + centerz), glm::vec2(1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	myCube[15] = Vertex(glm::vec3(widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	myCube[16] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(1, 1), glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0));
	myCube[17] = Vertex(glm::vec3(-widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 0), glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0));
	myCube[18] = Vertex(glm::vec3(-widthx + centerx, highty + centery, depthz + centerz), glm::vec2(0, 0), glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0));
	myCube[19] = Vertex(glm::vec3(-widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 1), glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0));

	myCube[20] = Vertex(glm::vec3(widthx + centerx, -highty + centery, -depthz + centerz), glm::vec2(1, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
	myCube[21] = Vertex(glm::vec3(widthx + centerx, -highty + centery, depthz + centerz), glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
	myCube[22] = Vertex(glm::vec3(widthx + centerx, highty + centery, depthz + centerz), glm::vec2(0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
	myCube[23] = Vertex(glm::vec3(widthx + centerx, highty + centery, -depthz + centerz), glm::vec2(0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
	return myCube;
}


Shape::Shape(const std::string& fileName,const std::string& textureFileName, glm::vec4 amb, int maxfaces){
	mesh = new Mesh(fileName,true, maxfaces); 
	tex = new Texture(textureFileName);
	isCopy = false;
	Kdtree tree = mesh->kdtree;
//	Vertex* tmp = initcube(tree.getRoot()->center.x, tree.getRoot()->center.y, tree.getRoot()->center.z, tree.getRoot()->halfwidthX, tree.getRoot()->halfhightY, tree.getRoot()->halfdepthZ);
//	this->mycube = new Mesh(tmp, (sizeof(tmp) * 44 * 24) / sizeof(tmp[0]), indices, sizeof(indices) / sizeof(indices[0]), false);
//	ambient = amb;
	diffuse = glm::vec4(0.2,0.1,0.4,1);
	ambient = glm::vec4(1, 1, 1, 1);

}

Shape::Shape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, glm::vec4 amb)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices,true);
	tex = 0; 
	isCopy = false;
	Kdtree tree = mesh->kdtree;
//	Vertex* tmp = initcube(tree.getRoot()->center.x, tree.getRoot()->center.y, tree.getRoot()->center.z, tree.getRoot()->halfwidthX, tree.getRoot()->halfhightY, tree.getRoot()->halfdepthZ);
//this->mycube = new Mesh(tmp, (sizeof(tmp) * 44 * 24) / sizeof(tmp[0]), indices, sizeof(indices) / sizeof(indices[0]), false);
//	ambient = amb;
	ambient = glm::vec4(1, 1, 1, 1);
	diffuse = glm::vec4(0.2, 0.1, 0.4, 1);

}

Shape::Shape(LineVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, glm::vec4 amb)
{

	lineMesh = new LineMesh(vertices,numVertices,indices,numIndices);
	tex = 0; 
	isCopy = false;
//	ambient = amb;
	ambient = glm::vec4(1, 1, 1, 1);
	diffuse = glm::vec4(0.2, 0.1, 0.4, 1);

}


Shape::Shape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices,const std::string& textureFileName, glm::vec4 amb)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices,true);
	tex = new Texture(textureFileName);
	isCopy = false;
	Kdtree tree = mesh->kdtree;
	//printf("%d\n", tree.getRoot()->halfwidthX + 5);
	diffuse = glm::vec4(0.2, 0.1, 0.4, 1);

	//Vertex* tmp = initcube(tree.getRoot()->center.x, tree.getRoot()->center.y, tree.getRoot()->center.z, tree.getRoot()->halfwidthX, tree.getRoot()->halfhightY, tree.getRoot()->halfdepthZ);
	//this->mycube = new Mesh(tmp, (sizeof(tmp) * 44 * 24) / sizeof(tmp[0]), indices, sizeof(indices) / sizeof(indices[0]), false);
//	ambient = amb;
	ambient = glm::vec4(1, 1, 1, 1);

}

	Shape::Shape(int CylParts,int linkPosition, glm::vec4 amb)
	{
		ambient = amb;
		mesh = new Mesh(CylParts,linkPosition,true);
		tex = 0; 
		isCopy = false;
		Kdtree tree = mesh->kdtree;
	//	Vertex* tmp = initcube(tree.getRoot()->center.x, tree.getRoot()->center.y, tree.getRoot()->center.z, tree.getRoot()->halfwidthX+5, tree.getRoot()->halfhightY+5, tree.getRoot()->halfdepthZ+5);

		//this->mycube = new Mesh(tmp, (sizeof(tmp) * 44 * 24) / sizeof(tmp[0]), indices, sizeof(indices) / sizeof(indices[0]), false);
		diffuse = glm::vec4(0.2, 0.1, 0.4, 1);

	}
	Shape::Shape(int CylParts,int linkPosition,const std::string& textureFileName, glm::vec4 amb)
	{
//		ambient = amb;
		mesh = new Mesh(CylParts,linkPosition,true);
		tex = new Texture(textureFileName); 
		isCopy = false;
		Kdtree tree = mesh->kdtree;

		//Vertex* tmp = initcube(tree.getRoot()->center.x, tree.getRoot()->center.y, tree.getRoot()->center.z, tree.getRoot()->halfwidthX, tree.getRoot()->halfhightY, tree.getRoot()->halfdepthZ);
		diffuse = glm::vec4(0.2, 0.1, 0.4, 1);

	//	this->mycube = new Mesh(tmp, (sizeof(tmp) * 44 * 24) / sizeof(tmp[0]), indices, sizeof(indices) / sizeof(indices[0]), false);
		ambient = glm::vec4(1, 1, 1, 1);

	}

void Shape::addMesh(Vertex* vertices, unsigned int numVertices,unsigned int* indices, unsigned int numIndices, const std::string& textureFileName)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices,true);
	tex = new Texture(textureFileName);
}

void Shape::addMesh(Vertex* vertices, unsigned int numVertices,unsigned int* indices, unsigned int numIndices)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices,true);
}

void Shape::addLineMesh(LineVertex* vertices, unsigned int numVertices,unsigned int* indices, unsigned int numIndices)
{
	lineMesh = new LineMesh(vertices,numVertices,indices,numIndices);
}

void Shape::draw(int mode)
{
	//transformations
	if (tex)
		tex->Bind();

	if (mesh)
	{
		mesh->Draw(mode);
	//	if (this->mycube != 0)
		//{
	//		mycube->Draw(2);
	//	}
	}

	if (lineMesh)
		lineMesh->Draw();
}

Shape::~Shape(void)
{
	if(!isCopy)
	{
		if(mesh)
 			delete mesh;
		if(lineMesh)
			delete lineMesh;
		if(tex)
			delete tex;
	}
}
