#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include "DAY_HA_THE.h"
#define Max 100
#define Max_chiphi 100001
#include "Day_noi.h"
#include <string>
#include <string.h>

class DAY_CAO_THE
{
public:
	vector <Toa_do> May_phat_dien;
	vector <Day_noi> Cach_noi_DCT;
	int Tong_chi_phi;
	int chiphi_KDC_KDC[Max][Max];
	int chiphi_MPD_KDC[Max][Max];
	Day_noi Cach_noi_KDC_KDC[Max][Max];
	Day_noi Cach_noi_MPD_KDC[Max][Max];
	vector <DAY_HA_THE> Khu_Dan_Cu;
	vector<Toa_do> Wall;
	vector<Toa_do> Fac;
	vector<Duong_di> Duong_noi_DCT;
	//============================================================================================================================
	void Tao_Duong_di(int map[][Max], int m, int n)
	{
		vector <Toa_do> tmp_duong_di;
		int min = -1;
		int tmp[Max][Max];
		Duong_noi_DCT.resize(Cach_noi_DCT.size());
		for (int i = 0; i < Cach_noi_DCT.size(); i++)
		{
			min = -1;
			for (int u = 1; u <= m; u++)
			{
				for (int v = 1; v <= n; v++)
				{
					if (map[u][v] > 0 || map[u][v] == -1)
					{
						tmp[u][v] = 0;
					}
					else
						tmp[u][v] = map[u][v];
				}
			}
			tmp[Cach_noi_DCT[i].Start.x][Cach_noi_DCT[i].Start.y] = 1;
			Cach_noi_DCT[i].Start.loang_tim_duong(tmp, m, n, Cach_noi_DCT[i].End, min, tmp_duong_di);
			if (min != -1)
			{
				for (int j = 0; j < tmp_duong_di.size(); j++)
				{
					Duong_noi_DCT[i].ListOfPoint.push_back(tmp_duong_di[j]);
				}
			}
			tmp_duong_di.clear();
		}
	}

	void Tinh_chi_phi_noi_tat_ca_MPD_KDC(int map[][Max], int m, int n)
	{
		for (unsigned i = 0; i < May_phat_dien.size(); i++)
		{
			for (unsigned j = 1; j < Khu_Dan_Cu.size(); j++)
			{
				Toa_do tmp_ret1;
				chiphi_MPD_KDC[i][j] = Khu_Dan_Cu[j].Chi_phi_min_MPD_KDC(map, m, n, May_phat_dien[i], tmp_ret1);
				if (chiphi_MPD_KDC[i][j] != -1)
				{
					Cach_noi_MPD_KDC[i][j].insert(May_phat_dien[i], tmp_ret1, chiphi_MPD_KDC[i][j]);
				}
			}
		}
	}
	//============================================================================================================================
	void Tinh_chi_phi_noi_tat_ca_KDC_KDC(int map[][Max], int m, int n)
	{
		for (unsigned i = 1; i < Khu_Dan_Cu.size() - 1; i++)
		{
			for (unsigned j = i + 1; j < Khu_Dan_Cu.size(); j++)
			{
				Toa_do tmp_ret1;
				Toa_do tmp_ret2;
				int k = Khu_Dan_Cu[i].Chi_phi_min_KDC_KDC(map, m, n, Khu_Dan_Cu[j], tmp_ret1, tmp_ret2);
				chiphi_KDC_KDC[i][j] = k;
				chiphi_KDC_KDC[j][i] = k;
				if (k != -1)
				{
					Cach_noi_KDC_KDC[i][j].insert(tmp_ret1, tmp_ret2, chiphi_KDC_KDC[i][j]);
					Cach_noi_KDC_KDC[j][i].insert(tmp_ret2, tmp_ret1, chiphi_KDC_KDC[i][j]);
				}
			}
		}
	}

	//============================================================================================================================
	//chi phi nho nhat noi day dien cao the 
	void Chi_phi_min(int map[][Max], int m, int n)
	{
		int size_KDC = Khu_Dan_Cu.size();
		int chiphi[Max];
		int nhan[Max];
		int T_daduyet[Max];
		Tinh_chi_phi_noi_tat_ca_MPD_KDC(map, m, n);
		Tinh_chi_phi_noi_tat_ca_KDC_KDC(map, m, n);


		for (int i = 0; i < size_KDC; i++)
		{
			chiphi[i] = Max_chiphi;
			nhan[i] = -1;
			T_daduyet[i] = 0;
		}

		for (int i = 1; i < size_KDC; i++)
		{
			int tmp = -1;
			for (unsigned j = 0; j < May_phat_dien.size(); j++)
			{
				if (tmp == -1 && chiphi_MPD_KDC[j][i] != -1)
				{
					tmp = j;
				}
				else
				{
					if (chiphi_MPD_KDC[tmp][i] > chiphi_MPD_KDC[j][i] && chiphi_MPD_KDC[j][i] != -1)
					{
						tmp = j;
					}
				}
			}
			if (tmp != -1)
			{
				chiphi[i] = chiphi_MPD_KDC[tmp][i];
				nhan[i] = -tmp - 2;
			}
			//MPD=0 -->> nhan[i] =-2
			//MPD=1 -->> nhan[i] =-3
		}

		int tmp_min = 1;
		while (tmp_min < size_KDC)
		{
			tmp_min = 1;
			while ((chiphi[tmp_min] == Max_chiphi || T_daduyet[tmp_min] == 1) && tmp_min < size_KDC)
				tmp_min++;

			if (tmp_min == size_KDC)
				break;

			for (int i = tmp_min + 1; i < size_KDC; i++)
			{
				if (chiphi[i] != Max_chiphi && chiphi[tmp_min] > chiphi[i] && T_daduyet[i] == 0)
				{
					tmp_min = i;
				}

			}
			for (int i = 1; i < size_KDC; i++)
			{
				if (i != tmp_min && T_daduyet[i] != 1)
				{
					if (nhan[i] < -1)
					{
						if (chiphi_KDC_KDC[tmp_min][i] < chiphi[i] && chiphi_KDC_KDC[tmp_min][i] != -1)
						{
							chiphi[i] = chiphi[tmp_min] + chiphi_KDC_KDC[tmp_min][i];
							nhan[i] = tmp_min;
						}
					}
					else
					if (chiphi[tmp_min] + chiphi_KDC_KDC[tmp_min][i] < chiphi[i] && chiphi_KDC_KDC[tmp_min][i] != -1)
					{
						chiphi[i] = chiphi[tmp_min] + chiphi_KDC_KDC[tmp_min][i];
						nhan[i] = tmp_min;
					}
				}
			}
			T_daduyet[tmp_min] = 1;
		}

		Tong_chi_phi = 0;
		for (int i = 1; i < size_KDC; i++)
		{
			if (nhan[i] >= 0)
			{
				Cach_noi_DCT.push_back(Cach_noi_KDC_KDC[nhan[i]][i]);
				Tong_chi_phi = Tong_chi_phi + chiphi_KDC_KDC[nhan[i]][i];
			}
			else
			if (nhan[i] < -1)
			{
				Cach_noi_DCT.push_back(Cach_noi_MPD_KDC[-nhan[i] - 2][i]);
				Tong_chi_phi = Tong_chi_phi + chiphi_MPD_KDC[-nhan[i] - 2][i];
			}
		}
		for (int i = 1; i < size_KDC; i++)
		{
			Tong_chi_phi = Tong_chi_phi + Khu_Dan_Cu[i].Chi_phi_min(map, m, n);
		}
		Tao_Duong_di(map, m, n);
		for (int i = 1; i < size_KDC; i++)
		{
			Khu_Dan_Cu[i].Tao_Duong_di(map, m, n);
			for (int j = 0; j < Khu_Dan_Cu[i].Duong_noi_DHT.size(); j++)
			{
				Duong_noi_DCT.push_back(Khu_Dan_Cu[i].Duong_noi_DHT[j]);
			}
		}
	}

	//============================================================================================================================
	void input(char *filein, int map[][Max], int &m, int &n)
	{
		ifstream fin;
		fin.open(filein);
		if (!fin.is_open())
			return;

		fin >> m >> n;
		for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
		{
			string s;
			fin >> s;
			if (s[0] == '#')
			{
				map[i][j] = -2;
				Toa_do A;
				A.x = j;
				A.y = i;
				Wall.push_back(A);
			}
			else
			{
				if (s[0] == 'X')
				{
					map[i][j] = -1;
					Toa_do A;
					A.x = j;
					A.y = i;
					Fac.push_back(A);
				}
				else
				{
					map[i][j] = stoi(s);
				}
			}
		}

		int Max_size = 0;
		for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
		{
			if (map[i][j] > 0)
			{
				if (map[i][j] > Max_size)
				{
					Khu_Dan_Cu.resize(map[i][j]);
					Max_size = map[i][j];
					DAY_HA_THE tmp;
					tmp.insert(i, j);
					Khu_Dan_Cu.push_back(tmp);
				}
				else
					Khu_Dan_Cu[map[i][j]].insert(i, j);
			}
			if (map[i][j] == -1)
			{
				Toa_do tmp;
				tmp.insert(i, j);
				May_phat_dien.push_back(tmp);
			}
		}

		fin.close();
	}
	//============================================================================================================================
	void output(char *fileout, int map[][Max], int m, int n)
	{
		ofstream fout;
		fout.open(fileout);
		if (!fout.is_open())
			return;

		fout << Khu_Dan_Cu.size() - 1 << endl;
		for (unsigned i = 1; i < Khu_Dan_Cu.size(); i++)
		{
			Khu_Dan_Cu[i].output(fout);
		}

		fout << Cach_noi_DCT.size() << endl;
		for (unsigned i = 0; i < Cach_noi_DCT.size(); i++)
		{
			Cach_noi_DCT[i].output(fout);
		}

		fout << Tong_chi_phi;

		fout.close();
	}

	DAY_CAO_THE();
	~DAY_CAO_THE();
};

