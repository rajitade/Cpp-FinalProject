#include <iostream>
#include <fstream>
#include <string>
#include "patient.h"
#include "appointment.h"
#include "file_management.h"
#include "user.h"
#include "doctor.h"
#include "audit.h"

using namespace std;

int main()
{
  // ================= DECLARE ARRAYS =================
  Patient patients[MAX_PATIENTS];
  Appointment appointments[MAX_APPOINTMENTS];
  Doctor doctors[MAX_DOCTORS];

  int numPatients = 0, numAppointments = 0, numDoctors = 0;
  int nextPatientId = 1, nextDoctorId = 1;

  // ================= LOGIN =================
  User currentUser;
  if (!login(currentUser))
  {
    cout << "Access denied. Program terminated.\n";
    return 0;
  }
  cout << "\nWelcome " << currentUser.username
       << " (" << currentUser.role << ")\n";

  // ================= LOAD DATA =================
  loadPatientsFromFile(patients, numPatients);
  loadAppointmentsFromFile(appointments, numAppointments);

  // Load doctors safely
  ifstream din("doctor.dat");
  numDoctors = 0;
  if (din)
  {
    while (numDoctors < MAX_DOCTORS && din >> doctors[numDoctors].id)
    {
      din.ignore(); // skip space
      getline(din, doctors[numDoctors].name, ' ');
      getline(din, doctors[numDoctors].specialization, ' ');
      din >> doctors[numDoctors].phone;
      numDoctors++;
    }
    din.close();
  }

  if (numDoctors > 0)
    nextDoctorId = doctors[numDoctors - 1].id + 1;
  if (numPatients > 0)
    nextPatientId = patients[numPatients - 1].id + 1;

  // ================= MAIN MENU LOOP =================
  int choice;
  do
  {
    cout << "\n\n*******************************************\n";
    cout << "*                                         *\n";
    cout << "*       CLINICAL MANAGEMENT SYSTEM        *\n";
    cout << "*                                         *\n";
    cout << "*******************************************\n\n";
    cout << "1. Add Patient\n";
    cout << "2. List Patients\n";
    cout << "3. Search Patient\n";
    cout << "4. Add Appointment\n";
    cout << "5. List Appointments\n";
    cout << "6. Update Appointment Status\n";
    cout << "7. Daily Appointment Report\n";

    if (currentUser.role == "ADMIN")
    {
      cout << "8. Delete Patient\n";
      cout << "9. Delete Appointment\n";
      cout << "10. Add Doctor\n";
      cout << "11. List Doctors\n";
      cout << "12. Delete Doctor\n";
      cout << "13. Save & Exit\n";
    }
    else
    { // Reception
      cout << "8. Save & Exit\n";
    }

    cout << "Enter your choice: ";
    cin >> choice;

    if (currentUser.role == "ADMIN")
    {
      switch (choice)
      {
      case 1:
        addPatient(patients, numPatients, nextPatientId);
        logAction(currentUser.username, "Added patient ID " + to_string(nextPatientId - 1));
        break;
      case 2:
        listPatients(patients, numPatients);
        break;
      case 3:
        searchPatient(patients, numPatients);
        break;
      case 4:
      {
        int patientIds[MAX_PATIENTS];
        for (int i = 0; i < numPatients; i++)
          patientIds[i] = patients[i].id;
        addAppointment(appointments, numAppointments, numPatients, patientIds, doctors, numDoctors);
        logAction(currentUser.username, "Added appointment ID " + to_string(numAppointments - 1));
        break;
      }
      case 5:
        listAppointments(appointments, numAppointments, patients, numPatients);
        break;
      case 6:
        updateAppointmentStatus(appointments, numAppointments);
        logAction(currentUser.username, "Updated appointment status");
        break;
      case 7:
        dailyReport(appointments, numAppointments, patients, numPatients);
        break;
      case 8:
        deletePatient(patients, numPatients);
        logAction(currentUser.username, "Deleted patient");
        break;
      case 9:
        deleteAppointment(appointments, numAppointments);
        logAction(currentUser.username, "Deleted appointment");
        break;
      case 10:
        addDoctor(doctors, numDoctors, nextDoctorId);
        logAction(currentUser.username, "Added doctor ID " + to_string(nextDoctorId - 1));
        break;
      case 11:
        listDoctors(doctors, numDoctors);
        break;
      case 12:
        deleteDoctor(doctors, numDoctors);
        logAction(currentUser.username, "Deleted doctor");
        break;
      case 13:
      { // Scoped block fixes switch-case variable issue
        savePatientsToFile(patients, numPatients);
        saveAppointmentsToFile(appointments, numAppointments);

        ofstream dout("doctor.dat");
        for (int i = 0; i < numDoctors; i++)
          dout << doctors[i].id << " " << doctors[i].name << " "
               << doctors[i].specialization << " "
               << doctors[i].phone << "\n";
        dout.close();

        cout << "Data saved. Exiting...\n";
        break;
      }
      default:
        cout << "Invalid choice!\n";
      }
    }
    else
    { // RECEPTION
      switch (choice)
      {
      case 1:
        addPatient(patients, numPatients, nextPatientId);
        logAction(currentUser.username, "Added patient ID " + to_string(nextPatientId - 1));
        break;
      case 2:
        listPatients(patients, numPatients);
        break;
      case 3:
        searchPatient(patients, numPatients);
        break;
      case 4:
      {
        int patientIds[MAX_PATIENTS];
        for (int i = 0; i < numPatients; i++)
          patientIds[i] = patients[i].id;
        addAppointment(appointments, numAppointments, numPatients, patientIds, doctors, numDoctors);
        logAction(currentUser.username, "Added appointment ID " + to_string(numAppointments - 1));
        break;
      }
      case 5:
        listAppointments(appointments, numAppointments, patients, numPatients);
        break;
      case 6:
        updateAppointmentStatus(appointments, numAppointments);
        logAction(currentUser.username, "Updated appointment status");
        break;
      case 7:
        dailyReport(appointments, numAppointments, patients, numPatients);
        break;
      case 8:
      { // Scoped block
        savePatientsToFile(patients, numPatients);
        saveAppointmentsToFile(appointments, numAppointments);
        cout << "Data saved. Exiting...\n";
        break;
      }
      default:
        cout << "Invalid choice or permission denied!\n";
      }
    }

  } while ((currentUser.role == "ADMIN" && choice != 13) ||
           (currentUser.role == "RECEPTION" && choice != 8));

  return 0;
}
