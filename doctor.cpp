#include <iostream>
#include <fstream>
#include "doctor.h"
using namespace std;

// Add a new doctor
void addDoctor(Doctor doctors[], int &numDoctors, int &nextDoctorId)
{
  if (numDoctors >= MAX_DOCTORS)
  {
    cout << "Doctor list full!\n";
    return;
  }

  Doctor d;
  d.id = nextDoctorId++;

  cout << "Enter doctor name: ";
  cin.ignore();
  getline(cin, d.name);

  cout << "Enter specialization: ";
  getline(cin, d.specialization);

  cout << "Enter phone number: ";
  cin >> d.phone;

  doctors[numDoctors++] = d;

  // Save to file
  ofstream outfile("doctor.dat", ios::app);
  outfile << d.id << " " << d.name << " " << d.specialization << " " << d.phone << "\n";
  outfile.close();

  cout << "Doctor added successfully!\n";
}

// List all doctors
void listDoctors(Doctor doctors[], int numDoctors)
{
  if (numDoctors == 0)
  {
    cout << "No doctors available.\n";
    return;
  }

  cout << "ID\tName\tSpecialization\tPhone\n";
  cout << "----------------------------------------\n";
  for (int i = 0; i < numDoctors; i++)
    cout << doctors[i].id << "\t"
         << doctors[i].name << "\t"
         << doctors[i].specialization << "\t"
         << doctors[i].phone << "\n";
}

// Delete a doctor
void deleteDoctor(Doctor doctors[], int &numDoctors)
{
  if (numDoctors == 0)
  {
    cout << "No doctors to delete.\n";
    return;
  }

  int id;
  cout << "Enter doctor ID to delete: ";
  cin >> id;

  int idx = -1;
  for (int i = 0; i < numDoctors; i++)
  {
    if (doctors[i].id == id)
    {
      idx = i;
      break;
    }
  }

  if (idx == -1)
  {
    cout << "Doctor not found.\n";
    return;
  }

  for (int i = idx; i < numDoctors - 1; i++)
    doctors[i] = doctors[i + 1];

  numDoctors--;

  // Rewrite file
  ofstream outfile("doctor.dat");
  for (int i = 0; i < numDoctors; i++)
    outfile << doctors[i].id << " " << doctors[i].name << " "
            << doctors[i].specialization << " " << doctors[i].phone << "\n";
  outfile.close();

  cout << "Doctor deleted successfully!\n";
}
