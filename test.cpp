#include <iostream>
#include <random>

double ret()
{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0, 9);

    return dis(gen);
}


int main()
{
	double *arr = new double[5];


	for(int i=0; i<5; i++){
		arr[i] = ret();
	}

	for (int i=0; i<5;i++)
		std::cout << (double)arr[i] << ":";
}