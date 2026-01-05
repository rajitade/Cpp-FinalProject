#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include "patient.h"
using namespace std;

struct Appointment
{
  int patientId;
  string date; // YYYY-MM-DD
  string time; // HH:MM
};

const int MAX_APPOINTMENTS = 200;

void addAppointment(Appointment appointments[], int &numAppointments, int numPatients, int patientIds[]);
void listAppointments(Appointment appointments[], int numAppointments, Patient patients[], int numPatients);
bool checkConflict(Appointment appointments[], int numAppointments, string date, string time);
void deleteAppointment(Appointment appointments[], int &numAppointments);
bool validateDate(string date);
bool validateTime(string time);

#endif
