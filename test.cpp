#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<vector>
#include<string>
#include<sstream>
#include<tuple>


char correct_character_check(std::string& input, char char1, char char2)
{
  while(true)
  {
    try
    {
      // Check if they have input more than 1 character
      if (input.length() != 1) throw input;
      char *character{new char};
      *character = input[0];
      // Check if the input is a character we want
      if (*character == char1 || *character == char2) return *character; else throw character;
    } catch (...) {
      std::cout<<"Please enter a character that is an "<<char1<<" or "<<char2<<": \n";
      std::getline(std::cin, input);
    }
  }
}

int main() 
{
  std::string* character{new std::string};
  std::cout<<"Would you like to see data for a specific year?\n(Type y for yes, n for no)\n";
  std::getline(std::cin, *character);
  char year{correct_character_check(*character, 'y', 'n')};
  delete character;
  std::cout<<year;
  return 0;
}

/*
*
for (auto showlist = course_titles.begin(); *course_title!= course_title.end(); course_title++)
{
  cout<<
}
for (const courseNameTem : course_title)
{
  cout<<
}
1 courseNameTem=1 cous
2 
3
4
*/