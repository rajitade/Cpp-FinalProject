#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

struct User
{
  string username;
  string password;
  string role; // ADMIN or RECEPTION
};

bool login(User &loggedInUser);

#endif
