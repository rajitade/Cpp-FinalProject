#include <iostream>
#include <regex>
#include <fstream>
#include "appointment.h"
#include "patient.h"
#include "doctor.h"

using namespace std;

// ======================= VALIDATION FUNCTIONS =======================

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

// ======================= CONFLICT DETECTION =======================

// Check if a doctor has another appointment at the same date/time
bool isConflict(Appointment appointments[], int numAppointments, int doctorId, string date, string time)
{
  for (int i = 0; i < numAppointments; i++)
  {
    if (appointments[i].doctorId == doctorId &&
        appointments[i].date == date &&
        appointments[i].time == time)
    {
      return true;
    }
  }
  return false;
}

// ======================= ADD APPOINTMENT =======================

void addAppointment(Appointment appointments[], int &numAppointments, int numPatients, int patientIds[], Doctor doctors[], int numDoctors)
{
  if (numAppointments >= MAX_APPOINTMENTS)
  {
    cout << "Appointment limit reached.\n";
    return;
  }

  Appointment a;
  a.id = (numAppointments > 0) ? appointments[numAppointments - 1].id + 1 : 1;

  // ---------- SELECT PATIENT ----------
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
  a.patientId = patientId;

  // ---------- SELECT DOCTOR ----------
  if (numDoctors == 0)
  {
    cout << "No doctors available. Please add a doctor first.\n";
    return;
  }

  cout << "Available doctors:\n";
  for (int i = 0; i < numDoctors; i++)
    cout << doctors[i].id << ": " << doctors[i].name
         << " (" << doctors[i].specialization << ")\n";

  int doctorId;
  cout << "Enter doctor ID: ";
  cin >> doctorId;

  bool doctorExists = false;
  for (int i = 0; i < numDoctors; i++)
  {
    if (doctors[i].id == doctorId)
    {
      doctorExists = true;
      break;
    }
  }
  if (!doctorExists)
  {
    cout << "Doctor ID does not exist.\n";
    return;
  }
  a.doctorId = doctorId;

  // ---------- ENTER DATE & TIME ----------
  cin.ignore();
  string date, time;
  cout << "Enter date (YYYY-MM-DD): ";
  getline(cin, date);
  if (!validateDate(date))
  {
    cout << "Invalid date format.\n";
    return;
  }

  cout << "Enter time (HH:MM): ";
  getline(cin, time);
  if (!validateTime(time))
  {
    cout << "Invalid time format.\n";
    return;
  }

  // ---------- CONFLICT CHECK ----------
  if (isConflict(appointments, numAppointments, doctorId, date, time))
  {
    cout << "Conflict! Doctor is already booked at this time.\n";
    return;
  }

  a.date = date;
  a.time = time;
  a.status = "Scheduled"; // Default status

  // Add appointment
  appointments[numAppointments++] = a;

  // Save to file
  ofstream outfile("appointment.dat", ios::app);
  outfile << a.id << " " << a.patientId << " " << a.doctorId << " "
          << a.date << " " << a.time << " " << a.status << "\n";
  outfile.close();

  cout << "Appointment scheduled successfully.\n";
}

// ======================= LIST APPOINTMENTS =======================

void listAppointments(Appointment appointments[], int numAppointments, Patient patients[], int numPatients)
{
  if (numAppointments == 0)
  {
    cout << "No appointments scheduled.\n";
    return;
  }

  cout << "ID\tPatient Name\tDoctorID\tDate\tTime\tStatus\n";
  cout << "---------------------------------------------------------------\n";

  for (int i = 0; i < numAppointments; i++)
  {
    int pid = appointments[i].patientId;
    string patientName = "Unknown";
    for (int j = 0; j < numPatients; j++)
    {
      if (patients[j].id == pid)
      {
        patientName = patients[j].firstName + " " + patients[j].lastName;
        break;
      }
    }

    cout << appointments[i].id << "\t"
         << patientName << "\t"
         << appointments[i].doctorId << "\t\t"
         << appointments[i].date << "\t"
         << appointments[i].time << "\t"
         << appointments[i].status << "\n";
  }
}

// ======================= DELETE APPOINTMENT =======================

void deleteAppointment(Appointment appointments[], int &numAppointments)
{
  if (numAppointments == 0)
  {
    cout << "No appointments to delete.\n";
    return;
  }

  int appointmentId;
  cout << "Enter appointment ID to delete: ";
  cin >> appointmentId;

  int idx = -1;
  for (int i = 0; i < numAppointments; i++)
  {
    if (appointments[i].id == appointmentId)
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
    appointments[i] = appointments[i + 1];

  numAppointments--;
  cout << "Appointment deleted successfully.\n";

  // Rewrite file
  ofstream outfile("appointment.dat");
  for (int i = 0; i < numAppointments; i++)
  {
    outfile << appointments[i].id << " "
            << appointments[i].patientId << " "
            << appointments[i].doctorId << " "
            << appointments[i].date << " "
            << appointments[i].time << " "
            << appointments[i].status << "\n";
  }
  outfile.close();
}

// ======================= UPDATE STATUS =======================

void updateAppointmentStatus(Appointment appointments[], int numAppointments)
{
  if (numAppointments == 0)
  {
    cout << "No appointments available.\n";
    return;
  }

  int appId;
  cout << "Enter appointment ID to update: ";
  cin >> appId;

  int idx = -1;
  for (int i = 0; i < numAppointments; i++)
  {
    if (appointments[i].id == appId)
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

  cout << "Current status: " << appointments[idx].status << endl;
  cout << "Select new status:\n1. Scheduled\n2. Completed\n3. Cancelled\n";
  int choice;
  cin >> choice;

  switch (choice)
  {
  case 1:
    appointments[idx].status = "Scheduled";
    break;
  case 2:
    appointments[idx].status = "Completed";
    break;
  case 3:
    appointments[idx].status = "Cancelled";
    break;
  default:
    cout << "Invalid choice. Status unchanged.\n";
    return;
  }

  // Rewrite file
  ofstream outfile("appointment.dat");
  for (int i = 0; i < numAppointments; i++)
  {
    outfile << appointments[i].id << " "
            << appointments[i].patientId << " "
            << appointments[i].doctorId << " "
            << appointments[i].date << " "
            << appointments[i].time << " "
            << appointments[i].status << "\n";
  }
  outfile.close();

  cout << "Appointment status updated successfully.\n";
}

// ======================= DAILY REPORT =======================

void dailyReport(Appointment appointments[], int numAppointments, Patient patients[], int numPatients)
{
  if (numAppointments == 0)
  {
    cout << "No appointments scheduled.\n";
    return;
  }

  string date;
  cout << "Enter date for report (YYYY-MM-DD): ";
  cin >> date;

  bool found = false;
  cout << "\nAppointments on " << date << ":\n";
  cout << "ID\tPatient Name\tDoctorID\tTime\tStatus\n";
  cout << "---------------------------------------------------------------\n";

  for (int i = 0; i < numAppointments; i++)
  {
    if (appointments[i].date == date)
    {
      string patientName = "Unknown";
      for (int j = 0; j < numPatients; j++)
      {
        if (patients[j].id == appointments[i].patientId)
        {
          patientName = patients[j].firstName + " " + patients[j].lastName;
          break;
        }
      }
      cout << appointments[i].id << "\t"
           << patientName << "\t"
           << appointments[i].doctorId << "\t\t"
           << appointments[i].time << "\t"
           << appointments[i].status << "\n";
      found = true;
    }
  }

  if (!found)
    cout << "No appointments found on this date.\n";
}
