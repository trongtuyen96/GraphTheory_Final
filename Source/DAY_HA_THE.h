#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#define Max 100
#define Max_chiphi 100001
#include "Toa_do.h"
#include "Day_noi.h"

class DAY_HA_THE
{

public:
	vector <Day_noi> Cach_noi_DHT;
	int chiphi_CH_CH[Max][Max];
	vector <Toa_do> Can_ho;
	vector<Duong_di> Duong_noi_DHT;
	//============================================================================================================================
	void Tao_Duong_di(int map[][Max], int m, int n)
	{
		vector <Toa_do> tmp_duong_di;
		if (Cach_noi_DHT.size() == 0)
			return;
		int min = -1;
		int tmp[Max][Max];
		Duong_noi_DHT.resize(Cach_noi_DHT.size());
		for (int i = 0; i < Cach_noi_DHT.size(); i++)
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
			tmp[Cach_noi_DHT[i].Start.x][Cach_noi_DHT[i].Start.y] = 1;
			Cach_noi_DHT[i].Start.loang_tim_duong(tmp, m, n, Cach_noi_DHT[i].End, min, tmp_duong_di);
			if (min != -1);
			{
				for (int j = 0; j < tmp_duong_di.size(); j++)
				{
					Duong_noi_DHT[i].ListOfPoint.push_back(tmp_duong_di[j]);
				}
			}
			tmp_duong_di.clear();
		}
	}
	//============================================================================================================================
	void Tinh_chiphi_CH_CH(int map[][Max], int m, int n)
	{
		for (unsigned i = 0; i < Can_ho.size() - 1; i++)
		{
			for (unsigned j = i + 1; j < Can_ho.size(); j++)
			{
				int k = Can_ho[i].Khoang_Cach(map, m, n, Can_ho[j]);
				chiphi_CH_CH[i][j] = k;
				chiphi_CH_CH[j][i] = k;
			}
		}
	}
	//============================================================================================================================
	//Dung thuat toan tim cay khung nho nhat
	//chi phi nho nhat noi day dien ha the trong khu dan cu
	int Chi_phi_min(int map[][Max], int m, int n)
	{
		if (Can_ho.size() == 1)
			return 0;

		Tinh_chiphi_CH_CH(map, m, n);

		int b[Max];
		for (unsigned i = 0; i < Can_ho.size(); i++)
		{
			b[i] = 0;
		}
		b[0] = 1;

		int val = 0;
		int min = 1;

		while (min != -1)
		{
			min = -1; int x1, x2;
			for (unsigned i = 0; i < Can_ho.size(); i++)
			{
				if (b[i] == 0)
				{
					for (unsigned j = 0; j < Can_ho.size(); j++)
					{
						if (b[j] == 1)
						{
							if (min == -1 && chiphi_CH_CH[j][i] != -1)
							{
								min = chiphi_CH_CH[j][i];
								x1 = i;
								x2 = j;
							}
							else
							if (chiphi_CH_CH[j][i] < min && chiphi_CH_CH[j][i] != -1)
							{
								min = chiphi_CH_CH[j][i];
								x1 = i;
								x2 = j;
							}
						}
					}
				}
			}
			if (min != -1)
			{
				Day_noi tmp;
				tmp.insert(Can_ho[x1], Can_ho[x2], min);
				Cach_noi_DHT.push_back(tmp);
				val = val + min;
				b[x1] = 1;
			}
		}

		return val;
	}
	//============================================================================================================================
	//chi phi nho nhat noi day dien cao the giua May Phat Dien den Khu Dan Cu
	//ret la toa do MPD noi den KDC
	int Chi_phi_min_MPD_KDC(int map[][Max], int m, int n, Toa_do MPD, Toa_do &ret)
	{
		int min = -1;

		for (unsigned i = 0; i < Can_ho.size(); i++)
		{
			if (min == -1)
			{
				int k = Can_ho[i].Khoang_Cach(map, m, n, MPD);
				if (k != -1)
				{
					min = Can_ho[i].Khoang_Cach(map, m, n, MPD);
					ret = Can_ho[i];
				}
			}
			else
			{
				int k = Can_ho[i].Khoang_Cach(map, m, n, MPD);
				if (k < min && k != -1)
				{
					min = k;
					ret = Can_ho[i];
				}
			}
		}

		return min;
	}
	//============================================================================================================================
	//chi phi nho nhat noi day dien cao the giua Khu Dan Cu nay den Khu Dan Cu kia
	//ret1 la toa do KDC1 noi den ret2 la toa do thuoc KDC2
	int Chi_phi_min_KDC_KDC(int map[][Max], int m, int n, DAY_HA_THE KDC2, Toa_do &ret1, Toa_do &ret2)
	{
		ret1 = Can_ho[0];
		ret2 = KDC2.Can_ho[0];
		int min = -1;
		for (unsigned i = 0; i < Can_ho.size(); i++)
		{
			for (unsigned j = 0; j < KDC2.Can_ho.size(); j++)
			{
				if (min == -1)
				{
					int k = Can_ho[i].Khoang_Cach(map, m, n, KDC2.Can_ho[j]);
					if (k != -1)
					{
						min = k;
						ret1 = Can_ho[i];
						ret2 = KDC2.Can_ho[j];
					}
				}
				else
				{
					int k = Can_ho[i].Khoang_Cach(map, m, n, KDC2.Can_ho[j]);
					if (k < min && k != -1)
					{
						min = k;
						ret1 = Can_ho[i];
						ret2 = KDC2.Can_ho[j];
					}
				}
			}
		}
		return min;
	}
	//============================================================================================================================
	void insert(int u, int v)
	{
		Toa_do tmp;
		tmp.insert(u, v);
		Can_ho.push_back(tmp);
	}
	//============================================================================================================================
	void output(ofstream &fout)
	{
		fout << Cach_noi_DHT.size() << endl;
		for (unsigned i = 0; i < Cach_noi_DHT.size(); i++)
		{
			Cach_noi_DHT[i].output(fout);
		}
	}
	DAY_HA_THE();
	~DAY_HA_THE();
};

