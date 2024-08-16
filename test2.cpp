// PL3/vector4.cpp
// Demonstration of the vector container, iteratotrs, sort and reverse
// Source: Prof. Niels Walet's code repository
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<vector>
#include<string>
#include<sstream>
#include<tuple>

void index_vector_sort(std::vector<char> &vector, std::vector<int> sorting_indices)
{
  std::vector<char> sorted_vector(vector.size());
  for (int i{}; i < vector.size(); i++)
  {
    sorted_vector[i] = vector[sorting_indices[i]]; 
  }
  vector = sorted_vector;
}

int main() 
{
  int specific_year;
  std::vector<int> sorted_indices{13,12,15,1,5,10,14,11,2,0,8,3,9,16,4,17,7,6};
  
  std::vector<char> list{'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k'};
  
  index_vector_sort(list, sorted_indices);
 
  for (int i{}; i < list.size(); i++)
  {
    std::cout<<list[i]<<"\n";
  }
  return 0;
}