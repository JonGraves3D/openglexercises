// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>
#include <stdio.h>
//Please implement the following functions:



float degrees_debug;

mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE

	float radians = degrees * pi / 180.0f;

	glm:mat3 m1 = mat3(
		axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
		axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
		axis.x*axis.z, axis.y*axis.z, axis.z*axis.z
		);
	
	m1 = glm::transpose(m1);

	mat3 m2 = mat3(
		0, -axis.z, axis.y, 
		axis.z, 0, -axis.x, 
		-axis.y, axis.x, 0);

	m2 = glm::transpose(m2);


	mat3 rotation = cos(radians) * mat3(1.0f) + (1 - cos(radians)) * m1 + sin(radians) * m2;

  // You will change this return call
  return rotation;
}


vec3 cross(vec3 v1, vec3 v2)
{

	float a = v1.y * v2.z - v1.z * v2.y;
	float b = v1.z * v2.x - v1.x * v2.z;
	float c = v1.x * v2.y - v1.y * v2.x;

	vec3 crossproduct = vec3(a, b, c);

	return crossproduct;
}

vec3 normalize(vec3 vector)
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
	//up = normalize(up);
	eye = Transform::rotate(degrees, up) * eye;

	//printf("Coordinates: %.2f, %.2f, %.2f, distance: %.2f \n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {

	vec3 axis = cross(eye, up);
	axis = normalize(axis);
	up = Transform::rotate(degrees, axis) * up;
	eye = Transform::rotate(degrees, axis) * eye;


	degrees_debug += degrees;

	printf(" %.2f", degrees_debug);
	printf("Distance: %.7f \n", sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {

	vec3 w = normalize(eye);
	up = normalize(up);
	vec3 u = cross(up, w);
	vec3 v = normalize(cross(w,u));

	mat4 rotation = mat4(
		u.x, v.x, w.x, 0, 
		u.y, v.y, w.y, 0, 
		u.z, v.z, w.z, 0,
		0, 0, 0, 1);


	mat4 translation = mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-eye.x, -eye.y, -eye.z, 1
		);

	mat4 transformation = rotation * translation;


	return transformation;

}
Transform::Transform()
{

}

Transform::~Transform()
{

}

//helper functions


