#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include "patient.h"
#include "appointment.h"

void savePatientsToFile(Patient patients[], int numPatients);
void loadPatientsFromFile(Patient patients[], int &numPatients);

void saveAppointmentsToFile(Appointment appointments[], int numAppointments);
void loadAppointmentsFromFile(Appointment appointments[], int &numAppointments);

#endif
