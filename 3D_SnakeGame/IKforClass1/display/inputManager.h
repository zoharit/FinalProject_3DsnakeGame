#pragma once 
#include "GLFW\glfw3.h"
#include "../IK/IK.h"
#include "display.h"




const int DISPLAY_WIDTH = 1200;
const int DISPLAY_HEIGHT = 800;
const float FAR = 100.0f;
const float NEAR = 1.0f;
const float CAM_ANGLE = 60.0f;
float relation = (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT;
const int boxInd = linksNum; 
const int tipInd = linksNum - 1;
const int scnInd = -1; 

Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

IK scn(glm::vec3(0.0f, 5.0f, -30.0f), CAM_ANGLE, relation, NEAR, FAR);

float factor = 1.0;

double x1 = 0, x2 = 0;
double ys1 = 0, y2 = 0;
float depth;








void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_P:
			if (scn.get_pickedShape() != boxInd && scn.get_pickedShape() != scnInd) {
				scn.setPicked(scn.get_pickedShape() - 1);
				if (scn.get_pickedShape() == -1) {
					scn.setPicked(tipInd);
				}
			}
			else {
				std::cout << "you in BoxMode or CameraMode, cannot execute command!" << std::endl;
			}
			break;
		case GLFW_KEY_B:
			if (scn.get_pickedShape() != boxInd)
				scn.setPicked(boxInd);
			else
				scn.setPicked(0);
			break;
		case GLFW_KEY_N:
			if (scn.get_pickedShape() != boxInd && scn.get_pickedShape() != scnInd) {
				scn.setPicked(scn.get_pickedShape() + 1);
				if (scn.get_pickedShape() == linksNum) {
					scn.setPicked(0);
				}
			}
			else
				std::cout << "camera mode" << std::endl;
			break;

		case GLFW_KEY_C:
			scn.changeMode();
			if (scn.getMode()) {
				scn.setPicked(-1);
			}
			else {
				scn.setPicked(0);
			}
			break;

		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_RIGHT:
			if (scn.find_collision(5, 7) == false)
			{
				glm::vec4 trans;
				scn.shapes.at(5)->getTraslate(trans);
				if (trans.x > -23)
				{
				
					scn.shapes[5]->translateInSystem(*scn.shapes[5], glm::vec3(-1, 0, 0), 0, false);
					scn.cameras[1]->MoveRight(-1);
				}
				
			}
			break;
		case GLFW_KEY_UP:
				{
			glm::vec4 trans;
			scn.shapes.at(5)->getTraslate(trans);
			if (trans.y <8)
			{
				scn.shapes[5]->translateInSystem(*scn.shapes[5], glm::vec3(0, 0.5f, 0), 0, false);
				scn.cameras[1]->MoveUp(0.25);

			}break;
				}
		case GLFW_KEY_DOWN:
		{
			glm::vec4 trans;
			scn.shapes.at(5)->getTraslate(trans);
			if (trans.y > -7)
			{
				scn.shapes[5]->translateInSystem(*scn.shapes[5], glm::vec3(0, -0.5, 0), 0, false);
				scn.cameras[1]->MoveUp(-0.25);
			}
			break;
		}

		case GLFW_KEY_LEFT:
			if (scn.find_collision(5, 6) == false)
			{
				glm::vec4 trans;
				scn.shapes.at(5)->getTraslate(trans);
				if (trans.x <23)
				{

					scn.shapes[5]->translateInSystem(*scn.shapes[5], glm::vec3(1, 0, 0), 1, false);
					scn.cameras[1]->MoveRight(1);
				}
				}
			break;

		case GLFW_KEY_D:
			break;
		case GLFW_KEY_SPACE:

		{
			scn.camera_index = scn.camera_index ^ 1;
		}

			break;
		case GLFW_KEY_W:
			scn.myTranslate(glm::vec3(0, 0, -1), 1);
			break;
		default:
			break;
		}
	}
}



void window_size_callback(GLFWwindow* window, int width, int height)
{

	scn.resize(width, height, NEAR, FAR);
	relation = (float)width / (float)height;
}