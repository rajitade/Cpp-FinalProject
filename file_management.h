#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include "patient.h"
#include "appointment.h"
#include "doctor.h" // NEW: include doctor struct

// ======================= PATIENTS =======================
void savePatientsToFile(Patient patients[], int numPatients);
void loadPatientsFromFile(Patient patients[], int &numPatients);

// ======================= APPOINTMENTS =======================
void saveAppointmentsToFile(Appointment appointments[], int numAppointments);
void loadAppointmentsFromFile(Appointment appointments[], int &numAppointments);

// ======================= DOCTORS =======================
void saveDoctorsToFile(Doctor doctors[], int numDoctors);
void loadDoctorsFromFile(Doctor doctors[], int &numDoctors);

#endif
