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
