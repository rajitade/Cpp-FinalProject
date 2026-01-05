#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include "patient.h"
#include "doctor.h"
using namespace std;

struct Appointment
{
  int id; // unique appointment ID
  int patientId;
  int doctorId;  // assigned doctor
  string date;   // YYYY-MM-DD
  string time;   // HH:MM
  string status; // Scheduled, Completed, Cancelled
};

const int MAX_APPOINTMENTS = 200;

// ======================= Appointment Management =======================
void addAppointment(Appointment appointments[], int &numAppointments, int numPatients, int patientIds[], Doctor doctors[], int numDoctors);
void listAppointments(Appointment appointments[], int numAppointments, Patient patients[], int numPatients);
void deleteAppointment(Appointment appointments[], int &numAppointments);
bool checkConflict(Appointment appointments[], int numAppointments, int doctorId, string date, string time);
bool validateDate(string date);
bool validateTime(string time);

// ======================= New Features =======================
void updateAppointmentStatus(Appointment appointments[], int numAppointments);
void dailyReport(Appointment appointments[], int numAppointments, Patient patients[], int numPatients);

#endif
