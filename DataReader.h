#ifndef _DATAREADER_H_
#define _DATAREADER_H_

#include<vector>
#include<string>

#include"Matrix.h"

std::vector<Matrix> read_data(std::string name);

std::vector<Matrix> read_target(std::string name);

#endif // !_DATAREADER_H_