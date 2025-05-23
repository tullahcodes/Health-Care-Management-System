#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PATIENT_FILE "patients.dat"
#define DOCTOR_FILE "doctors.dat"
#define APPOINTMENT_FILE "appointments.dat"


// Structure definitions
typedef struct {
    int id;
    char name[100];
    int age;
    char gender;
    char disease[100];
} Patient;

typedef struct {
    int id;
    char name[100];
    char specialty[100];
    int experience;
} Doctor;

typedef struct {
    int id;
    int patientId;
    char patientName[100];
    int doctorId;
    char doctorName[100];
    char date[20];
} Appointment;

// Function prototypes
void mainMenu();
void patientManagement();
void doctorManagement();
void appointmentScheduling();
void billingSystem();
void addPatient();
void viewPatients();
void editPatient();
void deletePatient();
void addDoctor();
void viewDoctors();
void editDoctor();
void deleteDoctor();
void scheduleAppointment();
void viewAppointments();
void cancelAppointment();
void generateBill();
void viewBills();

// Global variables
Patient patients[100];
Doctor doctors[50];
Appointment appointments[100];
int patientCount = 0;
int doctorCount = 0;
int appointmentCount = 0;

int main() {
    int choice;
    do {
        mainMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: patientManagement(); break;
            case 2: doctorManagement(); break;
            case 3: appointmentScheduling(); break;
            case 4: billingSystem(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n"); break;
        }
    } while (choice != 5);

    return 0;
}

void mainMenu() {
    printf("\n====================================\n");
    printf("|      Hospital Management System   |\n");
    printf("====================================\n");
    printf("|  1. Patient Management            |\n");
    printf("|  2. Doctor Management             |\n");
    printf("|  3. Appointment Scheduling        |\n");
    printf("|  4. Billing                       |\n");
    printf("|  5. Exit                          |\n");
    printf("====================================\n");
    printf("Enter your choice: ");
}

// Patient Management Functions
void patientManagement() {
    int choice;
    printf("\n--- Patient Management ---\n");
    printf("1. Add Patient\n");
    printf("2. View Patients\n");
    printf("3. Edit Patient\n");
    printf("4. Delete Patient\n");
    printf("5. Back to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: addPatient(); break;
        case 2: viewPatients(); break;
        case 3: editPatient(); break;
        case 4: deletePatient(); break;
        case 5: return;
        default: printf("Invalid choice!\n"); break;
    }
}

void addPatient() {
    printf("Enter Patient ID: ");
    scanf("%d", &patients[patientCount].id);
    getchar();  // Clear newline after reading int

    printf("Enter Patient Name: ");
    fgets(patients[patientCount].name, sizeof(patients[patientCount].name), stdin);
    patients[patientCount].name[strcspn(patients[patientCount].name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &patients[patientCount].age);

    printf("Enter Gender (M/F): ");
    scanf(" %c", &patients[patientCount].gender);
    getchar();  // <-- This is the crucial line to clear leftover newline

    printf("Enter Disease: ");
    fgets(patients[patientCount].disease, sizeof(patients[patientCount].disease), stdin);
    patients[patientCount].disease[strcspn(patients[patientCount].disease, "\n")] = '\0';

    // Save patient data to file
    FILE *file = fopen("patients.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%d,%s,%d,%c,%s\n",
            patients[patientCount].id,
            patients[patientCount].name,
            patients[patientCount].age,
            patients[patientCount].gender,
            patients[patientCount].disease);

    fclose(file);

    patientCount++;
    printf("Patient added successfully!\n");
}


void viewPatients() {
    FILE *file = fopen("patients.txt", "r"); // Open file in read mode
    if (file == NULL) {
        printf("No existing patient data found. Starting fresh.\n");
        return;
    }

    // Check if file is empty
    int ch = fgetc(file);
    if (ch == EOF) {
        printf("Mmmmmmh seems like you have no registered patients yet.\n");
        fclose(file);
        return;
    }
    rewind(file); // Go back to the beginning of the file

    patientCount = 0; // Reset patientCount before loading

    // Read patient data from the file
    while (fscanf(file, "%d,%99[^,],%d,%c,%99[^\n]\n",
                  &patients[patientCount].id,
                  patients[patientCount].name,
                  &patients[patientCount].age,
                  &patients[patientCount].gender,
                  patients[patientCount].disease) == 5) {
        patientCount++;
                  }

    fclose(file); // Close the file
    printf("Patient data loaded successfully!\n");

    for (int i = 0; i < patientCount; i++) {
        printf("\nID: %d\n", patients[i].id);
        printf("Name: %s\n", patients[i].name);
        printf("Age: %d\n", patients[i].age);
        printf("Gender: %c\n", patients[i].gender);
        printf("Disease: %s\n", patients[i].disease);
    }
}


void editPatient() {
    int id, found = -1;
    printf("Enter Patient ID to edit: ");
    scanf("%d", &id);
    getchar(); // Clear newline after reading int

    // Load existing patients from the file
    FILE *file = fopen("patients.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Patient patients[100]; // Assuming a maximum of 100 patients
    int patientCount = 0;

    // Read patients from the file
    while (fscanf(file, "%d,%99[^,],%d,%c,%99[^\n]\n",
                  &patients[patientCount].id,
                  patients[patientCount].name,
   
    //last quarter
    fprintf(file, "%d,%d,%s,%d,%s,%s\n",
        appointments[appointmentCount].id,
        appointments[appointmentCount].patientId,
        patientName,
        appointments[appointmentCount].doctorId,
        doctorName,
        appointments[appointmentCount].date);

fclose(file);
appointmentCount++;
printf("Appointment scheduled successfully!\n");
}


void viewAppointments() {
FILE *file = fopen("appointments.txt", "r");
if (file == NULL) {
    printf("No appointment data found.\n");
    return;
}

int id, patientId, doctorId;
char patientName[100], doctorName[100], date[20];

printf("\n--- List of Appointments ---\n");

while (fscanf(file, "%d,%d,%99[^,],%d,%99[^,],%19[^\n]\n",
              &id, &patientId, patientName, &doctorId, doctorName, date) == 6) {
    printf("\nAppointment ID: %d\n", id);
    printf("Patient ID: %d\n", patientId);
    printf("Patient Name: %s\n", patientName);
    printf("Doctor ID: %d\n", doctorId);
    printf("Doctor Name: %s\n", doctorName);
    printf("Date: %s\n", date);
              }

fclose(file);
}


void cancelAppointment() {
int id, found = 0;
printf("Enter Appointment ID to cancel: ");
scanf("%d", &id);

FILE *file = fopen("appointments.txt", "r");
if (file == NULL) {
    printf("No appointment data found.\n");
    return;
}

// Temporary array to store remaining appointments
Appointment tempAppointments[100];
int tempCount = 0;

int apptId, patientId, doctorId;
char patientName[100], doctorName[100], date[20];

while (fscanf(file, "%d,%d,%99[^,],%d,%99[^,],%19[^\n]\n",
              &apptId, &patientId, patientName, &doctorId, doctorName, date) == 6) {
    if (apptId == id) {
        found = 1;
        continue; // Skip this appointment (delete)
    }
    tempAppointments[tempCount].id = apptId;
    tempAppointments[tempCount].patientId = patientId;
    strcpy(tempAppointments[tempCount].patientName, patientName);
    tempAppointments[tempCount].doctorId = doctorId;
    strcpy(tempAppointments[tempCount].doctorName, doctorName);
    strcpy(tempAppointments[tempCount].date, date);
    tempCount++;
              }

fclose(file);

if (!found) {
    printf("Appointment not found!\n");
    return;
}

// Rewrite the file with remaining appointments
file = fopen("appointments.txt", "w");
if (file == NULL) {
    printf("Error writing to file.\n");
    return;
}

for (int i = 0; i < tempCount; i++) {
    fprintf(file, "%d,%d,%s,%d,%s,%s\n",
            tempAppointments[i].id,
            tempAppointments[i].patientId,
            tempAppointments[i].patientName,
            tempAppointments[i].doctorId,
            tempAppointments[i].doctorName,
            tempAppointments[i].date);
}

fclose(file);
printf("Appointment canceled successfully!\n");
}


// Billing System Functions
void billingSystem() {
int choice;
printf("\n--- Billing System ---\n");
printf("1. Generate Bill\n");
printf("2. View Bills\n");
printf("3. Back to Main Menu\n");
printf("Enter your choice: ");
scanf("%d", &choice);

switch (choice) {
    case 1: generateBill(); break;
    case 2: viewBills(); break;
    case 3: return;
    default: printf("Invalid choice!\n"); break;
}
}

void generateBill() {
int patientId, found = -1;
float consultationFee, treatmentCharges, totalAmount;
Patient tempPatients[100];
int tempPatientCount = 0;

// Load patients from file
FILE *file = fopen("patients.txt", "r");
if (file == NULL) {
    printf("Error: Could not open patients.txt\n");
    return;
}

while (fscanf(file, "%d,%99[^,],%d,%c,%99[^\n]\n",
              &tempPatients[tempPatientCount].id,
              tempPatients[tempPatientCount].name,
              &tempPatients[tempPatientCount].age,
              &tempPatients[tempPatientCount].gender,
              tempPatients[tempPatientCount].disease) == 5) {
    tempPatientCount++;
}
fclose(file);

// Ask for patient ID
printf("Enter Patient ID for billing: ");
scanf("%d", &patientId);

// Check if the patient exists
for (int i = 0; i < tempPatientCount; i++) {
    if (tempPatients[i].id == patientId) {
        found = i;
        break;
    }
}

if (found != -1) {
    printf("Enter Consultation Fee: ");
    scanf("%f", &consultationFee);
    printf("Enter Treatment Charges: ");
    scanf("%f", &treatmentCharges);

    totalAmount = consultationFee + treatmentCharges;

    // Print Bill
    printf("\n--- Bill Details ---\n");
    printf("Patient ID: %d\n", tempPatients[found].id);
    printf("Patient Name: %s\n", tempPatients[found].name);
    printf("Consultation Fee: %.2f\n", consultationFee);
    printf("Treatment Charges: %.2f\n", treatmentCharges);
    printf("Total Amount: %.2f\n", totalAmount);

    // Save to file
    FILE *billFile = fopen("bills.txt", "a");
    if (billFile == NULL) {
        printf("Error saving bill.\n");
        return;
    }

    fprintf(billFile, "%d,%s,%.2f,%.2f,%.2f\n",
            tempPatients[found].id,
            tempPatients[found].name,
            consultationFee,
            treatmentCharges,
            totalAmount);
    fclose(billFile);

    printf("Bill saved successfully.\n");
} else {
    printf("Error: Patient with ID %d does not exist.\n", patientId);
}
}


void viewBills() {
FILE *file = fopen("bills.txt", "r");
if (file == NULL) {
    printf("No billing records found.\n");
    return;
}

int patientId;
char name[100];
float consultationFee, treatmentCharges, totalAmount;

printf("\n--- All Bills ---\n");
while (fscanf(file, "%d,%99[^,],%f,%f,%f\n",
              &patientId, name,
              &consultationFee,
              &treatmentCharges,
              &totalAmount) == 5) {
    printf("\nPatient ID: %d\n", patientId);
    printf("Patient Name: %s\n", name);
    printf("Consultation Fee: %.2f\n", consultationFee);
    printf("Treatment Charges: %.2f\n", treatmentCharges);
    printf("Total Amount: %.2f\n", totalAmount);
}

fclose(file);
}
=======
                  &patients[patientCount].age,
                  &patients[patientCount].gender,
                  patients[patientCount].disease) != EOF) {
        patientCount++;
    }
    fclose(file);

    // Find the patient to edit
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // Update patient details
        printf("Enter new Name: ");
        fgets(patients[found].name, sizeof(patients[found].name), stdin);
        patients[found].name[strcspn(patients[found].name, "\n")] = '\0';

        printf("Enter new Age: ");
        scanf("%d", &patients[found].age);

        printf("Enter new Gender (M/F): ");
        scanf(" %c", &patients[found].gender);
        getchar(); // Clear newline

        printf("Enter new Disease: ");
        fgets(patients[found].disease, sizeof(patients[found].disease), stdin);
        patients[found].disease[strcspn(patients[found].disease, "\n")] = '\0';

        printf("Patient updated successfully!\n");

        // Write updated patients back to the file
        file = fopen("patients.txt", "w");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }

        for (int i = 0; i < patientCount; i++) {
            fprintf(file, "%d,%s,%d,%c,%s\n",
                    patients[i].id,
                    patients[i].name,
                    patients[i].age,
                    patients[i].gender,
                    patients[i].disease);
        }
        fclose(file);
    } else {
        printf("Patient not found!\n");
    }
}


void deletePatient() {
    int id, found = 0;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    FILE *file = fopen("patients.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Patient patients[100]; // Temporary array
    int patientCount = 0;

    // Read all patients from file
    while (fscanf(file, "%d,%99[^,],%d,%c,%99[^\n]\n",
                  &patients[patientCount].id,
                  patients[patientCount].name,
                  &patients[patientCount].age,
                  &patients[patientCount].gender,
                  patients[patientCount].disease) == 5) {
        patientCount++;
                  }
    fclose(file);

    // Check for patient with matching ID
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            found = 1;
            // Shift all elements after the deleted one
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patientCount--;
            break;
        }
    }

    if (!found) {
        printf("Patient with ID %d not found.\n", id);
        return;
    }

    // Write updated data back to file
    file = fopen("patients.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "%d,%s,%d,%c,%s\n",
                patients[i].id,
                patients[i].name,
                patients[i].age,
                patients[i].gender,
                patients[i].disease);
    }
    fclose(file);

    printf("Patient with ID %d deleted successfully.\n", id);
}

// Doctor Management Functions
void doctorManagement() {
    int choice;
    printf("\n--- Doctor Management ---\n");
    printf("1. Add Doctor\n");
    printf("2. View Doctors\n");
    printf("3. Edit Doctor\n");
    printf("4. Delete Doctor\n");
    printf("5. Back to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: addDoctor(); break;
        case 2: viewDoctors(); break;
        case 3: editDoctor(); break;
        case 4: deleteDoctor(); break;
        case 5: return;
        default: printf("Invalid choice!\n"); break;
    }
}

void addDoctor() {
    printf("Enter Doctor ID: ");
    scanf("%d", &doctors[doctorCount].id);
    getchar(); // Clear the newline left by scanf

    printf("Enter Doctor Name: ");
    fgets(doctors[doctorCount].name, sizeof(doctors[doctorCount].name), stdin);
    doctors[doctorCount].name[strcspn(doctors[doctorCount].name, "\n")] = '\0'; // Remove newline

    printf("Enter Specialty: ");
    fgets(doctors[doctorCount].specialty, sizeof(doctors[doctorCount].specialty), stdin);
    doctors[doctorCount].specialty[strcspn(doctors[doctorCount].specialty, "\n")] = '\0';

    printf("Enter Experience (in years): ");
    scanf("%d", &doctors[doctorCount].experience);

    // Save to file
    FILE *file = fopen("doctors.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d,%s,%s,%d\n",
                doctors[doctorCount].id,
                doctors[doctorCount].name,
                doctors[doctorCount].specialty,
                doctors[doctorCount].experience);
        fclose(file);
    }

    doctorCount++;
    printf("Doctor added successfully!\n");
}


void viewDoctors() {
    FILE *file = fopen("doctors.txt", "r");
    if (file == NULL) {
        printf("No existing doctor data found.\n");
        return;
    }

    Doctor doctor;
    int found = 0;

    while (fscanf(file, "%d,%99[^,],%99[^,],%d\n",
                  &doctor.id,
                  doctor.name,
                  doctor.specialty,
                  &doctor.experience) == 4) {
        found = 1;
        printf("\nID: %d\n", doctor.id);
        printf("Name: %s\n", doctor.name);
        printf("Specialty: %s\n", doctor.specialty);
        printf("Experience: %d years\n", doctor.experience);
                  }

    fclose(file);

    if (!found) {
        printf("Doctor file is empty.\n");
    }
}


void editDoctor() {
    int id, found = -1;
    Doctor doctors[100];  // Temporary array for file data
    int count = 0;

    FILE *file = fopen("doctors.txt", "r");
    if (file == NULL) {
        printf("Error opening doctors file.\n");
        return;
    }

    // Read doctor data from file
    while (fscanf(file, "%d,%99[^,],%99[^,],%d\n",
                  &doctors[count].id,
                  doctors[count].name,
                  doctors[count].specialty,
                  &doctors[count].experience) == 4) {
        count++;
    }
    fclose(file);

    // Ask user for the ID to edit
    printf("Enter Doctor ID to edit: ");
    scanf("%d", &id);

    // Search for doctor by ID
    for (int i = 0; i < count; i++) {
        if (doctors[i].id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // Edit doctor data
        printf("Enter new Name: ");
        getchar(); // Clear newline left in buffer
        fgets(doctors[found].name, sizeof(doctors[found].name), stdin);
        doctors[found].name[strcspn(doctors[found].name, "\n")] = '\0'; // Remove newline

        printf("Enter new Specialty: ");
        fgets(doctors[found].specialty, sizeof(doctors[found].specialty), stdin);
        doctors[found].specialty[strcspn(doctors[found].specialty, "\n")] = '\0';

        printf("Enter new Experience (in years): ");
        scanf("%d", &doctors[found].experience);

        // Save back to file
        file = fopen("doctors.txt", "w");
        if (file == NULL) {
            printf("Error writing to file.\n");
            return;
        }

        for (int i = 0; i < count; i++) {
            fprintf(file, "%d,%s,%s,%d\n",
                    doctors[i].id,
                    doctors[i].name,
                    doctors[i].specialty,
                    doctors[i].experience);
        }

        fclose(file);
        printf("Doctor updated successfully!\n");

    } else {
        printf("Doctor not found!\n");
    }
}


void deleteDoctor() {
    int id, found = -1;
    Doctor doctors[100];
    int count = 0;

    FILE *file = fopen("doctors.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Load doctors from file
    while (fscanf(file, "%d,%99[^,],%99[^,],%d\n",
                  &doctors[count].id,
                  doctors[count].name,
                  doctors[count].specialty,
                  &doctors[count].experience) == 4) {
        count++;
                  }
    fclose(file);

    printf("Enter Doctor ID to delete: ");
    scanf("%d", &id);

    // Search for doctor to delete
    for (int i = 0; i < count; i++) {
        if (doctors[i].id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // Shift the rest to overwrite the deleted doctor
        for (int i = found; i < count - 1; i++) {
            doctors[i] = doctors[i + 1];
        }
        count--;

        // Write updated list to file
        file = fopen("doctors.txt", "w");
        if (file == NULL) {
            printf("Error writing to file.\n");
            return;
        }

        for (int i = 0; i < count; i++) {
            fprintf(file, "%d,%s,%s,%d\n",
                    doctors[i].id,
                    doctors[i].name,
                    doctors[i].specialty,
                    doctors[i].experience);
        }

        fclose(file);
        printf("Doctor deleted successfully!\n");
    } else {
        printf("Doctor not found!\n");
    }
}


// Appointment Scheduling Functions
void appointmentScheduling() {
    int choice;
    printf("\n--- Appointment Scheduling ---\n");
    printf("1. Schedule Appointment\n");
    printf("2. View Appointments\n");
    printf("3. Cancel Appointment\n");
    printf("4. Back to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: scheduleAppointment(); break;
        case 2: viewAppointments(); break;
        case 3: cancelAppointment(); break;
        case 4: return;
        default: printf("Invalid choice!\n"); break;
    }
}

void scheduleAppointment() {
    // Load patients from file
    FILE *pFile = fopen("patients.txt", "r");
    patientCount = 0;
    if (pFile != NULL) {
        while (fscanf(pFile, "%d,%99[^,],%d,%c,%99[^\n]\n",
                      &patients[patientCount].id,
                      patients[patientCount].name,
                      &patients[patientCount].age,
                      &patients[patientCount].gender,
                      patients[patientCount].disease) == 5) {
            patientCount++;
        }
        fclose(pFile);
    }

    // Load doctors from file
    FILE *dFile = fopen("doctors.txt", "r");
    doctorCount = 0;
    if (dFile != NULL) {
        while (fscanf(dFile, "%d,%99[^,],%99[^,],%d\n",
                      &doctors[doctorCount].id,
                      doctors[doctorCount].name,
                      doctors[doctorCount].specialty,
                      &doctors[doctorCount].experience) == 4) {
            doctorCount++;
        }
        fclose(dFile);
    }

    // Input appointment details
    printf("Enter Appointment ID: ");
    scanf("%d", &appointments[appointmentCount].id);

    // Validate patient ID
    int patientId, patientFound = 0;
    char patientName[100];
    do {
        printf("Enter valid Patient ID: ");
        scanf("%d", &patientId);
        for (int i = 0; i < patientCount; i++) {
            if (patients[i].id == patientId) {
                patientFound = 1;
                strcpy(patientName, patients[i].name);
                break;
            }
        }
        if (!patientFound) {
            printf("Invalid Patient ID. Please try again.\n");
        }
    } while (!patientFound);
    appointments[appointmentCount].patientId = patientId;

    // Validate doctor ID
    int doctorId, doctorFound = 0;
    char doctorName[100];
    do {
        printf("Enter valid Doctor ID: ");
        scanf("%d", &doctorId);
        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i].id == doctorId) {
                doctorFound = 1;
                strcpy(doctorName, doctors[i].name);
                break;
            }
        }
        if (!doctorFound) {
            printf("Invalid Doctor ID. Please try again.\n");
        }
    } while (!doctorFound);
    appointments[appointmentCount].doctorId = doctorId;

    // Date input
    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%s", appointments[appointmentCount].date);

    // Write to file
    FILE *file = fopen("appointments.txt", "a");
    if (file == NULL) {
        printf("Error opening appointments.txt for writing.\n");
        return;
    }
