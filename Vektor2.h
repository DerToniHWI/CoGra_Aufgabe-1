#pragma once

#define DIM 3
#define DIM2 4

class Vektor2
{
public:
	double vek[DIM];
	Vektor2();
	Vektor2(double x, double y);
};

class Matrix2
{
	double mat[DIM][DIM];

public:
	Matrix2();
	
	void setTrans(double dx, double dy);
	void setRot(double w);
	Vektor2 operator* (const Vektor2 &v);
};

class Vektor3
{
public:
	double vek[DIM2];
	Vektor3();
	Vektor3(double x, double y, double z);
};

class Matrix3 {
	double mat[DIM2][DIM2];
public:
	Matrix3();

	Vektor3 operator* (const Vektor3& v);
	void setTransCube(double x, double y);
	void setRotCubeX(double w);
	void setRotCubeY(double w);
	void setRotCubeZ(double w);
};