#ifndef AUDIT_H
#define AUDIT_H

#include <string>
using namespace std;

// Logs an action performed by a user
void logAction(const string &username, const string &action);

#endif
