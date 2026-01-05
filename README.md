# Clinical Management System (CMS)

## Project Overview

The Clinical Management System (CMS) is a console-based procedural application designed to manage clinic operations efficiently.  
Developed in C++, the system uses structures, arrays, file handling, and procedural functions to manage patient records, appointments, doctors, and audit logging.  
It is suitable for small clinics where simplicity and affordability are essential.

## Features

- **User Login:** Admin and Reception roles with different permissions.
- **Patient Management:** Add, list, search, and delete patients.
- **Appointment Management:** Schedule appointments, prevent conflicts, update status, and list appointments with patient and doctor details.
- **Doctor Management:** Add, list, and delete doctors.
- **Reports & Logging:** Daily appointment report and audit logging of system actions.

## Setup & Run

1. Compile the program:

```bash
g++ main.cpp patient.cpp appointment.cpp doctor.cpp file_management.cpp user.cpp audit.cpp -o CMS
```

## Run the program:

./CMS

## Login credentials (example):

Admin: Username: admin / Password: admin123

Reception: Username: reception / Password: recep123

## Notes

All data is stored in .dat files for persistence.

Admin has full access, Reception has limited access.
