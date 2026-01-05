#ifndef PATIENT_H
#define PATIENT_H

#include <string>
using namespace std;

struct Patient
{
  int id;
  string firstName;
  string lastName;
  int age;
  string phone;
};

const int MAX_PATIENTS = 100;

// ======================= Patient Management =======================
void addPatient(Patient patients[], int &numPatients, int &nextId);
void listPatients(Patient patients[], int numPatients);
int findPatientById(Patient patients[], int numPatients, int id);
void searchPatient(Patient patients[], int numPatients);
void deletePatient(Patient patients[], int &numPatients);

// Optional: link to audit logging (implemented in audit.cpp)
void logPatientAction(const string &action);

#endif
