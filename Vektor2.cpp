#include "pch.h"
#include "Vektor2.h"

Vektor2::Vektor2() {
	vek[0] = 0;
	vek[1] = 0;
	vek[2] = 0;
};


Vektor2::Vektor2(double x, double y) {
	vek[0] = x;
	vek[1] = y;
	vek[2] = 1;

};

Matrix2::Matrix2() {
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			if (i == j) {
				mat[i][j] = 1;
			} else {
				mat[i][j] = 0;

			}
		}
	}
}

Vektor2 Matrix2::operator*(const Vektor2 &v) {
	Vektor2 temp;
	for (int j = 0; j < DIM; j++) {
		for (int i = 0; i < DIM; i++) {
			temp.vek[j] = temp.vek[j] + mat[i][j] * v.vek[i];
		}
	}
	return temp;
}

void Matrix2::setTrans(double dx, double dy) {
	mat[DIM - 1][0] = dx;
	mat[DIM - 1][1] = dy;
	//mat[DIM - 1][2] = 1;
}

void Matrix2::setRot(double w) {
	mat[0][0] = mat[1][1] = cos(w);
	mat[0][1] = sin(w);
	mat[1][0] = -sin(w);
}

Vektor3::Vektor3() {
	vek[0] = 0;
	vek[1] = 0;
	vek[2] = 0;
	vek[3] = 0;
};


Vektor3::Vektor3(double x, double y, double z) {
	vek[0] = x;
	vek[1] = y;
	vek[2] = z;
	vek[3] = 1;
};

Matrix3::Matrix3() {
	for (int i = 0; i < DIM2; i++) {
		for (int j = 0; j < DIM2; j++) {
			if (i == j) {
				mat[i][j] = 1;
			}
			else {
				mat[i][j] = 0;

			}
		}
	}
}

Vektor3 Matrix3::operator*(const Vektor3& v) {
	Vektor3 temp;
	for (int j = 0; j < DIM2; j++) {
		for (int i = 0; i < DIM2; i++) {
			temp.vek[j] = temp.vek[j] + mat[i][j] * v.vek[i];
		}
	}
	return temp;
}

void Matrix3::setRotCubeX(double w) {
	mat[1][1] = mat[2][2] = cos(w);
	mat[1][2] = -sin(w);
	mat[2][1] = sin(w);
	mat[0][0] = mat[3][3] = 1;
	mat[0][1] = mat[0][2] = mat[0][3] = mat[1][0] = mat[1][3] = mat[2][0] = mat[2][3] = mat[3][0] = mat[3][1] = mat[3][2] = 0;
}

void Matrix3::setRotCubeY(double w) {
	mat[0][0] = mat[2][2] = cos(w);
	mat[2][0] = sin(w);
	mat[0][2] = -sin(w);
	mat[1][1] = mat[3][3] = 1;
	mat[0][1] = mat[0][3] = mat[1][0] = mat[1][2] = mat[1][3] = mat[2][1] = mat[2][3] = mat[3][0] = mat[3][1] = mat[3][2] = 0;
}

void Matrix3::setRotCubeZ(double w) {
	mat[0][0] = mat[1][1] = cos(w);
	mat[1][0] = sin(w);
	mat[0][1] = -sin(w);
	mat[2][2] = mat[3][3] = 1;
	mat[0][2] = mat[0][3] = mat[1][2] = mat[1][3] = mat[2][0] = mat[2][1] = mat[2][3] = mat[3][0] = mat[3][1] = mat[3][2] = 0;
}

void Matrix3::setTransCube(double dx, double dy){
	mat[DIM2 - 1][0] = dx;
	mat[DIM2 - 1][1] = dy;
	//mat[DIM2 - 1][2] = 1;
}