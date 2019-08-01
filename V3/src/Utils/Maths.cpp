#include "pch.h"
#include "Maths.h"
#include <sstream>
std::string Maths::Vec3ToString(glm::vec3& v)
{

	std::stringstream s;
	s << v.x;
	s << " ";
	s << v.y;
	s << " ";
	s << v.z;
	s << "\n";
	return s.str();
}

std::string Maths::Vec2ToString(glm::vec2& v)
{

	std::stringstream s;
	s << v.x;
	s << " ";
	s << v.y;
	s << "\n";

	return s.str();

}

glm::mat3 Maths::aiMatrix3x3ToGlm(const aiMatrix3x3 &from)
{
	glm::mat3 to;
	//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
	to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3;
	to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3;
	to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3;
	return to;
}

glm::mat4 Maths::aiMatrix4x4ToGlm(const aiMatrix4x4 &from)
{
	glm::mat4 to;
	//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
	to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
	to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
	to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
	to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
	return to;
}

glm::vec3 Maths::aiVector3ToGlm(const aiVector3D &from)
{
	glm::vec3 r;
	r.x = from.x;
	r.y = from.y;
	r.z = from.z;
	return r;
}

glm::quat Maths::aiQuaternionToGlm(const aiQuaternion &from)
{
	glm::quat r;
	r.x = from.x;
	r.y = from.y;
	r.z = from.z;
	r.w = from.w;
	return r;

}

glm::quat Maths::nlerp(glm::quat q1, glm::quat q2, float blend)
{
	//cout << a.w + a.x + a.y + a.z << endl;
	glm::quat a = glm::normalize(q1);
	glm::quat b = glm::normalize(q2);

	glm::quat result;
	float dot_product = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	float one_minus_blend = 1.0f - blend;

	if (dot_product < 0.0f)
	{
		result.x = a.x * one_minus_blend + blend * -b.x;
		result.y = a.y * one_minus_blend + blend * -b.y;
		result.z = a.z * one_minus_blend + blend * -b.z;
		result.w = a.w * one_minus_blend + blend * -b.w;
	}
	else
	{
		result.x = a.x * one_minus_blend + blend * b.x;
		result.y = a.y * one_minus_blend + blend * b.y;
		result.z = a.z * one_minus_blend + blend * b.z;
		result.w = a.w * one_minus_blend + blend * b.w;
	}

	return glm::normalize(result);
}
/*
glm::vec3 Maths::QuatToEuler(const glm::quat& q)
{
	glm::vec3 r;

	// roll (x-axis rotation)
	double sinr_cosp = +2.0 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
	r.z = atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = +2.0 * (q.w * q.y - q.z * q.x);
	if (fabs(sinp) >= 1)
		r.x = copysign(glm::pi<double>() / 2, sinp); // use 90 degrees if out of range
	else
		r.x = asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = +2.0 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
	r.y = atan2(siny_cosp, cosy_cosp);

	return r;
}*/
/*
ImVec2 Maths::vec2ToImVec2(const glm::vec2& v)
{
	return ImVec2(v.x, v.y);
}

ImVec4 Maths::vec4ToImVec4(const glm::vec4& v)
{
	return ImVec4(v.x, v.y, v.z, v.w);
}*/


