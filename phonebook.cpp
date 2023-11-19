#include <iostream>
#include <string>
using namespace std;

// Define a Contact structure
struct Contact {
    string name;
    string phoneNumber;
    string email;
    Contact* prev;
    Contact* next;
};

class Phonebook {
private:
    Contact* head;
    Contact* tail;

public:
    Phonebook() : head(nullptr), tail(nullptr) {}

    // Function to add a contact to the phonebook
    void addContact(string name, string phoneNumber, string email) {
        if( phoneNumber.length() != (10) ){
            cout<< "Invalid Number ." << " " << "Enter Again" << endl;
            return ;
        }
        Contact* newContact = new Contact;
        newContact->name = name;
        newContact->phoneNumber = phoneNumber;
        newContact->email = email;
        newContact->prev = nullptr;
        newContact->next = nullptr;

        if (!head) {
            // If the phonebook is empty, set the new contact as the head
            head = newContact;
            tail = newContact;
        } else {
            // Otherwise, add the new contact to the end of the list
            tail->next = newContact;
            newContact->prev = tail;
            tail = newContact;
        }
    }

    // Function to search for a contact by name
    void searchContact(string name) {
        Contact* current = head;
        while (current) {
            if (current->name == name) {
                cout << "Name: " << current->name << " | Phone Number: " << current->phoneNumber << "| Email: " << current->name << endl;
                return;
            }
            current = current->next;
        }
        cout << "Contact not found." << endl;
    }

    // Function to display all contacts
    void displayContacts() {
        Contact* current = head;
        while (current) {
            cout << "Name: " << current->name << " | Phone Number: " << current->phoneNumber <<" | << Email: " << current->email << endl;
            current = current->next;
        }
    }

    // Function to delete a contact by name
    void deleteContact(string name) {
        Contact* current = head;
        while (current) {
            if (current->name == name) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                delete current;
                cout << "Contact deleted." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Contact not found." << endl;
    }
};

int main() {
    Phonebook phonebook;
    char choice;

    do {
        cout << "Welcome to Aashi's Phonebook" << endl;
        cout << "Phonebook Menu:" << endl;
        cout << "1. Add a Contact" << endl;
        cout << "2. Search for a Contact" << endl;
        cout << "3. Display All Contacts" << endl;
        cout << "4. Delete a Contact" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                string name, phoneNumber, email;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phoneNumber);
                cout << "Enter email: ";
                getline(cin, email);
                phonebook.addContact(name, phoneNumber, email);
                break;
            }
            case '2': {
                string name;
                cout << "Enter name to search: ";
                cin.ignore();
                getline(cin, name);
                phonebook.searchContact(name);
                break;
            }
            case '3':
                phonebook.displayContacts();
                break;
            case '4': {
                string name;
                cout << "Enter name to delete: ";
                cin.ignore();
                getline(cin, name);
                phonebook.deleteContact(name);
                break;
            }
            case '5':
                cout << "Exiting Phonebook." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != '5');

    return 0;
}
