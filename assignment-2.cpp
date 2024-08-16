// PHYS30762 Programming in C++
// Assignment 2: Physics Course Database
// Isaac Clemenger 23/02/2024

/* Reads in data of physics courses from a file, and outputs a specified selection of courses,
based on a given year, and computes the mean, standard deveiation and standard error on the
mean for the selection.*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<vector>
#include<string>
#include<sstream>
#include<tuple> 
#include<algorithm>


// Functions to validate input
bool check_file_exists(std::string file_name)
{
  std::fstream test_stream(file_name);
  if (test_stream.good()) return true; else return false; 
}

char correct_character_check(std::string& input, char char1, char char2)
{
  while(true)
  {
    try
    {
      // Check if they haven't input a single character as requested
      if (input.length() != 1) throw input;
      char character;
      character = input[0];
      // Check if the input is a character we want
      if (character == char1 || character == char2) return character; else throw character;
    } catch (...) {
      std::cout<<"Please enter a character that is an "<<char1<<" or "<<char2<<": \n";
      std::getline(std::cin, input);
    }
  }
}

char real_year_check(std::string& input)
{
  while(true)
  {
    try
    {
      // Only want single digit integers, so throw anything with more than 1 element
      if (input.length() != 1) throw input;
      int integer{std::stoi(input)};
      // See if year is within the range we want
      if (integer >= 1 && integer <= 4)
      {
        // Is being compared to string element in main function, so return as char
        return char(integer);
      } else {
        throw integer;
      }    
    } catch (...) {
      std::cout<<"Please enter a 1, 2, 3 or 4:\n";
      std::getline(std::cin, input);
    }
  }
}

// Functions to sort data
bool course_sort(std::string string1, std::string string2)
{
  // All course codes starts on index 5, and is 5 indices long, so only sort on these indices
  return string1.substr(5,5) < string2.substr(5,5);
}

bool name_sort(std::string string1, std::string string2)
{
  // All course names start on index 11, so sort from there up to end of the string
  return string1.substr(11) < string2.substr(11);
}

// Functions to calculate mean standard deviation, and error on the mean
double calculate_mean(std::vector<double> double_vector, double vector_length)
{
  double sum;
  for (int i{}; i<vector_length; i++ )
  {
    sum += double_vector[i];
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
  /* Formula for standard error only depends on deviation and N, so makes sense to calculate
   here and return both as a tuple */
  std_error = std_dev / sqrt(vector_length);
  std::tuple<double, double> dev_and_error(std_dev, std_error);
  return dev_and_error;
}


// Main function
int main()
{
  // Open file 
  std::string data_file{};
  while(true)
  {
    std::cout<<"Enter data filename: ";
    std::getline(std::cin, data_file);
    // Validate input
    if (check_file_exists(data_file) == true)
    {
      break;
    } else {
      std::cout<<"Unable to open file\n";
    }
  }
  // Open the file after checks to avoid opening lots of file streams
  std::fstream course_stream(data_file); 
  std::cout<<"File opened\n";

  // Determine length of the file
  // Allocate memory for data 
  double* average_mark{new double};
  int* course_code{new int};
  int* num_of_rows{new int};
  std::string* course_name{new std::string};
  std::string* course_title{new std::string};
  std::vector<double> average_marks;
  std::vector<std::string> course_titles;
  // Read data from file
  while (true)
    {
        course_stream>>*average_mark;
        course_stream>>*course_code;
        std::getline(course_stream, *course_name);
        // Exit the loop immediately after file ends, to avoid reading in final line twice
        if (course_stream.eof()) break;
        // Remove the trailing whitespace in the line from extacting the course mark and code
        (*course_name).erase(0,2);
        std::ostringstream name_stream;
        name_stream<<"PHYS "<<*course_code<<*course_name;
        *course_title = name_stream.str();
        name_stream.str("");
        average_marks.push_back(*average_mark);
        course_titles.push_back(*course_title);
    }
  // Delete dummy variables used to read in data
  delete average_mark, course_code, course_name, course_title;
  // Close file
  course_stream.close();

  // Find requested courses
  // Initialse required variables
  *num_of_rows = course_titles.size(); 
  // String input makes validation easier, so take in as string then convert to char
  std::string* string_see_specific_year{new std::string};
  char* see_specific_year{new char};
  char* specific_year{new char};
  std::string* string_specific_year{new std::string};
  std::cout<<"Would you like to see data for a specific year?\n(Type y for yes, n for no)\n";
  std::getline(std::cin,*string_see_specific_year);
  // Validate input
  *see_specific_year = correct_character_check(*string_see_specific_year,'y','n');
  int* deleted_indices{new int};
  /* Need to give the pointer a value to point to, such that we can dereference later in
  the loop*/
  *deleted_indices = 0;
  if (*see_specific_year == 'y')
  {
    std::cout<<"Which year would you like to see?\n";
    std::getline(std::cin,*string_specific_year);
    /* Validate input, we need to add 48 here as char to int finds the char with ascii code
    related to the int, so we need to 48 (ascii for 0), to get our integer */
    *specific_year = real_year_check(*string_specific_year) + 48;
    for (int i{}; i < *num_of_rows; i++)
    {
     /* Delete indices that are not requested, also then need to alter index by the number 
     of indices deleted, as vector length changes */
     if (course_titles[i - *deleted_indices][5] != (*specific_year))
     {
        course_titles.erase(course_titles.begin() + i - *deleted_indices);
        // Need to keep average marks array the same
        average_marks.erase(average_marks.begin() + i - *deleted_indices);
        (*deleted_indices) ++;
     }   
    }
  }
  // Free memory
  delete string_see_specific_year, see_specific_year, string_specific_year, specific_year, deleted_indices;

  // Sort based on users preferences
  // Initialsie required variables
  char* sort_type{new char};
  std::string* string_sort_type{new std::string};
  std::cout<<"Would you like to sort the data by course code or name\n(Type c for code, n for name)\n";
  std::getline(std::cin, *string_sort_type);
  // Validate input
  *sort_type = correct_character_check(*string_sort_type,'c','n');
  // Sort
  if (*sort_type == 'c')
  {
    sort(course_titles.begin(), course_titles.end(), course_sort); 
  } else 
  {
    sort(course_titles.begin(), course_titles.end(), name_sort);
  }
  delete string_sort_type, sort_type;

  // Print all courses using iterator
  *num_of_rows = course_titles.size();
  std::cout<<"Printing "<<*num_of_rows<<" requested courses:\n";
  // Initialise iterators
  std::vector<std::string>::iterator course_titles_begin{course_titles.begin()};
  std::vector<std::string>::iterator course_titles_end{course_titles.end()};  
  std::vector<std::string>::iterator course_titles_iterator;
  for (course_titles_iterator = course_titles_begin; course_titles_iterator < course_titles_end; course_titles_iterator++)
  {
    std::cout<<*course_titles_iterator<<"\n"; 
  }

  // Compute mean, standard deviation and standard error of mean
  double* mean{new double}; 
  *mean = calculate_mean(average_marks, *num_of_rows);
  std::tuple<double, double>* deviation_and_error{new std::tuple<double, double>};
  *deviation_and_error = calculate_standard_deviation(average_marks, *num_of_rows, *mean);
  double* standard_deviation{new double}; 
  *standard_deviation = std::get<0>(*deviation_and_error);
  double* standard_error{new double}; 
  *standard_error = std::get<1>(*deviation_and_error);
  // Print mean, standard deviation and standard error of mean
  std::cout.precision(3);
  std::cout<<"\n"<<"The mean of the requested courses is: "<<*mean<<" +- "<<*standard_error;
  std::cout<<"\n"<<"The standard deviation of the requested courses is: "<<*standard_deviation;
  // Free memory
  delete mean, standard_deviation, standard_error, deviation_and_error, num_of_rows;
  average_marks.clear();
  course_titles.clear();

  return 0;
}
