#include <iostream>
#include "patient.h"
#include "appointment.h"
#include "file_management.h"
using namespace std;

int main()
{
  Patient patients[MAX_PATIENTS];
  Appointment appointments[MAX_APPOINTMENTS];
  int numPatients = 0, numAppointments = 0;
  int nextPatientId = 1;

  loadPatientsFromFile(patients, numPatients);
  loadAppointmentsFromFile(appointments, numAppointments);
  if (numPatients > 0)
    nextPatientId = patients[numPatients - 1].id + 1;

  int choice;
  do
  {
    cout << "\n--- Clinical Management System ---\n";
    cout << "1. Add Patient\n";
    cout << "2. List Patients\n";
    cout << "3. Search Patient\n";
    cout << "4. Delete Patient\n";
    cout << "5. Add Appointment\n";
    cout << "6. List Appointments\n";
    cout << "7. Delete Appointment\n";
    cout << "8. Save & Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      addPatient(patients, numPatients, nextPatientId);
      break;
    case 2:
      listPatients(patients, numPatients);
      break;
    case 3:
      searchPatient(patients, numPatients);
      break;
    case 4:
      deletePatient(patients, numPatients);
      break;
    case 5:
    {
      int patientIds[MAX_PATIENTS];
      for (int i = 0; i < numPatients; i++)
        patientIds[i] = patients[i].id;
      addAppointment(appointments, numAppointments, numPatients, patientIds);
      break;
    }
    case 6:
      listAppointments(appointments, numAppointments, patients, numPatients);
      break;

    case 7:
      deleteAppointment(appointments, numAppointments);
      break;
    case 8:
      savePatientsToFile(patients, numPatients);
      saveAppointmentsToFile(appointments, numAppointments);
      cout << "Data saved. Exiting.\n";
      break;
    default:
      cout << "Invalid choice!\n";
    }
  } while (choice != 8);

  return 0;
}
