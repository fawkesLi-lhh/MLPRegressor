#include "MLPRegressor.h"

#include<cstdlib>
#include<ctime>
#include<fstream>
#include<cmath>

using namespace std;

double logistic(double x)
{
	return 1 / (1 + pow(2.718281828459, -x));
}
double logistic_derivative(double x)
{
	return logistic(x)*(1 - logistic(x));
}
MLPRegressor::MLPRegressor(::std::initializer_list<int> layer,
	::std::initializer_list<Activation> activation,
	::std::initializer_list<Activation> activation_deriv)
	: layers(layer), activations(activation), activation_derivs(activation_deriv)
{
	num_layers = layer.size();
	create_model(layers);
	srand(time(NULL));
	for (int i = 0; i < num_layers - 1; i++)  {
		biases[i].traverse([](double a, int i, int j) {return rand() % 100 / 100.0; });
		weights[i].traverse([](double a, int i, int j) {return rand() % 100 / 100.0; });
	}
}

MLPRegressor::MLPRegressor(::std::initializer_list<int> layer):layers(layer) {
	for (int i = 0; i < layer.size() - 1; i++) {
		activations.push_back(logistic);
		activation_derivs.push_back(logistic_derivative);
	}
	num_layers = layer.size();
	create_model(layers);
	srand(time(NULL));
	for (int i = 0; i < num_layers - 1; i++) {
		biases[i].traverse([](double a, int i, int j) {return rand() % 100 / 100.0; });
		weights[i].traverse([](double a, int i, int j) {return rand() % 100 / 100.0; });
	}
}

void MLPRegressor::fit(const std::vector<Matrix>& x, const std::vector<Matrix>& y, double learning_rate, int epochs)
{
	Matrix error(y[0].getN(),y[0].getM());
	for (int k = 0; k < epochs; k++)
	{
		for (int i = 0; i < x.size(); i++)
		{
			act[0] = x[i];
			for(int j = 0;j < num_layers - 1;j++) {
				act[j + 1] = weights[j] * act[j]; act[j + 1] += biases[j];
				act[j + 1].traverse([this,jj = j](double a, int i, int j) { return this->activations[jj](a); });
			}

			error = y[i]; error -= act[act.size() - 1];
			Matrix delta = act[act.size() - 1]; delta.traverse([this, jj = num_layers - 2](double a, int i, int j) {return this->activation_derivs[jj](a); });
			delta.traverse([error](double a, int i, int j) {return a * error.get(i, j); });
			deltas[num_layers - 2] = delta.transpose();

			for (int j = num_layers - 2; j > 0; j--) {
				delta = act[j].transpose();
				delta.traverse([this, jj = j](double a, int i, int j) {return this->activation_derivs[jj](a); });
				Matrix temp = deltas[j]; temp = temp * weights[j];
				delta.traverse([temp](double a, int i, int j) {return a * temp.get(i, j); });
				deltas[j - 1] = delta;

				Matrix delta = act[j] * deltas[j];
				delta *= learning_rate;
				weights[j] += delta.transpose();
				delta = deltas[j]; delta *= learning_rate;
				biases[j] += delta.transpose();
			}
			delta = act[0] * deltas[0];
			delta *= learning_rate;
			weights[0] += delta.transpose();
			delta = deltas[0]; delta *= learning_rate;
			biases[0] += delta.transpose();
		}
	}
}

Matrix MLPRegressor::predict(const Matrix& x)
{
	act[0] = x;
	for (int i = 0; i < num_layers - 1; i++) {
		act[i + 1] = weights[i] * act[i]; act[i + 1] += biases[i];
		act[i + 1].traverse([this,ii = i](double a, int i, int j) { return this->activations[ii](a); });
	}
	return act[num_layers - 1];
}

MLPRegressor::MLPRegressor(std::string name)
{
	std::ifstream fin(name);
	fin >> num_layers; layers.clear();
	for (int i = 0, tt; i < num_layers; i++)fin >> tt, layers.push_back(tt);
	create_model(layers);
	mistream m(fin);
	for (int i = 0; i < num_layers - 1; i++) {
		biases[i].traverse(m);
		weights[i].traverse(m);
	}
}

void MLPRegressor::save_model(std::string name)
{
	std::ofstream fout(name);
	fout << num_layers << "\n";
	for (int i = 0, tt; i < num_layers; i++)fout << layers[i] << " ";
	fout << "\n";
	mostream m(fout);
	for (int i = 0; i < num_layers - 1; i++) {
		biases[i].traverse(m); fout << "\n";
		weights[i].traverse(m); fout << "\n";
	}
}

void MLPRegressor::set_activation(::std::vector<Activation> activation,
	::std::vector<Activation> activation_deriv)
{
	activations = activation;
	activation_derivs = activation_deriv;
}

void MLPRegressor::create_model(const std::vector<int>& layers)
{
	Matrix ac(layers[0], 1);
	act.push_back(ac);
	for (int i = 0; i < num_layers - 1; i++)
	{
		Matrix weight(layers[i + 1], layers[i]);
		Matrix biase(layers[i + 1], 1);
		Matrix ac(layers[i + 1], 1);
		weights.push_back(weight);
		biases.push_back(biase);
		deltas.push_back(ac.transpose());
		act.push_back(ac);
	}
}
