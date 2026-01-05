#include <iostream>
#include <regex>
#include "appointment.h"
#include "patient.h"

using namespace std;

// Check if appointment conflicts with existing
bool checkConflict(Appointment appointments[], int numAppointments, string date, string time)
{
  for (int i = 0; i < numAppointments; i++)
  {
    if (appointments[i].date == date && appointments[i].time == time)
      return true;
  }
  return false;
}

// Validate date format YYYY-MM-DD
bool validateDate(string date)
{
  regex pattern("\\d{4}-\\d{2}-\\d{2}");
  return regex_match(date, pattern);
}

// Validate time format HH:MM
bool validateTime(string time)
{
  regex pattern("\\d{2}:\\d{2}");
  return regex_match(time, pattern);
}

// Add a new appointment
void addAppointment(Appointment appointments[], int &numAppointments, int numPatients, int patientIds[])
{
  if (numAppointments >= MAX_APPOINTMENTS)
  {
    cout << "Appointment limit reached.\n";
    return;
  }

  int patientId;
  cout << "Enter patient ID: ";
  cin >> patientId;

  bool patientExists = false;
  for (int i = 0; i < numPatients; i++)
  {
    if (patientIds[i] == patientId)
    {
      patientExists = true;
      break;
    }
  }

  if (!patientExists)
  {
    cout << "Patient ID does not exist.\n";
    return;
  }

  string date, time;
  cout << "Enter date (YYYY-MM-DD): ";
  cin >> date;
  if (!validateDate(date))
  {
    cout << "Invalid date format.\n";
    return;
  }

  cout << "Enter time (HH:MM): ";
  cin >> time;
  if (!validateTime(time))
  {
    cout << "Invalid time format.\n";
    return;
  }

  if (checkConflict(appointments, numAppointments, date, time))
  {
    cout << "Appointment conflict! Choose a different time.\n";
    return;
  }

  appointments[numAppointments++] = {patientId, date, time};
  cout << "Appointment scheduled successfully.\n";
}

// List all appointments with patient details
void listAppointments(Appointment appointments[], int numAppointments, Patient patients[], int numPatients)
{
  if (numAppointments == 0)
  {
    cout << "No appointments scheduled.\n";
    return;
  }

  cout << "PatientID\tName\t\tDate\t\tTime\tPhone\n";
  cout << "--------------------------------------------------------\n";

  for (int i = 0; i < numAppointments; i++)
  {
    int pid = appointments[i].patientId;
    int patientIndex = -1;
    for (int j = 0; j < numPatients; j++)
    {
      if (patients[j].id == pid)
      {
        patientIndex = j;
        break;
      }
    }

    if (patientIndex != -1)
    {
      cout << pid << "\t\t"
           << patients[patientIndex].firstName << " "
           << patients[patientIndex].lastName << "\t"
           << appointments[i].date << "\t"
           << appointments[i].time << "\t"
           << patients[patientIndex].phone << "\n";
    }
    else
    {
      cout << pid << "\t\tUnknown\t\t"
           << appointments[i].date << "\t"
           << appointments[i].time << "\t"
           << "N/A\n";
    }
  }
}

// Delete an appointment
void deleteAppointment(Appointment appointments[], int &numAppointments)
{
  if (numAppointments == 0)
  {
    cout << "No appointments to delete.\n";
    return;
  }

  int patientId;
  string date;
  cout << "Enter patient ID for appointment to delete: ";
  cin >> patientId;
  cout << "Enter date (YYYY-MM-DD): ";
  cin >> date;

  int idx = -1;
  for (int i = 0; i < numAppointments; i++)
  {
    if (appointments[i].patientId == patientId && appointments[i].date == date)
    {
      idx = i;
      break;
    }
  }

  if (idx == -1)
  {
    cout << "Appointment not found.\n";
    return;
  }

  for (int i = idx; i < numAppointments - 1; i++)
  {
    appointments[i] = appointments[i + 1];
  }
  numAppointments--;
  cout << "Appointment deleted successfully.\n";
}
