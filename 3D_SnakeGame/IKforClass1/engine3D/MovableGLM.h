#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "EulerAngles.h"

class MovableGLM : public EulerAngles
{
private:
	glm::mat4 translateMat[2];
	glm::mat4 rotateMat;
	
	
	//vec3 findAxis2(vec3 vec, int indx);

	glm::vec3 scaleFactor;
	glm::vec3 findAxis(glm::vec3 vec) const;

	//glm::vec3 getTipPos(glm::mat4 &prevTransformations);
	//glm::vec3 getRootPos(glm::mat4 &prevTransformations);
	
	//glm::vec3 getXdirection(glm::mat4 &prevTransformations);
	//glm::vec3 getZdirection(glm::mat4 &prevTransformations);
public:
	void MovableGLM::reset();
	//vec3 findAxis(vec4 &vec, int indx);
	//vec3 findAxis2(vec4 &vec, int indx);
	MovableGLM();
	
	glm::mat4 makeTransScale(glm::mat4 &prevTransformations) const;
	glm::mat4 makeTransScale() const;
	glm::mat4 makeTrans(glm::mat4 &prevTransformations) const;
	glm::mat4 makeTrans() const;
	void myRotate(float ang, glm::vec3 &vec, int indx);
	void myTranslate(glm::vec3 &vec, int indx);
	void myScale(glm::vec3 &vec);
	void globalSystemRot(float ang, glm::vec3 &vec, int indx);
	void changeCenterOfRotation(glm::vec3 &Pvec);
	void zeroTrans();
	void getTraslate(glm::vec4 &vec);
	void copyTranslations(MovableGLM *mGLM);
	void translateInSystem(const MovableGLM  &system,glm::vec3 &vec, int indx, bool toScale);
	void MovableGLM::rot(int axis, float sin, float cos);
	void set_rotate_mat(glm::mat4 rotateMat);

	glm::vec3 getPointInSystem(glm::mat4 &prevTransformations,glm::vec3 point);
	glm::vec3 getVectorInSystem(glm::mat4 &prevTransformations,glm::vec3 vec);
	glm::vec3 getCenterOfRotation(glm::mat4 &prevTransformations);
	
	//float getTraslateZ() { return makeTrans()[3][2]; }
	//inline void rotateVec4(vec4 &vec) { vec = rotateMat[0] *vec; }
};