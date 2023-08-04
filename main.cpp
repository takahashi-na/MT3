#define _USE_MATH_DEFINES
#include <Novice.h>
#include <cmath>
#include <assert.h>
#include "DirectXCommon.h"

const char kWindowTitle[] = "GC2C_08_タカハシシンイチ_MT3_01_01";

struct Vector2 {
	float x, y;
};

struct Vector3 {
	float x, y, z;
};

struct Vector4 { 
	float x, y, z, w;
};

struct Matrix3x3 {
	float m[3][3];
};

struct Matrix4x4 {
	float m[4][4];
};

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
float kWindowWidth = 1200;
float kWindowHeight = 720;

Vector3 Cross(const Vector3& v1, const Vector3& v2)

{
	return{ v1.y * v2.z - v1.z * v2.y,v1.z * v2.x - v1.x * v2.z,v1.x * v2.y - v1.y * v2.x };
}

// 代入演算子
Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			for (size_t k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k]*m2.m[k][j];
			}
		}
	}
	m1 = result;
	return m1;
}

// 二項演算子
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result = m1;

	return result *= m2;
}

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	// 1列目
	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	// 2列目
	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	// 3列目
	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	// 4列目
	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return result;
}

////  逆行列
//Matrix4x4 Inverse(const Matrix4x4& m)
//{
//	float determinantRecp=0.0f;
//	Matrix4x4 resultInverse;
//	float determinant = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
//		m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
//		m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -
//
//		m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
//		m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
//		m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -
//
//		m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
//		m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
//		m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +
//
//		m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
//		m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
//		m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +
//
//		m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
//		m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
//		m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -
//
//		m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
//		m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
//		m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -
//
//		m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
//		m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
//		m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +
//
//		m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
//		m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
//		m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];
//
//
//	assert(determinant != 0.0f);
//	determinantRecp = 1.0f / determinant;
//
//	//1行目
//	resultInverse.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] +
//		m.m[1][2] * m.m[2][3] * m.m[3][1] +
//		m.m[1][3] * m.m[2][1] * m.m[3][2] -
//		m.m[1][3] * m.m[2][2] * m.m[3][1] -
//		m.m[1][2] * m.m[2][1] * m.m[3][3] -
//		m.m[1][1] * m.m[2][3] * m.m[3][2]) * determinantRecp;
//
//	resultInverse.m[0][1] = -(m.m[0][1] * m.m[2][2] * m.m[3][3] +
//		m.m[0][2] * m.m[2][3] * m.m[3][1] +
//		m.m[0][3] * m.m[2][1] * m.m[3][2] -
//		m.m[0][3] * m.m[2][2] * m.m[3][1] -
//		m.m[0][2] * m.m[2][1] * m.m[3][3] -
//		m.m[0][1] * m.m[2][3] * m.m[3][2]) * determinantRecp;
//
//	resultInverse.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] +
//		m.m[0][2] * m.m[1][3] * m.m[3][1] +
//		m.m[0][3] * m.m[1][1] * m.m[3][2] -
//		m.m[0][3] * m.m[1][2] * m.m[3][1] -
//		m.m[0][2] * m.m[1][1] * m.m[3][3] -
//		m.m[0][1] * m.m[1][3] * m.m[3][2]) * determinantRecp;
//
//	resultInverse.m[0][3] = -(m.m[0][1] * m.m[1][2] * m.m[2][3] +
//		m.m[0][2] * m.m[1][3] * m.m[2][1] +
//		m.m[0][3] * m.m[1][1] * m.m[2][2] -
//		m.m[0][3] * m.m[1][2] * m.m[2][1] -
//		m.m[0][2] * m.m[1][1] * m.m[2][3] -
//		m.m[0][1] * m.m[1][3] * m.m[2][2]) * determinantRecp;
//
//	//2行目
//	resultInverse.m[1][0] = -(m.m[1][0] * m.m[2][2] * m.m[3][3] +
//		m.m[1][2] * m.m[2][3] * m.m[3][0] +
//		m.m[1][3] * m.m[2][0] * m.m[3][2] -
//		m.m[1][3] * m.m[2][2] * m.m[3][0] -
//		m.m[1][2] * m.m[2][0] * m.m[3][3] -
//		m.m[1][0] * m.m[2][3] * m.m[3][2]) * determinantRecp;
//
//	resultInverse.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] +
//		m.m[0][2] * m.m[2][3] * m.m[3][0] +
//		m.m[0][3] * m.m[2][0] * m.m[3][2] -
//		m.m[0][3] * m.m[2][2] * m.m[3][0] -
//		m.m[0][2] * m.m[2][0] * m.m[3][3] -
//		m.m[0][0] * m.m[2][3] * m.m[3][2]) * determinantRecp;
//
//	resultInverse.m[1][2] = -(m.m[0][0] * m.m[1][2] * m.m[3][3] +
//		m.m[0][2] * m.m[1][3] * m.m[3][0] +
//		m.m[0][3] * m.m[1][0] * m.m[3][2] -
//		m.m[0][3] * m.m[1][2] * m.m[3][0] -
//		m.m[0][2] * m.m[1][0] * m.m[3][3] -
//		m.m[0][0] * m.m[1][3] * m.m[3][2]) * determinantRecp;
//
//	resultInverse.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] +
//		m.m[0][2] * m.m[1][3] * m.m[2][0] +
//		m.m[0][3] * m.m[1][0] * m.m[2][2] -
//		m.m[0][3] * m.m[1][2] * m.m[2][0] -
//		m.m[0][2] * m.m[1][0] * m.m[2][3] -
//		m.m[0][0] * m.m[1][3] * m.m[2][2]) * determinantRecp;
//
//	//3行目
//	resultInverse.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] +
//		m.m[1][1] * m.m[2][3] * m.m[3][0] +
//		m.m[1][3] * m.m[2][0] * m.m[3][1] -
//		m.m[1][3] * m.m[2][1] * m.m[3][0] -
//		m.m[1][1] * m.m[2][0] * m.m[3][3] -
//		m.m[1][0] * m.m[2][3] * m.m[3][1]) * determinantRecp;
//
//	resultInverse.m[2][1] = -(m.m[0][0] * m.m[2][1] * m.m[3][3] +
//		m.m[0][1] * m.m[2][3] * m.m[3][0] +
//		m.m[0][3] * m.m[2][0] * m.m[3][1] -
//		m.m[0][3] * m.m[2][1] * m.m[3][0] -
//		m.m[0][1] * m.m[2][0] * m.m[3][3] -
//		m.m[0][0] * m.m[2][3] * m.m[3][1]) * determinantRecp;
//
//	resultInverse.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] +
//		m.m[0][1] * m.m[1][3] * m.m[3][0] +
//		m.m[0][3] * m.m[1][0] * m.m[3][1] -
//		m.m[0][3] * m.m[1][1] * m.m[3][0] -
//		m.m[0][1] * m.m[1][0] * m.m[3][3] -
//		m.m[0][0] * m.m[1][3] * m.m[3][1]) * determinantRecp;
//
//	resultInverse.m[2][3] = -(m.m[0][0] * m.m[1][1] * m.m[2][3] +
//		m.m[0][1] * m.m[1][3] * m.m[2][0] +
//		m.m[0][3] * m.m[1][0] * m.m[2][1] -
//		m.m[0][3] * m.m[1][1] * m.m[2][0] -
//		m.m[0][1] * m.m[1][0] * m.m[2][3] -
//		m.m[0][0] * m.m[1][3] * m.m[2][1]) * determinantRecp;
//
//	//4行目
//	resultInverse.m[3][0] = -(m.m[1][0] * m.m[2][1] * m.m[3][2] +
//		m.m[1][1] * m.m[2][2] * m.m[3][0] +
//		m.m[1][2] * m.m[2][0] * m.m[3][1] -
//		m.m[1][2] * m.m[2][1] * m.m[3][0] -
//		m.m[1][1] * m.m[2][0] * m.m[3][2] -
//		m.m[1][0] * m.m[2][2] * m.m[3][1]) * determinantRecp;
//
//	resultInverse.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] +
//		m.m[0][1] * m.m[2][2] * m.m[3][0] +
//		m.m[0][2] * m.m[2][0] * m.m[3][1] -
//		m.m[0][2] * m.m[2][1] * m.m[3][0] -
//		m.m[0][1] * m.m[2][0] * m.m[3][2] -
//		m.m[0][0] * m.m[2][2] * m.m[3][1]) * determinantRecp;
//
//	resultInverse.m[3][2] = -(m.m[0][0] * m.m[1][1] * m.m[3][2] +
//		m.m[0][1] * m.m[1][2] * m.m[3][0] +
//		m.m[0][2] * m.m[1][0] * m.m[3][1] -
//		m.m[0][2] * m.m[1][1] * m.m[3][0] -
//		m.m[0][1] * m.m[1][0] * m.m[3][2] -
//		m.m[0][0] * m.m[1][2] * m.m[3][1]) * determinantRecp;
//
//	resultInverse.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] +
//		m.m[0][1] * m.m[1][2] * m.m[2][0] +
//		m.m[0][2] * m.m[1][0] * m.m[2][1] -
//		m.m[0][2] * m.m[1][1] * m.m[2][0] -
//		m.m[0][1] * m.m[1][0] * m.m[2][2] -
//		m.m[0][0] * m.m[1][2] * m.m[2][1]) * determinantRecp;
//
//	return resultInverse;
//}
Matrix4x4 Inverse(const Matrix4x4& m) {
	// clang-format off
	float determinant = +m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];
	Matrix4x4 result;
	float recpDeterminant = 1.0f / determinant;
	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
	result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
	result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) * recpDeterminant;
	result.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) * recpDeterminant;
	result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
		m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
	result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
		m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
		m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
	result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
		m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
		m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) * recpDeterminant;
	result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) * recpDeterminant;
	result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) * recpDeterminant;
	result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
		m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
		m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) * recpDeterminant;
	result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
		m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
		m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) * recpDeterminant;
	result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) * recpDeterminant;
	result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
		m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) * recpDeterminant;
	result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
		m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) * recpDeterminant;
	result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
		m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
		m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) * recpDeterminant;
	result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) * recpDeterminant;
	return result;
	// clang-format on
}

// 1.X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian)
{
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] -= std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

// 2.Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian)
{
	Matrix4x4 result{};
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0.0f;
	result.m[0][2] -= std::sin(radian);
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0.0f;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

// 3.Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian)
{
	Matrix4x4 result{};
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] -= std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;
}

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result{};
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result; // w=1がデカルト座標系であるので(x,y,1)のベクトルとしてmatrixとの積をとる
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f); // ベクトルに対して基本的な操作を行う行列でwが0になることはありえない
	// w=1がデカルト座標系であるので、w除算することで同次座標をデカルト座標に戻す
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale,const Vector3& rotate,const Vector3& translate)
{
	Matrix4x4 matScale = MakeScaleMatrix(scale);

	/*Matrix4x4 matRotateX = MakeRotateXMatrix(rotate.x);
	Matrix4x4 matRotateY = MakeRotateYMatrix(rotate.y);
	Matrix4x4 matRotateZ = MakeRotateZMatrix(rotate.z);
	Matrix4x4 matRot = matRotateX * matRotateY * matRotateZ;*/

	//Matrix4x4 matTranslate = MakeTranslateMatrix(translate);

	//Matrix4x4 result =matScale*matRot*matTranslate;

	Matrix4x4 result = Multiply(
		Multiply(MakeRotateXMatrix(rotate.x), MakeRotateYMatrix(rotate.y)),
		MakeRotateZMatrix(rotate.z));

	result.m[0][0] *= scale.x;
	result.m[0][1] *= scale.x;
	result.m[0][2] *= scale.x;
	result.m[0][3] = 0;

	result.m[1][0] *= scale.y;
	result.m[1][1] *= scale.y;
	result.m[1][2] *= scale.y;
	result.m[1][3] = 0;

	result.m[2][0] *= scale.z;
	result.m[2][1] *= scale.z;
	result.m[2][2] *= scale.z;
	result.m[2][3] = 0;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;

	return result;
}

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result{};

	float cot = 1.0f / std::tan(fovY / 2.0f);

	result.m[0][0] = (cot/aspectRatio);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = cot;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farClip/(farClip-nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = -(nearClip*farClip) / (farClip - nearClip);
	result.m[3][3] = 0.0f;

	return result;
}

// 正射影行列
//Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
//{
//	Matrix4x4 result{};
//	result.m[0][0] =2/(right-left);
//	result.m[0][1] = 0.0f;
//	result.m[0][2] = 0.0f;
//	result.m[0][3] = 0.0f;
//
//	result.m[1][0] = 0.0f;
//	result.m[1][1] = 2/(top-bottom);
//	result.m[1][2] = 0.0f;
//	result.m[1][3] = 0.0f;
//
//	result.m[2][0] = 0.0f;
//	result.m[2][1] = 0.0f;
//	result.m[2][2] = 1/(farClip-nearClip);
//	result.m[2][3] = 0.0f;
//
//	result.m[3][0] = (left+right)/(left-right) ;
//	result.m[3][1] = (top+bottom)/(bottom-top);
//	result.m[3][2] = nearClip/(nearClip-farClip);
//	result.m[3][3] = 1.0f;
//
//	return result;
//}

// ビューポート行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result{};
	result.m[0][0] = width/2;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -height/2;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = maxDepth-minDepth;
	result.m[2][3] = 0.0f;

	result.m[3][0] = left + width / 2;
	result.m[3][1] = top + height / 2;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	return result;
}

//void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
//	Novice::ScreenPrintf(x, y-15, "%s", label);
//	for (int row = 0; row < 4; ++row) {
//		for (int column = 0;column < 4;++column) {
//			Novice::ScreenPrintf(
//				x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
//		}
//	}
//}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 rotate{};
	Vector3 translate{};
	Vector3 cameraPosition{ 0.0f, 0.0f, -5.0f };
	//Vector3 scale{ 1.2f,0.79f,-2.1f };

	Vector3 kLocalVertices[3]
	{
		{-0.5f,-0.5f,0.0f},
		{0.0f,0.5f,0.0f},
		{0.5f,-0.5f,0.0f}
	};

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//Matrix4x4 orthographicMatrix =
		//	MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
		/*Matrix4x4 perspectiveFovMatrix =
			MakePerspectiveFovMatrix(0.63f, 1.33, 0.1f, 1000.0f);*/

		if (keys[DIK_W]) {
			translate.z+=0.1f;
		}
		if (keys[DIK_S]) {
			translate.z-=0.1f;
		}
		if (keys[DIK_D]) {
			translate.x+=0.1f;
		}
		if (keys[DIK_A]) {
			translate.x-=0.1f;
		}

		// 回る
		rotate.y += 0.03f;

		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f,1.0f,1.0f}, rotate, translate);

		//ビュー変換行列を作るためにカメラポジションで行列作成
		Matrix4x4 cameraMatrix =
			MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);

		//↑のカメラ行列を反転してビュー座標系変換行列を作る
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		//透視投影行列を作る
		Matrix4x4 projectionMatrix =
			MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

		//ビュー変換行列と透視投影を掛けてワールド座標系→ビュー座標系→透視投影座標系への
		//変換行列を作る
		Matrix4x4 worldViewProjectionMatrix =
			Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

		// ViewportMatrixを作る
		Matrix4x4 viewportMatrix =
			MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		// 3角形ポリゴンの各頂点をScreen空間へ変換する
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			// Transformを使うと同次座標系->デカルト座標系の処理が行われる
			Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);

			// Viewport座標系への変換を行ってScreen空間へ
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		//MatrixScreenPrintf(0, kRowHeight, worldMatrix, "worldMatrix");
		/*MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, perspectiveFovMatrix, "perspectiveFovMatrix");
		MatrixScreenPrintf(0, kRowHeight * 10, viewportMatrix, "viewportMatrix");*/
		//MatrixScreenPrintf(0, kRowHeight * 5, perspectiveFovMatrix, "perspectiveFovMatrix");
		 
		// 描画
		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x),
			int(screenVertices[1].y), int(screenVertices[2].x), int(screenVertices[2].y), RED,
			kFillModeSolid);

		VectorScreenPrintf(0, 0, cross, "Cross");


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
