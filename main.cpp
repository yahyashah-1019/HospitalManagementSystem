
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class AppointmentQueue;

// ==================== PATIENT NODE ====================

struct PatientNode
{
    int patientID;
    char name[50];
    int age;
    char gender[15];
    char contact[20];
    char reason[100];

    PatientNode* next;
};

// ==================== PATIENT LINKED LIST ====================

class PatientList
{
private:
    PatientNode* head;
    PatientNode* tail;

public:

    PatientList()
    {
        head = NULL;
        tail = NULL;
    }

    ~PatientList()
    {
        PatientNode* temp;

        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }

        tail = NULL;
    }

    PatientNode* findPatient(int id)
    {
        PatientNode* temp = head;

        while (temp != NULL)
        {
            if (temp->patientID == id)
                return temp;

            temp = temp->next;
        }

        return NULL;
    }

    // Register a new patient
    void registerPatient()
    {
        PatientNode* newNode = new PatientNode;

        cout << "\nEnter Patient ID: ";
        cin >> newNode->patientID;

        if (findPatient(newNode->patientID) != NULL)
        {
            cout << "\nThis Patient ID already exists!\n";
            delete newNode;
            return;
        }

        cin.ignore(1000, '\n');

        cout << "Enter Name: ";
        cin.getline(newNode->name, 50);

        cout << "Enter Age: ";
        cin >> newNode->age;

        if (newNode->age <= 0 || newNode->age > 120)
        {
            cout << "Invalid age!\n";
            delete newNode;
            return;
        }

        cin.ignore(1000, '\n');

        cout << "Enter Gender: ";
        cin.getline(newNode->gender, 15);

        cout << "Enter Contact: ";
        cin.getline(newNode->contact, 20);

        cout << "Enter Reason: ";
        cin.getline(newNode->reason, 100);

        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        cout << "\nPatient registered successfully!\n";
    }

    // Selection Sort by Patient ID
    void sortPatients()
    {
        if (head == NULL || head->next == NULL)
        {
            cout << "\nNot enough patients to sort.\n";
            return;
        }

        PatientNode* current = head;

        while (current != NULL)
        {
            PatientNode* minNode = current;
            PatientNode* temp = current->next;

            while (temp != NULL)
            {
                if (temp->patientID < minNode->patientID)
                    minNode = temp;

                temp = temp->next;
            }

            if (minNode != current)
            {
                int id = current->patientID;
                current->patientID = minNode->patientID;
                minNode->patientID = id;

                int age = current->age;
                current->age = minNode->age;
                minNode->age = age;

                char name[50], gender[15], contact[20], reason[100];

                strcpy(name, current->name);
                strcpy(current->name, minNode->name);
                strcpy(minNode->name, name);

                strcpy(gender, current->gender);
                strcpy(current->gender, minNode->gender);
                strcpy(minNode->gender, gender);

                strcpy(contact, current->contact);
                strcpy(current->contact, minNode->contact);
                strcpy(minNode->contact, contact);

                strcpy(reason, current->reason);
                strcpy(current->reason, minNode->reason);
                strcpy(minNode->reason, reason);
            }

            current = current->next;
        }

        cout << "\nPatients sorted successfully!\n";
        displayPatients();
    }

    // Save patient records
    void savePatients()
    {
        ofstream file("patients.txt");

        if (!file)
        {
            cout << "\nError opening patients.txt!\n";
            return;
        }

        PatientNode* temp = head;

        while (temp != NULL)
        {
            file << temp->patientID << endl;
            file << temp->name << endl;
            file << temp->age << endl;
            file << temp->gender << endl;
            file << temp->contact << endl;
            file << temp->reason << endl;

            temp = temp->next;
        }

        file.close();

        cout << "\nPatient records saved successfully!\n";
    }

    // Load patient records
    void loadPatients()
    {
        ifstream file("patients.txt");

        if (!file)
            return;

        while (true)
        {
            PatientNode* newNode = new PatientNode;

            if (!(file >> newNode->patientID))
            {
                delete newNode;
                break;
            }

            file.ignore(1000, '\n');

            if (!file.getline(newNode->name, 50))
            {
                delete newNode;
                break;
            }

            if (!(file >> newNode->age))
            {
                delete newNode;
                break;
            }

            file.ignore(1000, '\n');

            if (!file.getline(newNode->gender, 15))
            {
                delete newNode;
                break;
            }

            if (!file.getline(newNode->contact, 20))
            {
                delete newNode;
                break;
            }

            if (!file.getline(newNode->reason, 100))
            {
                delete newNode;
                break;
            }

            if (newNode->patientID <= 0 ||
                newNode->age <= 0 || newNode->age > 120 ||
                strlen(newNode->name) == 0 ||
                strlen(newNode->gender) == 0 ||
                strlen(newNode->contact) == 0 ||
                strlen(newNode->reason) == 0 ||
                findPatient(newNode->patientID) != NULL)
            {
                cout << "\nInvalid patient record skipped!\n";
                delete newNode;
                continue;
            }

            newNode->next = NULL;

            if (head == NULL)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }

        file.close();

        cout << "\nPatient records loaded successfully!\n";
    }

    // Display all patients
    void displayPatients()
    {
        if (head == NULL)
        {
            cout << "\nNo patients registered yet.\n";
            return;
        }

        PatientNode* temp = head;

        while (temp != NULL)
        {
            cout << "\n-------------------------\n";
            cout << "Patient ID: " << temp->patientID << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Age: " << temp->age << endl;
            cout << "Gender: " << temp->gender << endl;
            cout << "Contact: " << temp->contact << endl;
            cout << "Reason: " << temp->reason << endl;

            temp = temp->next;
        }
    }

    // Search patient
    void searchPatient()
    {
        int id;

        cout << "\nEnter Patient ID to search: ";
        cin >> id;

        PatientNode* temp = findPatient(id);

        if (temp == NULL)
        {
            cout << "\nPatient not found!\n";
            return;
        }

        cout << "\nPatient Found!\n";
        cout << "ID: " << temp->patientID << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Age: " << temp->age << endl;
        cout << "Gender: " << temp->gender << endl;
        cout << "Contact: " << temp->contact << endl;
        cout << "Reason: " << temp->reason << endl;
    }

    // Update patient
    void updatePatient()
    {
        int id;

        cout << "\nEnter Patient ID to update: ";
        cin >> id;

        PatientNode* temp = findPatient(id);

        if (temp == NULL)
        {
            cout << "\nPatient not found!\n";
            return;
        }

        cout << "\nPatient Found!\n";

        cin.ignore(1000, '\n');

        cout << "Enter New Name: ";
        cin.getline(temp->name, 50);

        cout << "Enter New Age: ";
        cin >> temp->age;

        if (temp->age <= 0 || temp->age > 120)
        {
            cout << "Invalid age! Update cancelled.\n";
            return;
        }

        cin.ignore(1000, '\n');

        cout << "Enter New Gender: ";
        cin.getline(temp->gender, 15);

        cout << "Enter New Contact: ";
        cin.getline(temp->contact, 20);

        cout << "Enter New Reason: ";
        cin.getline(temp->reason, 100);

        cout << "\nPatient updated successfully!\n";
    }

    // Declaration; implementation appears after AppointmentQueue
    void deletePatient(AppointmentQueue& appointments);
};

// ==================== APPOINTMENT NODE ====================

struct AppointmentNode
{
    int appointmentID;
    int patientID;
    char doctorName[50];
    char date[20];
    char time[20];
    char status[20];

    AppointmentNode* next;
};

// ==================== APPOINTMENT QUEUE ====================

class AppointmentQueue
{
private:
    AppointmentNode* front;
    AppointmentNode* rear;
    AppointmentNode* historyHead;
    AppointmentNode* historyTail;

    // Check duplicate appointment ID
    bool appointmentExists(int id)
    {
        AppointmentNode* temp = front;

        while (temp != NULL)
        {
            if (temp->appointmentID == id)
                return true;

            temp = temp->next;
        }

        temp = historyHead;

        while (temp != NULL)
        {
            if (temp->appointmentID == id)
                return true;

            temp = temp->next;
        }

        return false;
    }

    // Add appointment to history
    void addToHistory(AppointmentNode* source, const char* newStatus)
    {
        AppointmentNode* newNode = new AppointmentNode;

        newNode->appointmentID = source->appointmentID;
        newNode->patientID = source->patientID;

        strcpy(newNode->doctorName, source->doctorName);
        strcpy(newNode->date, source->date);
        strcpy(newNode->time, source->time);
        strcpy(newNode->status, newStatus);

        newNode->next = NULL;

        if (historyHead == NULL)
        {
            historyHead = newNode;
            historyTail = newNode;
        }
        else
        {
            historyTail->next = newNode;
            historyTail = newNode;
        }
    }

public:

    AppointmentQueue()
    {
        front = NULL;
        rear = NULL;
        historyHead = NULL;
        historyTail = NULL;
    }

    ~AppointmentQueue()
    {
        AppointmentNode* temp;

        while (front != NULL)
        {
            temp = front;
            front = front->next;
            delete temp;
        }

        while (historyHead != NULL)
        {
            temp = historyHead;
            historyHead = historyHead->next;
            delete temp;
        }

        rear = NULL;
        historyTail = NULL;
    }

    // Check whether patient has an active appointment
    bool hasActiveAppointment(int patientID)
    {
        AppointmentNode* temp = front;

        while (temp != NULL)
        {
            if (temp->patientID == patientID)
                return true;

            temp = temp->next;
        }

        return false;
    }

    // Schedule appointment
    void scheduleAppointment(PatientList& patients)
    {
        AppointmentNode* newNode = new AppointmentNode;

        cout << "\nEnter Appointment ID: ";
        cin >> newNode->appointmentID;

        if (appointmentExists(newNode->appointmentID))
        {
            cout << "\nAppointment ID already exists!\n";
            delete newNode;
            return;
        }

        cout << "Enter Patient ID: ";
        cin >> newNode->patientID;

        if (patients.findPatient(newNode->patientID) == NULL)
        {
            cout << "\nPatient is not registered!\n";
            delete newNode;
            return;
        }

        cin.ignore(1000, '\n');

        cout << "Enter Doctor Name: ";
        cin.getline(newNode->doctorName, 50);

        cout << "Enter Appointment Date: ";
        cin.getline(newNode->date, 20);

        cout << "Enter Appointment Time: ";
        cin.getline(newNode->time, 20);

        strcpy(newNode->status, "Scheduled");

        newNode->next = NULL;

        // Enqueue at rear
        if (front == NULL)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        cout << "\nAppointment scheduled successfully!\n";

        saveAppointments();
    }

    // Load appointments
    void loadAppointments()
    {
        ifstream file("appointments.txt");

        if (!file)
        {
            cout << "\nNo previous appointment records found.\n";
            return;
        }

        while (true)
        {
            AppointmentNode* newNode = new AppointmentNode;

            if (!(file >> newNode->appointmentID))
            {
                delete newNode;
                break;
            }

            if (!(file >> newNode->patientID))
            {
                delete newNode;
                break;
            }

            file.ignore(1000, '\n');

            if (!file.getline(newNode->doctorName, 50) ||
                !file.getline(newNode->date, 20) ||
                !file.getline(newNode->time, 20) ||
                !file.getline(newNode->status, 20))
            {
                delete newNode;
                break;
            }

            newNode->next = NULL;

            if (front == NULL)
            {
                front = newNode;
                rear = newNode;
            }
            else
            {
                rear->next = newNode;
                rear = newNode;
            }
        }

        file.close();

        cout << "\nAppointment records loaded successfully!\n";
    }

    // Load appointment history
    void loadHistory()
    {
        ifstream file("appointment_history.txt");

        if (!file)
        {
            cout << "\nNo previous appointment history found.\n";
            return;
        }

        while (true)
        {
            AppointmentNode* newNode = new AppointmentNode;

            if (!(file >> newNode->appointmentID))
            {
                delete newNode;
                break;
            }

            if (!(file >> newNode->patientID))
            {
                delete newNode;
                break;
            }

            file.ignore(1000, '\n');

            if (!file.getline(newNode->doctorName, 50) ||
                !file.getline(newNode->date, 20) ||
                !file.getline(newNode->time, 20) ||
                !file.getline(newNode->status, 20))
            {
                delete newNode;
                break;
            }

            newNode->next = NULL;

            if (historyHead == NULL)
            {
                historyHead = newNode;
                historyTail = newNode;
            }
            else
            {
                historyTail->next = newNode;
                historyTail = newNode;
            }
        }

        file.close();

        cout << "\nAppointment history loaded successfully!\n";
    }

    // Display waiting queue
    void displayQueue()
    {
        if (front == NULL)
        {
            cout << "\nNo appointments waiting.\n";
            return;
        }

        AppointmentNode* temp = front;

        cout << "\n===== WAITING APPOINTMENTS =====\n";

        while (temp != NULL)
        {
            cout << "\nAppointment ID: " << temp->appointmentID << endl;
            cout << "Patient ID: " << temp->patientID << endl;
            cout << "Doctor: " << temp->doctorName << endl;
            cout << "Date: " << temp->date << endl;
            cout << "Time: " << temp->time << endl;
            cout << "Status: " << temp->status << endl;

            temp = temp->next;
        }
    }

    // Process next appointment (FIFO dequeue)
    void processNextAppointment()
    {
        if (front == NULL)
        {
            cout << "\nNo appointments to process.\n";
            return;
        }

        AppointmentNode* temp = front;

        cout << "\nProcessing Appointment ID: "
             << temp->appointmentID << endl;

        cout << "Patient ID: " << temp->patientID << endl;

        addToHistory(temp, "Completed");

        front = front->next;

        if (front == NULL)
            rear = NULL;

        delete temp;

        cout << "\nAppointment completed successfully!\n";

        saveAppointments();
        saveHistory();
    }

    // Cancel appointment
    void cancelAppointment()
    {
        if (front == NULL)
        {
            cout << "\nNo appointments available to cancel.\n";
            return;
        }

        int id;

        cout << "\nEnter Appointment ID to cancel: ";
        cin >> id;

        AppointmentNode* temp = front;
        AppointmentNode* previous = NULL;

        while (temp != NULL && temp->appointmentID != id)
        {
            previous = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "\nAppointment not found!\n";
            return;
        }

        addToHistory(temp, "Cancelled");

        if (previous == NULL)
            front = front->next;
        else
            previous->next = temp->next;

        if (temp == rear)
            rear = previous;

        delete temp;

        cout << "\nAppointment cancelled successfully!\n";

        saveAppointments();
        saveHistory();
    }

    // Save waiting appointments
    void saveAppointments()
    {
        ofstream file("appointments.txt");

        if (!file)
        {
            cout << "\nError opening appointments.txt!\n";
            return;
        }

        AppointmentNode* temp = front;

        while (temp != NULL)
        {
            file << temp->appointmentID << endl;
            file << temp->patientID << endl;
            file << temp->doctorName << endl;
            file << temp->date << endl;
            file << temp->time << endl;
            file << temp->status << endl;

            temp = temp->next;
        }

        file.close();

        cout << "\nAppointments saved successfully!\n";
    }

    // Save appointment history
    void saveHistory()
    {
        ofstream file("appointment_history.txt");

        if (!file)
        {
            cout << "\nError opening appointment_history.txt!\n";
            return;
        }

        AppointmentNode* temp = historyHead;

        while (temp != NULL)
        {
            file << temp->appointmentID << endl;
            file << temp->patientID << endl;
            file << temp->doctorName << endl;
            file << temp->date << endl;
            file << temp->time << endl;
            file << temp->status << endl;

            temp = temp->next;
        }

        file.close();

        cout << "\nAppointment history saved successfully!\n";
    }

    // Display appointment history
    void displayHistory()
    {
        if (historyHead == NULL)
        {
            cout << "\nNo appointment history available.\n";
            return;
        }

        AppointmentNode* temp = historyHead;

        cout << "\n===== APPOINTMENT HISTORY =====\n";

        while (temp != NULL)
        {
            cout << "\nAppointment ID: " << temp->appointmentID << endl;
            cout << "Patient ID: " << temp->patientID << endl;
            cout << "Doctor: " << temp->doctorName << endl;
            cout << "Date: " << temp->date << endl;
            cout << "Time: " << temp->time << endl;
            cout << "Status: " << temp->status << endl;

            temp = temp->next;
        }
    }
};

// ==================== DELETE PATIENT IMPLEMENTATION ====================

void PatientList::deletePatient(AppointmentQueue& appointments)
{
    if (head == NULL)
    {
        cout << "\nNo patients available to delete.\n";
        return;
    }

    int id;

    cout << "\nEnter Patient ID to delete: ";
    cin >> id;

    // Prevent deletion if an active appointment exists
    if (appointments.hasActiveAppointment(id))
    {
        cout << "\nCannot delete patient! "
             << "Patient has an active appointment.\n";
        return;
    }

    PatientNode* temp = head;
    PatientNode* previous = NULL;

    // Find patient
    while (temp != NULL && temp->patientID != id)
    {
        previous = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "\nPatient not found!\n";
        return;
    }

    // Delete first node
    if (previous == NULL)
        head = head->next;
    else
        previous->next = temp->next;

    // Update tail
    if (temp == tail)
        tail = previous;

    delete temp;

    cout << "\nPatient deleted successfully!\n";
    savePatients();
}

// ==================== MAIN FUNCTION ====================

int main()
{
    PatientList patients;
    AppointmentQueue appointments;

    // Load saved records
    patients.loadPatients();
    appointments.loadAppointments();
    appointments.loadHistory();

    int choice;

    do
    {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====\n";

        cout << "\n--- PATIENT MANAGEMENT ---\n";
        cout << "1. Register Patient\n";
        cout << "2. Display Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Update Patient\n";
        cout << "5. Delete Patient\n";

        cout << "\n--- APPOINTMENT MANAGEMENT ---\n";
        cout << "6. Schedule Appointment\n";
        cout << "7. Display Waiting Queue\n";
        cout << "8. Process Next Appointment\n";
        cout << "9. Cancel Appointment\n";
        cout << "10. Display Appointment History\n";

        cout << "\n11. Sort Patients by ID\n";

        cout << "\n0. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                patients.registerPatient();
                patients.savePatients();
                break;

            case 2:
                patients.displayPatients();
                break;

            case 3:
                patients.searchPatient();
                break;

            case 4:
                patients.updatePatient();
                patients.savePatients();
                break;


            case 5:
                  patients.deletePatient(appointments);
                   break;

            case 6:
                appointments.scheduleAppointment(patients);
                break;

            case 7:
                appointments.displayQueue();
                break;

            case 8:
                appointments.processNextAppointment();
                break;

            case 9:
                appointments.cancelAppointment();
                break;

            case 10:
                appointments.displayHistory();
                break;

            case 11:
                patients.sortPatients();
                patients.savePatients();
                break;

            case 0:
                cout << "\nThank you for using Hospital Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
