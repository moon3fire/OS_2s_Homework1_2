#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <algorithm>
#include <stdlib.h>
void CalculateInterval(const int& index , const int& interval , const int& side , const int& lenght , int& this_row , int& this_column , const std::vector<std::vector<int>>& first , const std::vector<std::vector<int>>& second , std::vector<std::vector<int>>& answer)
{
	//row1 column2 -- column1 = row2
	std::vector<int> line(side);
	std::vector<int> column(side);
	int start = index*interval;
	int end = start + interval;
	for(int i = start ; i < end ; ++i)
	{
		if(i == lenght)
		{
			i = 0;
			end -= lenght;
			++this_row;
		}
		for(int elem = 0 ; elem < side ; ++elem)
		{
			line.push_back(first.at(elem).at(this_row));
			column.push_back(second.at(this_column).at(elem));
		}
		++this_column;
		for(int i = 0 ; i < side ; ++i)
		{
			answer[this_column][this_row] += line[i]*column[i];
		}
		line.clear();
		column.clear();
		this_column = 0;
	}
}

int main()
{
	int row1 , row2 , column1 , column2;
	std::cout << "Write how many rows you want first matrix to have" << std::endl;
	std::cin >> row1;
	std::cout << "Write how many columns you want first matrix to have" << std::endl;
	std::cin >> column1;
	std::cout << "Write how many rows you want second matrix to have" << std::endl;
	std::cin >> row2;
	std::cout << "Write how many columns you want second matrix to have" << std::endl;
	std::cin >> column2;
	std::vector<std::vector<int>> A(row1 , std::vector<int>(column1));
	std::vector<std::vector<int>> B(row2 , std::vector<int>(column2));
	std::vector<std::vector<int>> C(row1 , std::vector<int>(column2));
	if(column1 != row2)
	{
		std::cout << "Multipication is impossible" << std::endl;
		return 0;
	}
	
	for(int i = 0 ; i < row1 ; ++i)
	{
		for(int j = 0 ; j < column1 ; ++j)
		{
			A[i][j] = rand() % 5 + 1;
		}
	}
	
	for(int i = 0 ; i < row2 ; ++i)
	{
		for(int j = 0 ; j < column2 ; ++j)
		{
			B[i][j] = rand() % 5 + 1;
		}
	}
	
	int num_of_elements = row1 * column2;
	int degree_count = 0;
	while(num_of_elements > 0)
	{
		++degree_count;
		num_of_elements /= 2; // maybe this below
	}
	int indexes_to_count = row1 * column2 / degree_count;
	int row_counter = 0;
	int column_counter = 0;
	for(int i = 0 ; i < degree_count ; ++i)
	{
		// fork();
		CalculateInterval(i , indexes_to_count , column1 , row1 , row_counter , column_counter , A , B , C);
	}
	for(int i = 0 ; i < row1 ; ++i)
	{
		for(int j = 0 ; j < column2 ; ++j)
		{
			std::cout << C[i][j];
		}
		std::cout << std::endl;
	}
	
}
