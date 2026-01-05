#include <iostream>
#include <fstream>
#include <ctime>
#include "audit.h"
using namespace std;

// Log action with timestamp
void logAction(const string &username, const string &action)
{
  ofstream outfile("audit.log", ios::app); // append mode
  if (!outfile)
  {
    cout << "Error opening audit.log\n";
    return;
  }

  // Get current time
  time_t now = time(0);
  char *dt = ctime(&now); // returns a string with newline

  // Remove newline from ctime
  string timestamp(dt);
  if (!timestamp.empty() && timestamp[timestamp.length() - 1] == '\n')
    timestamp.erase(timestamp.length() - 1);

  outfile << "[" << timestamp << "] "
          << username << " : " << action << endl;

  outfile.close();
}
