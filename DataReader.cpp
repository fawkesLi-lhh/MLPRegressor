#include "DataReader.h"

#include<fstream>

std::vector<Matrix> read_data(std::string name)
{
	std::vector<Matrix> data;
	Matrix now(64, 1);
	double tt[66];

	std::ifstream fin(name);
	bool flag = true;
	while (flag) {
		for (int i = 0; i < 64; i++) {
			if (!(fin >> tt[i])) {
				flag = false;
				break;
			}
		}
		if (!flag)break;
		now.traverse([tt](double a, int i, int j) { return tt[i + j]; });
		data.push_back(now);
	}

	return data;
}

std::vector<Matrix> read_target(std::string name)
{
	std::vector<Matrix> target;
	Matrix now(10, 1);
	std::ifstream fin(name);
	bool flag = true;
	double tt;
	int val;
	while (true) {
		if (!(fin >> tt))break;
		val = tt + 0.5;
		now.traverse([val](double a, int i, int j) {return (i + j) == val; });
		target.push_back(now);
	}

	return target;
}
