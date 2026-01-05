#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
using namespace std;

#define MAX_DOCTORS 20

struct Doctor
{
  int id;
  string name;
  string specialization;
  string phone;
};

// Doctor functions
void addDoctor(Doctor doctors[], int &numDoctors, int &nextDoctorId);
void listDoctors(Doctor doctors[], int numDoctors);
void deleteDoctor(Doctor doctors[], int &numDoctors);

#endif
