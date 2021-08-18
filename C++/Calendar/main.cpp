// This is a C++ mini project which prints out the 
// calendar for any given year.
// This project exposes the programmer to inter-related
// functions, I/O manipulation (<iomanip>) and 'static' 
// keyword in C++

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void header() {
  string months[] = {"January", "February", "March", "April", "May", "June",
                     "July", "August", "September", "October", "November", "December"
                    };
  
  // The value of this static 'i' remain in the memory as long as the program
  // is running.
  // Instead of keeping track of a variable which tells which month is to be displayed,
  // we can use 'static' to just get the job done without having to write extra code.
  static int i = 0;
  
  string month = months[i++];
  
  cout << "\n" << std::right << std::setfill('-') << std::setw(10) << ""
       << " " << month << " "
       << std::left << std::setw(10) << "" << std::setfill(' ')
       << endl;
  
  // This can be also done by simply printing a string like
  // "Sun Mon Tue Wed Thu Fri Sat" but we're playing with
  // <iomanip> here so no simple strings.
  cout << "Sun"
       << std::right << std::setw(5) << "Mon"
       << std::right << std::setw(5) << "Tue"
       << std::right << std::setw(5) << "Wed"
       << std::right << std::setw(5) << "Thu"
       << std::right << std::setw(5) << "Fri"
       << std::right << std::setw(5) << "Sat"
       << endl;
}

bool isLeapYear(int year) {
  if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    return true;
  return false;
}

int findDay(int dd, int mm, int yy) {
  // Tomohiko Sakamoto’s Algorithm
  // For explanation, visit this link https://www.geeksforgeeks.org/tomohiko-sakamotos-algorithm-finding-day-week/
  
  int arr[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  
  if (mm < 3)
    yy -= 1;
    
  return ((yy + yy/4 - yy/100 + yy/400 + arr[mm - 1] + dd) % 7);
}

int numberOfDays(int mm, int yy) {
  // Don't store arrays of months and track them and find how many
  // days are in the current month.
  // In a simple approach, only three cases are there:
  // 1) 'mm' is even, which means it is a 31 day month
  // 2) Now check if 'mm' is equal to 1. In this case,
  // check for a leap year and return 28 or 29 days accordingly.
  // 3) If the above two cases are not true, then we are dealing 
  // with a 30 day month. 
  // 30 day months: April, June, September, November
  // 31 day months: Jan, March, May, July, August, October, December
  if (mm % 2 == 0)
    return 31;
  else if (mm == 1) {
    if (isLeapYear(yy))
      return 29;
    return 28;
  }
  else
    return 30;
}

void printCalendar(int yy) {
  int currentDay = findDay(01, 01, yy);
  int daysCount = 0;
  
  cout << "Year: " << yy  << "\n" << endl;
  
  for (int i{}; i < 12; i++) {
    daysCount = numberOfDays(i, yy);
    
    header();
    
    // 'k' is used to keep track of which date to print
    // on the next iteration
    int k{};
    for (k = 0; k < currentDay; k++) {
      cout << std::right << std::setw(5) << "";
    }
    
    for (int j = 1; j <= daysCount; j++) {
      cout << std::right << std::setw(3) << j << "  ";
      
      if (++k > 6) {
        k = 0;
        cout << endl;
      }
    }
    
    if (k)
      cout << endl;
    
    currentDay = k;
  }
}

int main() {
  int yy{};
  
  cout << "Enter the year you wish to see the calendar of: ";
  cin >> yy;
  
  printCalendar(yy);
  
  cout << endl;
  
  return 0;
}
