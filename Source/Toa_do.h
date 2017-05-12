#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#define Max 100
#define Max_chiphi 100001

class Toa_do
{
public:
	int x;
	int y;
	void loang_tim_duong(int tmp[][Max], int m, int n, Toa_do end, int &min, vector <Toa_do> &duong_di)
	{
		int b[4] = { 1, -1, 0, 0 };
		int c[4] = { 0, 0, 1, -1 };
		vector <Toa_do> A;
		A.push_back(*this);
		int mau = 0;
		int top = 0;
		while (top < A.size())
		{
			int cur = A.size();
			mau++;
			while (top < cur)
			{
				Toa_do B = A[top];
				top++;
				tmp[B.x][B.y] = mau;
				if (B.x == end.x && B.y == end.y)
				{
					min = mau;

					int tmpx = B.x;
					int tmpy = B.y;
					Toa_do tmp_diem;
					tmp_diem.insert(tmpx, tmpy);
					duong_di.push_back(tmp_diem);
					int tmp_mau = mau;
					while (tmp_mau > 1)
					{
						for (int i = 0; i < 4; i++)
						{
							if (tmpx + b[i] >= 1 && tmpy + c[i] >= 1 && tmpx + b[i] <= m && tmpy + c[i] <= n)
							{
								if (tmp[tmpx + b[i]][tmpy + c[i]] == tmp_mau - 1)
								{
									tmpx = tmpx + b[i];
									tmpy = tmpy + c[i];
									tmp_diem.insert(tmpx, tmpy);
									duong_di.push_back(tmp_diem);
									tmp_mau = tmp_mau - 1;
									break;
								}
							}
						}
					}
					return;
				}
				for (int i = 0; i < 4; i++)
				{
					if (B.x + b[i] >= 1 && B.y + c[i] >= 1 && B.x + b[i] <= m && B.y + c[i] <= n)
					{
						if (tmp[B.x + b[i]][B.y + c[i]] == 0)
						{
							Toa_do C;
							C.x = B.x + b[i];
							C.y = B.y + c[i];
							A.push_back(C);
							tmp[B.x + b[i]][B.y + c[i]] = -1;
						}
					}
				}
			}
		}
	}
	void loang(int tmp[][Max], int m, int n, Toa_do end, int &min)
	{
		int b[4] = { 1, -1, 0, 0 };
		int c[4] = { 0, 0, 1, -1 };
		vector <Toa_do> A;
		A.push_back(*this);
		int mau = 0;
		int top = 0;
		while (top < A.size())
		{
			int cur = A.size();
			mau++;
			while (top < cur)
			{
				Toa_do B = A[top];
				top++;
				tmp[B.x][B.y] = mau;
				if (B.x == end.x && B.y == end.y)
				{
					min = mau;
					return;
				}
				for (int i = 0; i < 4; i++)
				{
					if (B.x + b[i] >= 1 && B.y + c[i] >= 1 && B.x + b[i] <= m && B.y + c[i] <= n)
					{
						if (tmp[B.x + b[i]][B.y + c[i]] == 0)
						{
							Toa_do C;
							C.x = B.x + b[i];
							C.y = B.y + c[i];
							A.push_back(C);
							tmp[B.x + b[i]][B.y + c[i]] = -1;
						}
					}
				}
			}
		}
		/*	for (int i = 0; i < 4; i++)
		{
		if (u + b[i] >= 1 && v + c[i] >= 1 && u + b[i] <= m && v + c[i] <= n)
		{
		if (tmp[u + b[i]][v + c[i]] == 0)
		{
		tmp[u + b[i]][v + c[i]] = count+1;
		if (u + b[i] == end.x && u + c[i] == end.y)
		{
		if (min >count + 1)
		min = count + 1;
		return;
		}
		}
		}
		}
		for (int i = 0; i < 4; i++)
		{
		if (u + b[i] >= 1 && v + c[i] >= 1 && u + b[i] <= m && v + c[i] <= n && tmp[u + b[i]][v + c[i]] == count+1)
		{
		loang(tmp, m, n, u + b[i], v + c[i], count + 1, end, b, c,min);
		}
		}*/
	}
	//============================================================================================================================
	//Su dung thuat toan A*
	//Tra ve khoang cach giua 2 diem 
	int Khoang_Cach(int map[][Max], int m, int n, Toa_do end)
	{
		int tmp[Max][Max];
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (map[i][j] > 0 || map[i][j] == -1)
				{
					tmp[i][j] = 0;
				}
				else
					tmp[i][j] = map[i][j];
			}
		}
		tmp[x][y] = 1;
		int min = -1;
		this->loang(tmp, m, n, end, min);
		return min;
	};
	//============================================================================================================================
	void insert(int u, int v)
	{
		x = u;
		y = v;
	}
	//============================================================================================================================
	void insert(Toa_do k)
	{
		x = k.x;
		y = k.y;
	}
	//============================================================================================================================
	//============================================================================================================================
	void output(ofstream &fout)
	{
		fout << x << " " << y;
	}
	Toa_do();
	~Toa_do();
};

