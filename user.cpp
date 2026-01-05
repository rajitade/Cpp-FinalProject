#include <iostream>
#include <fstream>
#include "user.h"
using namespace std;

bool login(User &loggedInUser)
{
  string u, p;

  cout << "\n===== LOGIN SYSTEM =====\n";
  cout << "Username: ";
  cin >> u;
  cout << "Password: ";
  cin >> p;

  ifstream infile("users.dat");
  if (!infile)
  {
    cout << "Error: users.dat file not found!\n";
    return false;
  }

  User temp;
  while (infile >> temp.username >> temp.password >> temp.role)
  {
    if (temp.username == u && temp.password == p)
    {
      loggedInUser = temp;
      infile.close();
      return true;
    }
  }

  infile.close();
  cout << "Invalid username or password.\n";
  return false;
}
