#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#define Max 100
#define Max_chiphi 100001
#include "Toa_do.h"
struct Duong_di
{
	vector <Toa_do> ListOfPoint;
};
class Day_noi
{
private:

public:
	Toa_do Start;
	Toa_do End;
	int Khoang_cach;
	void insert(Toa_do u, Toa_do v, int kc)
	{
		Start = u;
		End = v;
		Khoang_cach = kc;
	}
	void output(ofstream &fout)
	{
		Start.output(fout);
		fout << " ";
		End.output(fout);
		fout << " ";
		fout << Khoang_cach << endl;
	}
	Day_noi();
	~Day_noi();
};

