#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
UserId=Moinul
Password=Moinul909
*/

// Define login credentials
#define USER_ID "Moinul"
#define PASSWORD "Moinul909"

// Patient structure
typedef struct Patient {
    int patientId;      // Unique ID for each patient
    char name[50];
    int age;
    char disease[50];
    struct Patient* next;  // Pointer to the next patient in the linked list
} Patient;

// Function to create a new patient
Patient* createPatient(int patientId, char* name, int age, char* disease) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    newPatient->patientId = patientId;  // Assign unique ID
    strcpy(newPatient->name, name);
    newPatient->age = age;
    strcpy(newPatient->disease, disease);
    newPatient->next = NULL;
    return newPatient;
}

// Function to add a patient to the linked list based on arrival time
void addPatient(Patient** head, int* patientIdCounter, char* name, int age, char* disease) {
    Patient* newPatient = createPatient(*patientIdCounter, name, age, disease);
    if (*head == NULL) {
        *head = newPatient;
    } else {
        Patient* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPatient;  // Add new patient to the end of the list
    }
    (*patientIdCounter)++;  // Increment the patient ID counter for the next patient
    printf("Patient %s added successfully with ID %d!\n", name, newPatient->patientId);
}

// Function to remove a patient from the linked list
void removePatient(Patient** head, int patientId) {
    Patient* temp = *head;
    Patient* prev = NULL;

    // Check if the patient to be removed is the head
    if (temp != NULL && temp->patientId == patientId) {
        *head = temp->next;  // Change head
        free(temp);  // Free the old head
        printf("Patient with ID %d removed successfully!\n", patientId);
        return;
    }

    // Search for the patient to be removed
    while (temp != NULL && temp->patientId != patientId) {
        prev = temp;
        temp = temp->next;
    }

    // If the patient was not found
    if (temp == NULL) {
        printf("Patient with ID %d not found!\n", patientId);
        return;
    }

    // Unlink the patient from the list
    prev->next = temp->next;
    free(temp);  // Free the memory
    printf("Patient with ID %d removed successfully!\n", patientId);
}

// Function to search for a patient by ID
void searchPatient(Patient* head, int patientId) {
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->patientId == patientId) {
            printf("Patient Found: \n");
            printf("ID: %d\n", temp->patientId);
            printf("Name: %s\n", temp->name);
            printf("Age: %d\n", temp->age);
            printf("Disease: %s\n", temp->disease);
            return;
        }
        temp = temp->next;
    }
    printf("Patient with ID %d not found!\n", patientId);
}

// Function to display all patients
void displayPatients(Patient* head) {
    if (head == NULL) {
        printf("No patients in the system.\n");
        return;
    }

    Patient* temp = head;
    printf("Patients in the system:\n");
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Age: %d, Disease: %s\n", temp->patientId, temp->name, temp->age, temp->disease);
        temp = temp->next;
    }
}

// Function to verify login credentials
int login() {
    char inputUserId[50];
    char inputPassword[50];

    printf("Enter User ID: ");
    scanf("%s", inputUserId);

    printf("Enter Password: ");
    scanf("%s", inputPassword);

    // Check if the entered credentials match the predefined credentials
    if (strcmp(inputUserId, USER_ID) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Login successful!\n\n");
        return 1;  // Return 1 for successful login
    } else {
        printf("Invalid User ID or Password.\n");
        return 0;  // Return 0 for failed login
    }
}

// Main function to demonstrate the Hospital Management System
int main() {
    // Login mechanism
    if (login()) {
        Patient* head = NULL;  // Head of the linked list
        int choice;
        char name[50], disease[50];
        int age;
        int patientIdCounter = 1;  // Counter for patient IDs

        while (1) {
            printf("\nHospital Management System\n");
            printf("1. Add Patient\n");
            printf("2. Remove Patient\n");
            printf("3. Search Patient\n");
            printf("4. Display All Patients\n");
            printf("5. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();  // Consume the trailing newline character

            switch (choice) {
                case 1:
                    printf("Enter Patient Name: ");
                    fgets(name, 50, stdin);
                    name[strcspn(name, "\n")] = 0;  // Remove newline character

                    printf("Enter Patient Age: ");
                    scanf("%d", &age);
                    getchar();  // Consume the trailing newline character

                    printf("Enter Patient Disease: ");
                    fgets(disease, 50, stdin);
                    disease[strcspn(disease, "\n")] = 0;  // Remove newline character

                    addPatient(&head, &patientIdCounter, name, age, disease);
                    break;
                case 2:
                    printf("Enter Patient ID to Remove: ");
                    int patientIdToRemove;
                    scanf("%d", &patientIdToRemove);
                    removePatient(&head, patientIdToRemove);
                    break;
                case 3:
                    printf("Enter Patient ID to Search: ");
                    int patientIdToSearch;
                    scanf("%d", &patientIdToSearch);
                    searchPatient(head, patientIdToSearch);
                    break;
                case 4:
                    displayPatients(head);
                    break;
                case 5:
                    printf("Exiting program.\n");
                    return 0;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("Access denied. Exiting program.\n");
    }

    return 0;
}
