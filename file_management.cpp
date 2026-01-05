#include <iostream>
#include <fstream>
#include "file_management.h"
using namespace std;

// ======================= PATIENTS =======================

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

// ======================= APPOINTMENTS =======================

void saveAppointmentsToFile(Appointment appointments[], int numAppointments)
{
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

void loadAppointmentsFromFile(Appointment appointments[], int &numAppointments)
{
  ifstream infile("appointment.dat");
  numAppointments = 0;
  while (infile >> appointments[numAppointments].id >> appointments[numAppointments].patientId >> appointments[numAppointments].doctorId >> appointments[numAppointments].date >> appointments[numAppointments].time >> appointments[numAppointments].status)
  {
    numAppointments++;
    if (numAppointments >= MAX_APPOINTMENTS)
      break;
  }
  infile.close();
}

// ======================= DOCTORS =======================

void saveDoctorsToFile(Doctor doctors[], int numDoctors)
{
  ofstream outfile("doctor.dat");
  for (int i = 0; i < numDoctors; i++)
  {
    outfile << doctors[i].id << " "
            << doctors[i].name << " "
            << doctors[i].specialization << " "
            << doctors[i].phone << "\n";
  }
  outfile.close();
}

void loadDoctorsFromFile(Doctor doctors[], int &numDoctors)
{
  ifstream infile("doctor.dat");
  numDoctors = 0;
  while (infile >> doctors[numDoctors].id)
  {
    infile.ignore(); // skip space
    getline(infile, doctors[numDoctors].name, ' ');
    getline(infile, doctors[numDoctors].specialization, ' ');
    infile >> doctors[numDoctors].phone;
    numDoctors++;
    if (numDoctors >= MAX_DOCTORS)
      break;
  }
  infile.close();
}
