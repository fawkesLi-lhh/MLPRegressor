#ifndef  _MATRIX_H_
#define _MATRIX_H_

#include <cstdlib>
#include <iostream>
#include <vector>
#include <istream>
#include <ostream>

typedef void(*FUNPOINT)();
void do_something();
class Matrix {
public:
	Matrix(int n, int m) :N(n), M(m), data(n,std::vector<double>(m,0)){}
	template<typename FUN1, typename FUN2 = FUNPOINT, typename FUN3 = FUNPOINT>
	void traverse(FUN1 f1, FUN2 f2 = do_something, FUN3 f3 = do_something){
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) data[i][j] = f1(data[i][j],i,j);
			f2();
		} f3();
	}
	double get(int i, int j) const { return data[i][j]; }
	void set(double a, int i, int j) { data[i][j] = a; }
	Matrix transpose() const { Matrix ans(M,N); ans.traverse([this](double a, int i, int j) {return this->get(j, i); }); return ans; }
	Matrix& operator*=(double x) { traverse([x](double a, int i, int j) { return a * x; }); return *this; }
	Matrix& operator/=(const double x) { traverse([x](double a, int i, int j) { return a / x; });return *this;}
	Matrix& operator+=(const Matrix& x) { traverse([x](double a, int i, int j) { return a + x.get(i,j); }); return *this; }
	Matrix& operator-=(const Matrix& x) { traverse([x](double a, int i, int j) { return a - x.get(i,j); }); return *this; }
	Matrix operator*(const Matrix& x) const { 
		if (M != x.getN()) std::cout << "Matrix * error" << std::endl;
		Matrix ans(N, x.getM()); int temp = M; 
		ans.traverse([this, x, temp](double a, int i, int j) { double ans = 0; for (int k = 0; k < temp; k++)ans += this->get(i, k)*x.get(k, j); return ans; });
		return ans;
	}
	void print() { traverse([](double a,int i,int j) {printf("%f ", a); return a; }, []() {printf("\n"); }, []() {printf("\n"); }); }
	int getN() const { return N; }
	int getM() const { return M; }
private:
	int N, M;
	std::vector<std::vector<double>> data;
};

std::pair<int,int> maxIndex(const Matrix& x);
class mistream {
public:
	mistream(std::istream &tt):sin(tt){}
	double operator()(double a, int i, int j) {
		sin >> a;
		return a;
	}
private:
	std::istream &sin;
};
class mostream {
public:
	mostream(std::ostream &tt) :sout(tt) {}
	double operator()(double a, int i, int j) {
		sout << a << " ";
		return a;
	}
private:
	std::ostream &sout;
};
#endif // ! _MATRIX_H_

/*
typedef void(*FUNPOINT)();
void do_something(){}
template<typename T>
class Matrix {
public:
	Matrix(int n, int m) :N(n), M(m), data(n, std::vector<T>(m, 0)) {}
	template<typename FUN1, typename FUN2 = FUNPOINT, typename FUN3 = FUNPOINT>
	void traverse(FUN1 f1, FUN2 f2 = do_something, FUN3 f3 = do_something) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) data[i][j] = f1(data[i][j], i, j);
			f2();
		} f3();
	}
	T get(int i, int j)const  { return data[i][j]; }
	std::vector<T>& operator[](int a){ return data[a]; }
	Matrix transpose() const { Matrix ans(M, N); ans.traverse([this](double a, int i, int j) {return this->get(j, i); }); return ans; }
	Matrix& operator*=(double x) { traverse([x](T a, int i, int j) { return a * x; }); return *this; }
	Matrix& operator/=(const double x) { traverse([x](T a, int i, int j) { return a / x; }); return *this; }
	Matrix& operator+=(const Matrix& x) { traverse([x](T a, int i, int j) { return a + x.get(i, j); }); return *this; }
	Matrix& operator-=(const Matrix& x) { traverse([x](T a, int i, int j) { return a - x.get(i, j); }); return *this; }
	Matrix operator*(const Matrix& x) const {
		if (M != x.getN()) std::cout << "Matrix * error" << std::endl;
		Matrix ans(N, x.getM()); int temp = M;
		ans.traverse([this, x, temp](T a, int i, int j) { T ans = 0; for (int k = 0; k < temp; k++)ans += this->get(i, k)*x.get(k, j); return ans%10000; });
		return ans;
	}
	void print() { traverse([](T a, int i, int j) {cout<<a<<" "; return a; }, []() {cout<<"\n"; }, []() {cout << "\n"; }); }
	int getN() const { return N; }
	int getM() const { return M; }
private:
	int N, M;
	std::vector<std::vector<T>> data;
};
*/