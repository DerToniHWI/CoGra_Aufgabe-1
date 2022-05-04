#pragma once

#define DIM 3

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