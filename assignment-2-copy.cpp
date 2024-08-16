// PHYS30762 Programming in C++
// Assignment 2

// THIS IS ONLY A COPY NOT FINAL VERSION TO TEST ALTERNATE METHOD OF TAKING INPUT WITH 2 VECTORS
// MAKING IT EASIER TO SORT

// FINAL VERSION IS assignment-2.cpp

// Program to compute mean, standard deviation and standard
// error of the set of courses. Data is read from file

// Skeleton code - assessed components are missing

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<vector>
#include<string>
#include<sstream>
#include<tuple> 
#include<algorithm>

// Functions to compute mean, standard deviation or for other tasks.
bool check_file_exists(std::string file_name)
{
  std::fstream test_stream(file_name);
  if (test_stream.good()) return true; else return false; 
}

void correct_character_check(char& character, char char1, char char2)
/* User enters a character to pick their unit, or if they would like to repeat the code, so need a general 
function that sees if the user has entered one of two specific characters*/ 
{
  while (character != char1 && character != char2)
  {
    std::cout<<"Please enter a character that is an "<<char1<<" or "<<char2<<": \n";
    std::cin.clear();
    std::cin.ignore();
    std::cin>>character;
  }
}

int real_year_check(std::string& input)
{
  while(true)
  {
    try
    {
      int integer = std::stoi(input);
      int i{0};
      while (i < input.length())
      {
        if (input[i] == '.') throw input;
        i++;
      }
      if (integer == 1 || integer == 2 || integer == 3|| integer == 4)
      {
        return integer;  
      } else {
        throw integer;
      }    
    } catch (...) {
      std::cout<<"Please enter a 1, 2, 3 or 4:\n";
      std::cin>>input;
    }
  }
}

double calculate_mean(std::vector<double> double_vector, double vector_length)
{
  double sum;
  for (int i{}; i<vector_length; i++ )
  {
    sum += double_vector[i];
    //std::cout<<double_vector[i]<<"\n";
  }
  return sum / vector_length;
}

std::tuple<double, double> calculate_standard_deviation(std::vector<double> double_vector, int vector_length, double mean)
{
  double sum;
  double std_dev;
  double std_error;
  for (int i{}; i<vector_length; i++ )
  {
    sum += pow(double_vector[i] - mean, 2);
  }
  std_dev  = sqrt(sum * (1. / (vector_length - 1)));
  std_error = std_dev / sqrt(vector_length);
  std::tuple<double, double> dev_and_error(std_dev, std_error);
  return dev_and_error;
}

void index_vector_sort(std::vector<std::string> &vector, std::vector<int> sorting_indices)
{
  std::vector<std::string> sorted_vector(vector.size());
  for (int i{}; i < vector.size(); i++)
  {
    sorted_vector[i] = vector[sorting_indices[i]]; 
  }
  vector = sorted_vector;
}

void index_vector_sort(std::vector<int> &vector, std::vector<int> sorting_indices)
{
  std::vector<int> sorted_vector(vector.size());
  for (int i{}; i < vector.size(); i++)
  {
    sorted_vector[i] = vector[sorting_indices[i]]; 
  }
  vector = sorted_vector;
}

void ascending_string_sort_pair_of_vectors(std::vector<int> &vector_int, std::vector<std::string> &vector_string)
{
    std::vector<std::string> unsorted_vector_string{vector_string};
    std::vector<int> sorted_indices(vector_string.size());
    sort(vector_string.begin(), vector_string.end());
    // Once the vector of strings has been sorted, we need to sort the vector of ints too, so their order is unchanged 
    for (int i{}; i < vector_string.size(); i++)
    {
      for (int j{}; j < vector_string.size(); j++) 
      {
        if (vector_string[i] == unsorted_vector_string[j])
        {
          sorted_indices[i] = j;
        }
      }       
    }
    index_vector_sort(vector_int, sorted_indices);
}

void ascending_int_sort_pair_of_vectors(std::vector<int> &vector_int, std::vector<std::string> &vector_string)
{
    std::vector<int> unsorted_vector_int{vector_int};
    std::vector<int> sorted_indices(vector_int.size());
    sort(vector_int.begin(), vector_int.end());
    // Once the vector of strings has been sorted, we need to sort the vector of ints too, so their order is unchanged 
    for (int i{}; i < vector_int.size(); i++)
    {
      for (int j{}; j < vector_int.size(); j++) 
      {
        if (vector_int[i] == unsorted_vector_int[j])
        {
          sorted_indices[i] = j;
        }
      }       
    }
    index_vector_sort(vector_string, sorted_indices);
}

// Main function
int main()
{
  // Define variables
  std::string data_file{"courselist.dat"};
  // Open file (you must check if successful)
  while(true)
  {
    //std::cout<<"Enter data filename: ";
    //std::cin>>data_file;
    // Check if there is a path to the file
    if (check_file_exists(data_file) == true)
    {
      break;
    } else {
      std::cout<<"Unable to open file\n";
    }
  }
  // Open the file after checks to avoid opening lots of file streams
  std::fstream course_stream(data_file); 
  std::cout<<"file opened\n";
  // Determine length of the file
  // Allocate memory for data 
  double average_mark;
  int course_code;
  std::string course_name;
  std::vector<double> average_marks;
  std::vector<std::string> course_names;
  std::vector<int> course_codes;

  // Read data from file
  while (true)
    {
        course_stream>>average_mark;
        course_stream>>course_code;
        std::getline(course_stream, course_name);
        if (course_stream.eof()) break;
        course_name.erase(0,2);
        average_marks.push_back(average_mark);
        course_codes.push_back(course_code);
        course_names.push_back(course_name);
    }
  // Close file
  course_stream.close();
 
  int num_of_rows{0};
  num_of_rows = course_codes.size(); 
  char* see_specific_year{new char};
  // String to take input is only for validation, so dynamically allocate it such that we can delete it when done
  std::string* string_specific_year{new std::string};
  std::cout<<"Would you like to see data for a specific year?\n(Type y for yes, n for no)\n";
  std::cin>>*see_specific_year;
  correct_character_check(*see_specific_year,'y','n');
  int deleted_indices{0};
  if (*see_specific_year == 'y')
  {
    std::cout<<"Which year would you like to see?\n(For year 1, type 1)\n";
    std::cin>>*string_specific_year;
    // Validate user input
    int specific_year{real_year_check(*string_specific_year)};
    // Free memory for the input string which is not longer used
    delete string_specific_year;
    for (int i{}; i < num_of_rows; i++)
    {
     /* As our vector changes size as we delete indices, we need to correct the index we are
     checking for by the number of deleted indices, such that we don't skip indices. [5] as 
     the 5th index of each string in the vector is the first number of the course code.*/
     if (!((specific_year*10000 < course_codes[i - deleted_indices]) && (course_codes[i - deleted_indices] < (specific_year + 1) * 10000)))
     {
        // Deletes all indices of unwanted years, also need to correct for deleted indices
        course_codes.erase(course_codes.begin() + i - deleted_indices);
        course_names.erase(course_names.begin() + i - deleted_indices);
        average_marks.erase(average_marks.begin() + i - deleted_indices);
        deleted_indices ++;
     }   
    }
  }
  // Free memory
  delete see_specific_year;
  // Sort the data on user's preferences
  char* sort_type{new char};
  std::cout<<"Would you like to sort the data by course code or name\n(Type c for code, n for name)\n";
  std::cin>>*sort_type;
  correct_character_check(*sort_type, 'c', 'n');
  if (*sort_type == 'c')
  {
    ascending_int_sort_pair_of_vectors(course_codes, course_names);
  } else if (*sort_type == 'n')
  {
    ascending_string_sort_pair_of_vectors(course_codes, course_names);
  }
  // free memory
  delete sort_type;
  // Print number of courses requested
  num_of_rows = average_marks.size();
  std::vector<std::string> course_titles(num_of_rows);
  for (int i{}; i < num_of_rows; i++)
  {
    std::ostringstream name_stream;
    name_stream<<"PHYS "<<course_codes[i]<<course_names[i];
    std::string course_title(name_stream.str());
    name_stream.str("");
    course_titles[i] = course_title;
  }
  std::vector<std::string>::iterator course_titles_begin{course_titles.begin()};
  std::vector<std::string>::iterator course_titles_end{course_titles.end()};  
  std::vector<std::string>::iterator course_titles_iterator;
  for (course_titles_iterator = course_titles_begin; course_titles_iterator < course_titles_end; course_titles_iterator++)
  {
    std::cout<<*course_titles_iterator<<"\n"; 
  }
  // Compute mean, standard deviation and  standard error of mean
  double mean{calculate_mean(average_marks, num_of_rows)};
  std::tuple<double, double> deviation_and_error{calculate_standard_deviation(average_marks, num_of_rows, mean)};
  double standard_deviation{std::get<0>(deviation_and_error)};
  double standard_error{std::get<1>(deviation_and_error)};
  
  std::cout<<"\n"<<mean;
  std::cout<<"\n"<<standard_deviation;
  std::cout<<"\n"<<standard_error;
  
  // Free memory
  return 0;
}