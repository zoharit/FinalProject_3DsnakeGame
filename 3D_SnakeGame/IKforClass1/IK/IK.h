#pragma once
#include "scene.h"
#include <iostream>

const int linksNum = 5;
const int maximumIterations = 1;

class IK : public Scene
{
	bool cameraMode;
	glm::vec3 tipPosition;
	glm::vec3 distPosition;
	bool isIKactive;
	double delta;
	float maxDistance;

public:

	IK(void);
	virtual ~IK(void);
	IK(glm::vec3 position, float angle, float hwRelation, float near, float far);

	void init(Vertex *vertices, unsigned int *indices, int verticesSize, int indicesSize);
	void IK::showcave(bool reset);
	void addShape(int type, int parent);
	void addShape(const std::string& fileName, int parent, int maxfaces);
	void addShape(const std::string& fileName, const std::string& textureFileName, int parent, int maxfaces);
	void addShape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, int parent, int maxfaces);
	void addShape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const std::string& textureFileName, int parent, int maxfaces);
	void addShape(int CylParts, int linkPosition, int parent, int maxfaces);
	void addShape(int CylParts, int linkPosition, const std::string& textureFileName, int parent, int maxfaces);
	void IK::medium();
	void IK::hide_hard();
	void IK::hide_medium();
	void IK::show_easy(bool rest);
	void IK::show_hard(bool rest);
	void IK::show_medium(bool reset);
	void IK::menu(Vertex *vertices, unsigned int *indices, int verticesSize, int indicesSize, int id);
	void IK::hard();
	void inline changeMode() { cameraMode = !cameraMode; }
	void makeChange();
	void calculateStep(std::vector<glm::vec3> zAlignedPos, std::vector<glm::vec3> prevPos, std::vector<glm::vec3> newPos/*bool EulerVersion*/);
	float Distance(int indx1, int indx2);
	bool inline isActive() const { return isIKactive; }
	void inline dActivate() { isIKactive = false; }
	void inline setActive() { isIKactive = true; }

	//@Added
	glm::vec3 getPrevAxis(int index, int axis);
	bool getMode() { return cameraMode; }
	float distToTarget(int linkInd);
	void printVec(glm::vec3 v, std::string funcName);
	void printPos(std::vector<glm::vec3> pos);

};

