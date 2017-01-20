// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>
#include <stdio.h>
//Please implement the following functions:

mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE

	glm:mat3 m1 = glm::mat3(
		axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
		axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
		axis.x*axis.y, axis.y*axis.z, axis.z*axis.z
		);
	
	m1 = glm::transpose(m1);

	glm::mat3 m2 = glm::mat3(0, -axis.z, axis.y, axis.z, 0, -axis.x, -axis.y, axis.x, 0);

	m2 = glm::transpose(m2);

	glm::mat3 rotation = cos(degrees * pi / 180.0f) * glm::mat3(1.0f) + (1 - cos(degrees * pi / 180.0f)) * m1 + sin(degrees * pi / 180.0f) * m2;

  // You will change this return call
  return rotation;
}


glm::vec3 cross(glm::vec3 v1, glm::vec3 v2)
{

	float a = v1.y * v2.z - v2.z * v1.y;
	float b = v1.z * v2.x - v2.x * v1.z;
	float c = v1.x * v2.y - v2.y * v1.x;

	printf("a:%.2f  \n", a);
	printf("b:%.2f  \n", b);
	printf("c:%.2f  \n", c);

	glm::vec3 crossproduct = glm::vec3(a, b, c);

	return crossproduct;
}

glm::vec3 normalize(glm::vec3 vector)
{
	float w = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

	vector.x = vector.x / w;
	vector.y = vector.y / w;
	vector.z = vector.z / w;

	return vector;
}


// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	eye = Transform::rotate(degrees, up) * eye;

	printf("Coordinates: %.2f, %.2f, %.2f, distance: %.2f \n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {

	glm::vec3 axis = cross(eye, up);
	axis = normalize(axis);
	up = Transform::rotate(degrees, axis) * up;
	eye = Transform::rotate(degrees, axis) * eye;

	printf("Coordinates: %.2f, %.2f, %.2f, distance: %.2f \n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE

  // You will change this return call
  return mat4();
}

Transform::Transform()
{

}

Transform::~Transform()
{

}

//helper functions


