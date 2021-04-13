#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <string>

#include"Matrix.h"
#include"DataReader.h"
#include"MLPRegressor.h"

using namespace std;


signed main() //平时打算法比赛习惯了用signed main
{
	auto x_train = read_data("train_data.txt");
	auto y_train = read_target("train_target.txt");
	auto x_test = read_data("test_data.txt");
	auto y_test = read_target("test_target.txt");

	MLPRegressor model({ 64,50,10 }, { logistic,logistic }, { logistic_derivative ,logistic_derivative });
	auto t1 = std::chrono::system_clock::now();
	model.fit(x_train, y_train);
	model.save_model("test_model.mlp");
	//MLPRegressor model("test_model.mlp"); //使用文件加载已经训练好的模型

	int cnt = 0;
	for (int i = 0; i < x_test.size(); i++) 
	{
		auto p = model.predict(x_test[i]);
		if (maxIndex(p) == maxIndex(y_test[i]))cnt++;
	}
	auto t2 = std::chrono::system_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000 << endl;
	std::cout <<"score: "<< 1.0*cnt / x_test.size() << std::endl;
	
	return 0;
}

