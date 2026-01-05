#include <iostream>
#include "patient.h"
#include "audit.h" // For logging actions
using namespace std;

void addPatient(Patient patients[], int &numPatients, int &nextId)
{
  if (numPatients >= MAX_PATIENTS)
  {
    cout << "Patient limit reached.\n";
    return;
  }

  Patient p;
  p.id = nextId++;
  cout << "Enter first name: ";
  cin >> p.firstName;
  cout << "Enter last name: ";
  cin >> p.lastName;
  cout << "Enter age: ";
  cin >> p.age;
  cout << "Enter phone number: ";
  cin >> p.phone;

  patients[numPatients++] = p;
  cout << "Patient added successfully. ID: " << p.id << "\n";

  // Log action
  logAction("SYSTEM", "Added patient ID " + to_string(p.id));
}

void listPatients(Patient patients[], int numPatients)
{
  if (numPatients == 0)
  {
    cout << "No patients registered.\n";
    return;
  }
  cout << "ID\tName\t\tAge\tPhone\n";
  cout << "--------------------------------------\n";
  for (int i = 0; i < numPatients; i++)
  {
    cout << patients[i].id << "\t"
         << patients[i].firstName << " " << patients[i].lastName
         << "\t" << patients[i].age
         << "\t" << patients[i].phone << "\n";
  }
}

int findPatientById(Patient patients[], int numPatients, int id)
{
  for (int i = 0; i < numPatients; i++)
  {
    if (patients[i].id == id)
      return i;
  }
  return -1;
}

void searchPatient(Patient patients[], int numPatients)
{
  if (numPatients == 0)
  {
    cout << "No patients registered.\n";
    return;
  }
  int choice;
  cout << "Search by:\n1. ID\n2. Name\nChoice: ";
  cin >> choice;
  if (choice == 1)
  {
    int id;
    cout << "Enter patient ID: ";
    cin >> id;
    int idx = findPatientById(patients, numPatients, id);
    if (idx != -1)
    {
      cout << "Patient Found: "
           << patients[idx].firstName << " "
           << patients[idx].lastName << "\n";
    }
    else
      cout << "Patient not found.\n";
  }
  else if (choice == 2)
  {
    string name;
    cout << "Enter first or last name: ";
    cin >> name;
    bool found = false;
    for (int i = 0; i < numPatients; i++)
    {
      if (patients[i].firstName == name || patients[i].lastName == name)
      {
        cout << "ID: " << patients[i].id
             << " Name: " << patients[i].firstName << " " << patients[i].lastName
             << " Age: " << patients[i].age
             << " Phone: " << patients[i].phone << "\n";
        found = true;
      }
    }
    if (!found)
      cout << "No patients found with that name.\n";
  }
  else
  {
    cout << "Invalid choice.\n";
  }
}

void deletePatient(Patient patients[], int &numPatients)
{
  if (numPatients == 0)
  {
    cout << "No patients to delete.\n";
    return;
  }
  int id;
  cout << "Enter patient ID to delete: ";
  cin >> id;
  int idx = findPatientById(patients, numPatients, id);
  if (idx == -1)
  {
    cout << "Patient not found.\n";
    return;
  }
  for (int i = idx; i < numPatients - 1; i++)
  {
    patients[i] = patients[i + 1];
  }
  numPatients--;
  cout << "Patient deleted successfully.\n";

  // Log action
  logAction("SYSTEM", "Deleted patient ID " + to_string(id));
}
