#include "IK.h"
#include <iostream>

using namespace std;
using namespace glm;
#include <string>
#include <sstream>


IK::IK(void)
{
	cameraMode = false;
	isIKactive = false;
	delta = 1e-1;
	distPosition = vec3(1, 0, 0);
	tipPosition = vec3(0, 0, 2 * linksNum*scaleFactor);
	maxDistance = linksNum * scaleFactor;
	//std::cout << "maxDistance = " << maxDistance << std::endl;
}
IK::IK(vec3 position, float angle, float hwRelation, float near, float far) : Scene(position, angle, hwRelation, near, far)
{
	cameraMode = false;
	isIKactive = false;
	delta = 1e-1;
	distPosition = vec3(1, 0, 0);
	tipPosition = vec3(0, 0, 2 * linksNum*scaleFactor);
	maxDistance = linksNum * scaleFactor; 

}

IK::~IK(void)
{
}

void IK::init(Vertex *vertices, unsigned int *indices, int verticesSize, int indicesSize)
{
	myRotate(-90.0f, vec3(1, 0, 0), -1);
	addShape(0, 2, "./res/textures/skin3.jpg", -1,0);
	pickedShape = 0;
	shapeTransformation(zScale, scaleFactor);
	shapes[pickedShape]->ambient = glm::vec4(0.7, 0.7, 0.7, 1);
	shapes[pickedShape]->diffuse = glm::vec4(1, 0, 0, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);

	shapeTransformation(zGlobalTranslate, -5.0f);
	for (int i = 1; i < linksNum - 1; i++)
	{
		pickedShape = i;
		addShape(1, 1, "./res/textures/skin3.jpg", -1,0);
		shapeTransformation(zScale, scaleFactor);

		shapeTransformation(zGlobalTranslate, 3.0);
		shapes[pickedShape]->ambient = glm::vec4(0.7, 0.7, 0.7, 1);
		shapes[pickedShape]->diffuse = glm::vec4(0, 1, 0, 1);
		shapes[pickedShape]->specular = glm::vec4(0.5, 0.3, 0.9, 1);
		setParent(i, i - 1);
	}
	pickedShape = linksNum - 1;
	addShape(0, 3, "./res/textures/skin3.jpg", -1,0);
	shapeTransformation(zScale, scaleFactor);

	shapeTransformation(zGlobalTranslate, 4.5);
	setParent(linksNum - 1, linksNum - 2);
	shapes[pickedShape]->ambient = glm::vec4(0.7, 0.7, 0.7, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.2, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0, 0, 1, 1);
	pickedShape = 0;

	pickedShape = 5;	//ik

	addShape(vertices, verticesSize, indices, indicesSize, "./res/textures/monkeyskin.jpg", -1,0);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 0.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 16.0);
	shapes[pickedShape]->ambient = glm::vec4(0.1, 0.2, 0.3, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.2, 0.6, 0.9, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;


	pickedShape = 6;	//block ik

	addShape(vertices, verticesSize, indices, indicesSize, "./res/textures/box0.bmp", -1,0);
	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 23.0f);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 16.0);
	shapes[pickedShape]->diffuse = glm::vec4(0, 0,1, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2,0.2, 0.3, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;

	pickedShape = 7;	//block ik2

	addShape(vertices, verticesSize, indices, indicesSize, "./res/textures/box0.bmp", -1,0);
	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -23.0f);
	shapeTransformation(yGlobalTranslate, 0.0f);
	shapeTransformation(zGlobalTranslate, 16.0f);
	shapes[pickedShape]->diffuse = glm::vec4(1, 1, 1, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.2, 0.3, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;

	pickedShape = 8;	//background

	addShape(vertices, verticesSize, indices, indicesSize, "./res/textures/justin-kauffman-449060-unsplash.jpg", -1,0);
	shapeTransformation(xScale, 160);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 100);
	shapeTransformation(xGlobalTranslate, 0.0);
	shapeTransformation(yGlobalTranslate, -10.0);
	shapeTransformation(zGlobalTranslate, 0.0);
	shapeTransformation(yGlobalRotate, 110.0f);
	shapes[pickedShape]->diffuse = glm::vec4(1, 1, 1, 1);
	shapes[pickedShape]->ambient = glm::vec4(1, 1, 1, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	pickedShape = 9;//background2
	addShape(vertices, verticesSize, indices, indicesSize, "./res/textures/rowan-heuvel-20511-unsplash.jpg", -1,0);
	shapeTransformation(xScale, 130);
	shapeTransformation(yScale, 100);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 0.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 80.0);
	shapes[pickedShape]->diffuse = glm::vec4(1, 1, 1, 1);
	shapes[pickedShape]->ambient = glm::vec4(1, 1, 1, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	
	pickedShape = 10;//wall
	addShape(vertices, verticesSize, indices, indicesSize, -1,0);
	shapeTransformation(xScale, 100);
	shapeTransformation(yScale, 50);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 0.0);
	shapeTransformation(yGlobalTranslate, 0.4f);
	shapeTransformation(zGlobalTranslate,150.0);
	shapes[pickedShape]->diffuse = glm::vec4(1, 1, 1, 1);
	shapes[pickedShape]->ambient = glm::vec4(1, 0.0f, 0.0f, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);

	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = true;
	pickedShape = 11;	//monky
	addShape("./res/objs/monkey3.obj", "./res/textures/fur.jpg",-1,0);
	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 15.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, -3.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->diffuse = glm::vec4(0.5, 0.8, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.2, 0.3, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);

	pickedShape = 12;	//monky
addShape("./res/objs/monkey3.obj","./res/textures/fur.jpg", -1, 300);
	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 15.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, -3.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.1, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.2, 0.3, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	pickedShape = 13;	//monky
	addShape(11, -1);
	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 30.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->diffuse = glm::vec4(0.7, 0.8, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(1, 0, 0, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);

	pickedShape = 14;	//monky
	addShape(12, -1);
	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 30.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.5, 0.4, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.3, 1);

	shapes[pickedShape]->ambient = glm::vec4(0.5, 1, 0.3, 1);


	pickedShape = 15;	//monky
	addShape(13, -1);
	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 10.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.2, 0.9, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.1, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.2, 1, 1);
	pickedShape = 16;	//monky
	addShape(14, -1);
	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 10.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->diffuse = glm::vec4(0, 0.8, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 1, 0, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.4, 1);


	pickedShape = 17;	//monky
	addShape(13, -1);
	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 15.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 25.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.8, 0, 1);
	shapes[pickedShape]->ambient = glm::vec4(1, 0.2, 1, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);

	pickedShape = 18;	//monky
	addShape(14, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 15.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 25.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->diffuse = glm::vec4(1, 0.8, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.9, 0.3, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.1, 1);


	pickedShape = 19;	//monky
	addShape(13, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -5.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 40.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.2, 1, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);


	pickedShape = 20;	//monky

		addShape(14, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -5.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 40.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.8, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0, 0.3, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);


	pickedShape = 21;	//monky
	addShape(13, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 45.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->ambient = glm::vec4(1, 0.2, 0.3, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.8, 0.7, 1);

	pickedShape = 22;	//monky
	addShape(14, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 45.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->diffuse = glm::vec4(0, 0.8, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0, 1, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);

	pickedShape = 23;	//monky
	addShape(13, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -17.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 50.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.1, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.5, 0.3, 1);

	pickedShape = 24;	//monky

		addShape(14, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -17.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 50.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0, 0.8, 0, 1);
	shapes[pickedShape]->ambient = glm::vec4(1, 0.2, 0.3, 1);
	pickedShape = 25;	//monky

		addShape(13, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 16.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 60.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.8, 0.7, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.5, 0.5, 1);
	pickedShape = 26;	//monky
addShape(14, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 16.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 60.0);
	shapes[pickedShape]->diffuse = glm::vec4(0, 0.8, 0.7, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.2, 0.3, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	pickedShape = 0;


	distPosition = getDistination(linksNum);
	tipPosition = getTipPosition(linksNum - 1);


}
void IK::menu(Vertex *vertices, unsigned int *indices, int verticesSize, int indicesSize, int id) {
	pickedShape = 41;
	std::string s;
	s.append("./res/textures/snake");
	s.append(std::to_string(id));
	s.append(".jpg");
	addShape(vertices, verticesSize, indices, indicesSize,s , -1, 0);
	shapeTransformation(xScale, 30);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 32);
	shapeTransformation(xGlobalTranslate, 0.0);
	shapeTransformation(yGlobalTranslate, -8.0);
	shapeTransformation(zGlobalTranslate, 0.0);
	shapeTransformation(zLocalRotate, 90.0f);
	shapeTransformation(yLocalRotate, -90.0f);
	shapes[pickedShape]->ambient = glm::vec4(1,1,1, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.8, 0.7, 1);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = false;

	pickedShape = 42;
	addShape("./res/objs/cavetorus.obj","./res/textures/sand.jpg", -1, 0);

	shapeTransformation(xScale, 5);
	shapeTransformation(yScale,5);
	shapeTransformation(zScale, 5);
	shapeTransformation(xGlobalTranslate, -2.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 16.0);
	shapeTransformation(yLocalRotate, 90.0f);

	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.1, 0, 1);
	shapes[pickedShape]->diffuse = glm::vec4(1, 1, 0, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.3, 0.3, 1);


}


void IK::hard() {
	pickedShape = 35;	

	addShape("./res/objs/cat.obj", -1, 0);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 0.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 20.0);
	shapeTransformation(xScale, 3);
	shapeTransformation(zScale, 3);

	shapeTransformation(yScale, 3);
	shapeTransformation(yGlobalRotate, -90.0f);
	shapeTransformation(xGlobalRotate, -90.0f);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.1, 0.2, 0.3, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.1,0.8, 0.7, 1);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;

	pickedShape = 36;	

	addShape("./res/objs/cat.obj", -1, 500);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 0.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 20.0);
	shapeTransformation(xScale, 3);
	shapeTransformation(zScale, 3);

	shapeTransformation(yScale, 3);
	shapeTransformation(yGlobalRotate, -90.0f);
	shapeTransformation(zGlobalRotate, -90.0f);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->ambient = glm::vec4(1.0, 0.2, 0.7, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.4, 0.5, 1);



	pickedShape = 37;
	addShape(35, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 30.0);
	shapeTransformation(xScale, 4);
	shapeTransformation(zScale, 4);
	shapeTransformation(yScale, 4);
	shapeTransformation(yGlobalRotate, -180.0f);
	shapeTransformation(xGlobalRotate, -90.0f);

	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.7, 0.3, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.1, 0.8, 0.7, 1);


	pickedShape = 38;	
	addShape(36, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 30.0);
	shapeTransformation(xScale, 4);
	shapeTransformation(zScale, 4);
	shapeTransformation(yScale, 4);

	shapeTransformation(yGlobalRotate, -180.0f);
	shapeTransformation(xGlobalRotate, -90.0f);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.2, 1, 0.3, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.8, 0, 1);


	pickedShape =39;
	addShape(35, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 0.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 50.0);
	shapeTransformation(xScale, 4);
	shapeTransformation(zScale, 4);
	shapeTransformation(yScale, 4);
	shapeTransformation(yGlobalRotate, -180.0f);
	shapeTransformation(xGlobalRotate, -90.0f);

	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->ambient = glm::vec4(1, 0.2, 0.7, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0, 0.8, 0, 1);

	
	pickedShape = 40;
	addShape(36, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 0.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 50.0);
	shapeTransformation(xScale, 4);
	shapeTransformation(zScale, 4);
	shapeTransformation(yScale, 4);
	shapeTransformation(yGlobalRotate, -180.0f);
	shapeTransformation(xGlobalRotate, -90.0f);

	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.1, 1, 0.3, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0, 0, 1);


}




void IK::medium()
	{
		
pickedShape = 27;	//monky
addShape("./res/objs/Rock.obj", "./res/textures/rock1.jpg",-1,0);

					shapeTransformation(xScale, 1);
					shapeTransformation(yScale, 1);
					shapeTransformation(zScale, 1);
					shapeTransformation(xGlobalTranslate, 10.0);
					shapeTransformation(yGlobalTranslate, 0.0);
					shapeTransformation(zGlobalTranslate, 10.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->ambient = glm::vec4(1, 0, 0, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0, 0.4f, 0.5f, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);


	pickedShape = 28;	//monky
	addShape("./res/objs/Rock.obj", "./res/textures/rock1.jpg", -1, 300);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 10.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->ambient = glm::vec4(1, 1,0, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.8f, 0.4f, 0.5f, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	
	
	pickedShape = 29;	//monky
	addShape(27, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 40.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->ambient = glm::vec4(1, 1, 0, 1);
	shapes[pickedShape]->diffuse = glm::vec4(1, 0.5, 0.7, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);


	pickedShape = 30;	//monky
	addShape(28, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 40.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);
	shapes[pickedShape]->ambient = glm::vec4(0.1, 0.9, 0.3, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0, 0.7, 1);

	pickedShape = 31;	//monky
	addShape(27, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 50.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->ambient = glm::vec4(0.1, 0.2, 0.9, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.5, 0.7, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);


	pickedShape = 32;	//monky
	addShape(28, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, 10.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 50.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->ambient = glm::vec4(0.1, 1, 1, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0, 1, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.5, 1);

	pickedShape = 33;	//monky
	addShape(27, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate,-5.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 70.0);
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->ambient = glm::vec4(0.502, 0.251, 0, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.5, 0.7, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.2, 0.9, 1);

	pickedShape = 34;	//monky
	addShape(28, -1);

	shapeTransformation(xScale, 1);
	shapeTransformation(yScale, 1);
	shapeTransformation(zScale, 1);
	shapeTransformation(xGlobalTranslate, -5.0);
	shapeTransformation(yGlobalTranslate, 0.0);
	shapeTransformation(zGlobalTranslate, 70.0);
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->ambient = glm::vec4(0.502, 0.251,0, 1);
	shapes[pickedShape]->diffuse = glm::vec4(0.9, 0.5, 0.7, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.7, 0.9, 1);

}

void IK::addShape(int CylParts, int linkPosition, int parent, int maxfaces)
{

	__super::addShape(CylParts, linkPosition, parent);
}

void IK::addShape(int CylParts, int linkPosition, const std::string& fileName, int parent, int maxfaces)
{
	__super::addShape(CylParts, linkPosition, fileName, parent);
}

void IK::addShape(int type, int parent)
{

	__super::addShape(type, parent);
}

void IK::addShape(const std::string& fileName, int parent, int maxfaces)
{
	__super::addShape(fileName, parent, maxfaces);
}

void IK::addShape(const std::string& fileName, const std::string& textureFileName, int parent, int maxfaces)
{

	__super::addShape(fileName, textureFileName, parent, maxfaces);
}

void IK::addShape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, int parent, int maxfaces)
{

	__super::addShape(vertices, numVertices, indices, numIndices, parent);
}

void IK::addShape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const std::string &textureFlieName, int parent, int maxfaces)
{

	__super::addShape(vertices, numVertices, indices, numIndices, textureFlieName, parent);
}

glm::vec3 IK::getPrevAxis(int index, int axis) {
	mat4 prevAxisMat = mat4(1);

	for (int j = 0; j < index; j++) {
		prevAxisMat *= GetShapeTrans(j);
	}
	
	switch (axis) {
	case zAxis1:
		return normalize(vec3(prevAxisMat[2]));
		break;
	case xAxis1:
		return  normalize(vec3(prevAxisMat[0]));
		break;
	}
}

// Pre: prevPos holds the old positions for the joints
//      newPos holds the new positions for the joints
void IK::calculateStep(std::vector<glm::vec3> zAlignedPos, std::vector<glm::vec3> prevPos, std::vector<glm::vec3> newPos/*bool EulerVersion*/)
{
	glm::vec3 v, vp;
	float xAngle, xCos;
	// forward
	for (int i = 0; i < newPos.size() - 1; i++) 
	{
		v =newPos.at(i) - newPos.at(i + 1);
		vp =newPos.at(i) - prevPos.at(i + 1);
		if(v!=vec3(0,0,0))
		{
				v = glm::normalize(v);

		}
		if (vp != vec3(0, 0, 0))
		{
			vp = glm::normalize(vp);
		}
	glm::vec3 xHat = glm::cross(v, vp);
		
		if (xHat != vec3(0, 0, 0))
		{
			xHat = glm::normalize(xHat);
		}
		else
		{
			xHat = vec3(1,0,0);
		}
		xCos = glm::clamp(glm::dot(v, vp), -1.0f, 1.0f);
		xAngle = -glm::acos(xCos);
	
		shapeRotation(xHat, xAngle, i);
	}
}

void IK::makeChange()
{
	// before making any steps we need to set the
	// inital values to make the transition from
	vector<glm::vec3> beforePos;					// holds the previous joints positions
	vector<glm::vec3> afterPos;						// holds the new joints positions
	vector<glm::vec3> zAxisPos;						// holds the zAxis alined joint positions

	glm::vec3 target = getDistination(5);	// holds the target position
	float ri, lambda_i;								// ri- for distance from the link to the target

	if (glm::abs(distToTarget(linksNum - 1)) > delta) {
		for (int i = 0; i < linksNum; i++) {
			zAxisPos.push_back(glm::vec3(0, 0, 1) * (float)i * (float)scaleFactor);
			beforePos.push_back(getDistination(i));
		}
		zAxisPos.push_back(glm::vec3(0, 0, 1) * (float)linksNum * (float)scaleFactor);
		beforePos.push_back(getTipPosition(linksNum - 1)); // getting the last joint position


		// the target is unreachable
		// NOTE: -1 returns distance from (0,0,0) to the box
		afterPos.push_back(beforePos.at(0));		// first set the anchor joint stable
		for (int i = 0; i <= linksNum - 1; i++) {
			ri = distToTarget(i - 1);
			if (ri != 0)
				lambda_i = scaleFactor / ri;
			else
				lambda_i = 0;
			// find the new joint position
			afterPos.push_back((1 - lambda_i)*afterPos.at(i) + lambda_i * target);

		}

		calculateStep(zAxisPos, beforePos, afterPos);


	}
	if (glm::abs(distToTarget(linksNum - 1)) <= delta) {
		std::cout << "Target reached, IK mode OFF" << std::endl;
		std::cout << "Distance to taget is: " << distToTarget(linksNum - 1) << std::endl;
		dActivate();
	}

}

float IK::distToTarget(int linkInd) {
	float dist;
	glm::vec3 linkTip;
	if (linkInd >= 0)
		linkTip = getTipPosition(linkInd);
	else
		linkTip = glm::vec3(0, 0, 0);
	glm::vec3 cubeCenter = getDistination(linksNum);
		dist = glm::distance(linkTip, cubeCenter);

	return dist;
}

float IK::Distance(int indx1, int indx2) {
	glm::vec3 first = getTipPosition(indx1);
	glm::vec3 second = getTipPosition(indx2);
	float dist = glm::distance(first, second);

	return dist;
}

void IK::show_easy(bool reset)
{
	for (int i = 0; i < linksNum; i++)
	{
		setParent(i, -1);
	}
	pickedShape = 0;
	shapes[pickedShape]->reset();
	shapeTransformation(zGlobalTranslate, -5.0f);

	for (int i = 1; i < linksNum - 1; i++)
	{
		pickedShape = i;
		if (reset) {
		shapes[pickedShape]->reset();
	
			shapeTransformation(zGlobalTranslate, 3.0);
			setParent(i, i - 1);
		}
	}
	pickedShape = linksNum - 1;
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(zGlobalTranslate, 4.5);
		setParent(linksNum - 1, linksNum - 2);

	}
	

	pickedShape = 0;

	pickedShape = 5;	//ik

	if (reset) {
		shapes[pickedShape]->reset();

		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 0.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 16.0);
	}

	pickedShape = 6;	//block ik
	if (reset) {
		shapes[pickedShape]->reset();

		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 23.0f);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 16.0);

	}
	pickedShape = 7;	//block ik2

	if (reset) {
		shapes[pickedShape]->reset();

		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -23.0f);
		shapeTransformation(yGlobalTranslate, 0.0f);
		shapeTransformation(zGlobalTranslate, 16.0f);
	}
	pickedShape = 8;	//background

	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 160);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 100);
		shapeTransformation(xGlobalTranslate, 0.0);
		shapeTransformation(yGlobalTranslate, -10.0);
		shapeTransformation(zGlobalTranslate, 0.0);
		shapeTransformation(yGlobalRotate, 110.0f);

	}
	pickedShape = 9;//background2
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 130);
		shapeTransformation(yScale, 100);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 0.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 90.0);
	}
	pickedShape = 10;//wall
	
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 100);
		shapeTransformation(yScale, 50);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 0.0);
		shapeTransformation(yGlobalTranslate, 0.4f);
		shapeTransformation(zGlobalTranslate, 150.0);
	}
	pickedShape = 11;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 15.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, -3.0);
	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;


	pickedShape = 12;	//monky

	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 15.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, -3.0);
	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;

	pickedShape = 13;	//monky

		if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 30.0);
	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;


	pickedShape = 14;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 30.0);
	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;




	pickedShape = 15;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 10.0);
	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;


	pickedShape = 16;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 10.0);
	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;



	pickedShape = 17;	//monky
if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 15.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 25.0);
	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;



	pickedShape = 18;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 15.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 25.0);
	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;



	pickedShape = 19;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -5.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 40.0);
	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;



	pickedShape = 20;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -5.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 40.0);
	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;




	pickedShape = 21;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 45.0);
	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;



	pickedShape = 22;	//monky

	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 45.0);
	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;

	pickedShape = 23;	//monky

		if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -17.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 50.0);
	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;



	pickedShape = 24;	//monky

		if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -17.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 50.0);
	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;


	pickedShape = 25;	//monky

		if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 16.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 60.0);
	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;

	pickedShape = 26;	//monky

		if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 16.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 60.0);
	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	pickedShape = 0;

	distPosition = getDistination(linksNum);
	tipPosition = getTipPosition(linksNum - 1);


}
void IK::show_medium(bool reset)
{

	pickedShape = 27;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 10.0);
	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;



	pickedShape = 28;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 10.0);
	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;



	pickedShape = 29;	//monky
	if (reset) {

		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 40.0);
		}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;



	pickedShape = 30;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 40.0);
	}shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;



	pickedShape = 31;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 50.0);
		}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;



	pickedShape = 32;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 50.0);
		}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;

	pickedShape = 33;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -5.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 70.0);
			}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;

	pickedShape = 34;	//monky
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, -5.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 70.0);
			}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;

}
void IK::showcave(bool reset)
{

	pickedShape = 42;
	if (reset) {
		shapes[pickedShape]->reset();

		shapeTransformation(xScale, 5);
		shapeTransformation(yScale, 5);
		shapeTransformation(zScale, 5);
		shapeTransformation(xGlobalTranslate, -2.0);
		shapeTransformation(yGlobalTranslate, 0.0f);
		shapeTransformation(zGlobalTranslate, 16.0);
		shapeTransformation(yLocalRotate, 90.0f);
		shapeTransformation(yScale, 1);
	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->ambient = glm::vec4(0.2, 0.1, 0, 1);
	shapes[pickedShape]->diffuse = glm::vec4(1, 1, 0, 1);
	shapes[pickedShape]->specular = glm::vec4(0.3, 0.3, 0.3, 1);


}
void IK::show_hard(bool reset)
{
	pickedShape = 35;
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 0.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 20.0);
		shapeTransformation(xScale, 3);
		shapeTransformation(zScale, 3);
		shapeTransformation(yScale, 3);
		shapeTransformation(yLocalRotate, 90.0f);
		shapes[pickedShape]->speed = glm::vec3(0.05, 0, 0);

	}
	shapes[pickedShape]->minx = 23;
	shapes[pickedShape]->maxx = -23;
		shapes[pickedShape]->toDraw = true;
		shapes[pickedShape]->collide = false;
	
	pickedShape = 36;
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 0.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 20.0);
		shapeTransformation(xScale, 3);
		shapeTransformation(zScale, 3);
		shapeTransformation(yScale, 3);
		shapeTransformation(yLocalRotate, 90.0f);
		shapes[pickedShape]->speed = glm::vec3(0.05, 0, 0);
	}
	shapes[pickedShape]->minx = 23;
	shapes[pickedShape]->maxx = -23;

	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;

	pickedShape = 37;
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 30.0);
		shapeTransformation(xScale, 4);
		shapeTransformation(zScale, 4);
		shapeTransformation(yScale, 4);
		shapeTransformation(yLocalRotate, 90.0f);
		shapes[pickedShape]->speed = glm::vec3(0.05, 0, 0);

	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->minx = 10;
	shapes[pickedShape]->maxx = 23;

	pickedShape = 38;
	//addShape(36, -1);
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 10.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 30.0);
		shapeTransformation(xScale, 4);
		shapeTransformation(zScale, 4);
		shapeTransformation(yScale, 4);
		shapeTransformation(yLocalRotate, 90.0f);
		shapes[pickedShape]->speed = glm::vec3(0.05, 0, 0);
		shapes[pickedShape]->minx = 10;
		shapes[pickedShape]->maxx = 23;

	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;


	pickedShape = 39;
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 0.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 50.0);
		shapeTransformation(xScale, 4);
		shapeTransformation(zScale, 4);
		shapeTransformation(yScale, 4);
		shapeTransformation(yLocalRotate, 90.0f);
		shapes[pickedShape]->speed = glm::vec3(0.05, 0, 0);

	}
	shapes[pickedShape]->toDraw = true;
	shapes[pickedShape]->collide = false;
	shapes[pickedShape]->minx = 0;
	shapes[pickedShape]->maxx = 10;


	pickedShape = 40;
	if (reset) {
		shapes[pickedShape]->reset();
		shapeTransformation(xScale, 1);
		shapeTransformation(yScale, 1);
		shapeTransformation(zScale, 1);
		shapeTransformation(xGlobalTranslate, 0.0);
		shapeTransformation(yGlobalTranslate, 0.0);
		shapeTransformation(zGlobalTranslate, 50.0);
		shapeTransformation(xScale, 4);
		shapeTransformation(zScale, 4);
		shapeTransformation(yScale, 4);
		shapeTransformation(yLocalRotate, 90.0f);
		shapes[pickedShape]->speed = glm::vec3(0.05, 0, 0);

	}
	shapes[pickedShape]->toDraw = false;
	shapes[pickedShape]->collide = true;
	shapes[pickedShape]->minx = 0;
	shapes[pickedShape]->maxx = 10;



}

void IK::hide_medium()
{
	shapes[27]->toDraw = false;
	shapes[27]->collide = false;

	shapes[28]->toDraw = false;
	shapes[28]->collide = false;

	shapes[29]->toDraw = false;
	shapes[29]->collide = false;

	shapes[30]->toDraw = false;
	shapes[30]->collide = false;

	shapes[31]->toDraw = false;
	shapes[31]->collide = false;

	shapes[32]->toDraw = false;
	shapes[32]->collide = false;

	shapes[33]->toDraw = false;
	shapes[33]->collide = false;

	shapes[34]->toDraw = false;
	shapes[34]->collide = false;


}
void IK::hide_hard()
{
	shapes[35]->toDraw = false;
	shapes[35]->collide = false;

	shapes[36]->toDraw = false;
	shapes[36]->collide = false;

	shapes[37]->toDraw = false;
	shapes[37]->collide = false;

	shapes[38]->toDraw = false;
	shapes[38]->collide = false;

	shapes[39]->toDraw = false;
	shapes[39]->collide = false;

	shapes[40]->toDraw = false;
	shapes[40]->collide = false;


}