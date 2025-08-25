#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
    Contact* next;  // Self-referential pointer
};

Contact* head = nullptr;

// Function prototypes
void loadFromFile();
void saveToFile();
void insertContact();
void displayContacts();
void searchContact();
void updateContact();
void deleteContact();
void freeMemory();

void insertAlphabetically(Contact* newContact) {
    if (head == nullptr || newContact->name < head->name) {
        newContact->next = head;
        head = newContact;
    } else {
        Contact* current = head;
        while (current->next != nullptr && current->next->name < newContact->name) {
            current = current->next;
        }
        newContact->next = current->next;
        current->next = newContact;
    }
}

void insertContact() {
    Contact* newContact = new Contact();
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newContact->name);
    cout << "Enter phone: ";
    getline(cin, newContact->phone);
    cout << "Enter email: ";
    getline(cin, newContact->email);
    newContact->next = nullptr;

    insertAlphabetically(newContact);
    cout << "Contact added successfully.\n";
}

void displayContacts() {
    if (head == nullptr) {
        cout << "No contacts available.\n";
        return;
    }
    cout << left << setw(20) << "Name" << setw(15) << "Phone" << setw(25) << "Email" << endl;
    cout << string(60, '-') << endl;
    Contact* current = head;
    while (current != nullptr) {
        cout << left << setw(20) << current->name
             << setw(15) << current->phone
             << setw(25) << current->email << endl;
        current = current->next;
    }
}

void searchContact() {
    if (head == nullptr) {
        cout << "No contacts to search.\n";
        return;
    }
    cout << "Enter name to search: ";
    cin.ignore();
    string key;
    getline(cin, key);
    Contact* current = head;
    while (current != nullptr) {
        if (current->name == key) {
            cout << "Contact found:\n";
            cout << "Name: " << current->name << "\nPhone: " << current->phone << "\nEmail: " << current->email << endl;
            return;
        }
        current = current->next;
    }
    cout << "Contact not found.\n";
}

void updateContact() {
    if (head == nullptr) {
        cout << "No contacts to update.\n";
        return;
    }
    cout << "Enter name to update: ";
    cin.ignore();
    string key;
    getline(cin, key);
    Contact* current = head;
    while (current != nullptr) {
        if (current->name == key) {
            cout << "Enter new phone: ";
            getline(cin, current->phone);
            cout << "Enter new email: ";
            getline(cin, current->email);
            cout << "Contact updated successfully.\n";
            return;
        }
        current = current->next;
    }
    cout << "Contact not found.\n";
}

void deleteContact() {
    if (head == nullptr) {
        cout << "No contacts to delete.\n";
        return;
    }
    cout << "Enter name to delete: ";
    cin.ignore();
    string key;
    getline(cin, key);

    Contact* current = head;
    Contact* previous = nullptr;

    while (current != nullptr && current->name != key) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Contact not found.\n";
        return;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
    cout << "Contact deleted successfully.\n";
}

void saveToFile() {
    ofstream file("contacts.txt");
    if (!file) {
        cout << "Error saving contacts.\n";
        return;
    }
    Contact* current = head;
    while (current != nullptr) {
        file << current->name << "|" << current->phone << "|" << current->email << "\n";
        current = current->next;
    }
    file.close();
    cout << "Contacts saved to file.\n";
}

void loadFromFile() {
    ifstream file("contacts.txt");
    if (!file) {
        return; // No file yet
    }
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.rfind('|');
        if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) continue;

        Contact* newContact = new Contact();
        newContact->name = line.substr(0, pos1);
        newContact->phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
        newContact->email = line.substr(pos2 + 1);
        newContact->next = nullptr;

        insertAlphabetically(newContact);
    }
    file.close();
}

void freeMemory() {
    while (head != nullptr) {
        Contact* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    loadFromFile();
    int choice;
    do {
        cout << "\n=== Contact Book Menu ===\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Update Contact\n";
        cout << "5. Delete Contact\n";
        cout << "6. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: updateContact(); break;
            case 5: deleteContact(); break;
            case 6: saveToFile(); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    freeMemory();
    return 0;
}
