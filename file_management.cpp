#include <iostream>
#include <fstream>
#include "file_management.h"
using namespace std;

// Patients
void savePatientsToFile(Patient patients[], int numPatients)
{
  ofstream outfile("patients.dat");
  for (int i = 0; i < numPatients; i++)
  {
    outfile << patients[i].id << " "
            << patients[i].firstName << " "
            << patients[i].lastName << " "
            << patients[i].age << " "
            << patients[i].phone << "\n";
  }
  outfile.close();
}

void loadPatientsFromFile(Patient patients[], int &numPatients)
{
  ifstream infile("patients.dat");
  numPatients = 0;
  while (infile >> patients[numPatients].id >> patients[numPatients].firstName >> patients[numPatients].lastName >> patients[numPatients].age >> patients[numPatients].phone)
  {
    numPatients++;
    if (numPatients >= MAX_PATIENTS)
      break;
  }
  infile.close();
}

// Appointments
void saveAppointmentsToFile(Appointment appointments[], int numAppointments)
{
  ofstream outfile("appointments.dat");
  for (int i = 0; i < numAppointments; i++)
  {
    outfile << appointments[i].patientId << " "
            << appointments[i].date << " "
            << appointments[i].time << "\n";
  }
  outfile.close();
}

void loadAppointmentsFromFile(Appointment appointments[], int &numAppointments)
{
  ifstream infile("appointments.dat");
  numAppointments = 0;
  while (infile >> appointments[numAppointments].patientId >> appointments[numAppointments].date >> appointments[numAppointments].time)
  {
    numAppointments++;
    if (numAppointments >= MAX_APPOINTMENTS)
      break;
  }
  infile.close();
}
