#ifndef _MLPREGRESSOR_H_
#define _MLPREGRESSOR_H_

#include <string>
#include <vector>

#include "Matrix.h"

typedef double(*Activation)(double x);
double logistic(double x);
double logistic_derivative(double x);

class MLPRegressor
{
public:
	MLPRegressor(::std::initializer_list<int> layer, ::std::initializer_list<Activation> activation, ::std::initializer_list<Activation> activation_deriv);
	MLPRegressor(::std::initializer_list<int> layer);

	void fit(const ::std::vector<Matrix> &x, const ::std::vector<Matrix> &y, double learning_rate = 0.2, int epochs = 5);

	Matrix predict(const Matrix& x);

	MLPRegressor(::std::string name);

	void save_model(::std::string name);

private:
	void set_activation(::std::vector<Activation> activation,
		::std::vector<Activation> activation_deriv);

	void create_model(const ::std::vector<int>& layer);

private:
	::std::vector<int> layers;
	::std::vector<Activation> activations;
	::std::vector<Activation> activation_derivs;
	::std::vector<Matrix> deltas;
	::std::vector<Matrix> act;

	int num_layers;
	::std::vector<Matrix> biases, weights;
};

#endif // !_MLPREGRESSOR_H_
