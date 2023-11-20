#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    string email;
    string group;
    Contact* prev;
    Contact* next;
};

class Phonebook {
private:
    Contact* head;
    Contact* tail;
    stack<Contact*> undoStack;
    stack<Contact*> redoStack;
    unordered_map<string, Contact*> contactMap;
    unordered_map<string, vector<Contact*>> groups;

public:
    Phonebook() : head(nullptr), tail(nullptr) {}

    void addContact(string name, string phoneNumber, string email, string group) {
        if (phoneNumber.length() != 10) {
            cout << "Invalid Number. Enter Again" << endl;
            return;
        }

        if (contactMap.find(phoneNumber) != contactMap.end() || findDuplicateByName(name)) {
            cout << "Contact already exists. Cannot add duplicate." << endl;
            return;
        }

        Contact* newContact = new Contact;
        newContact->name = name;
        newContact->phoneNumber = phoneNumber;
        newContact->email = email;
        newContact->group = group;
        newContact->prev = nullptr;
        newContact->next = nullptr;

        contactMap[phoneNumber] = newContact;
        groups[group].push_back(newContact);

        if (!head) {
            head = newContact;
            tail = newContact;
        } else {
            tail->next = newContact;
            newContact->prev = tail;
            tail = newContact;
        }

        undoStack.push(head);
    }

    bool findDuplicateByName(string name) {
        Contact* current = head;
        while (current) {
            if (current->name == name) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void searchContact(string name) {
        Contact* current = head;
        while (current) {
            if (current->name == name) {
                cout << "Name: " << current->name << " | Phone Number: " << current->phoneNumber << " | Email: " << current->email << endl;
                return;
            }
            current = current->next;
        }
        cout << "Contact not found." << endl;
    }

    void displayContacts() {
        Contact* current = head;
        while (current) {
            cout << "Name: " << current->name << " | Phone Number: " << current->phoneNumber << " | Email: " << current->email << endl;
            current = current->next;
        }
    }

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

    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(head);
            head = undoStack.top();
            undoStack.pop();
            cout << "Undo successful." << endl;
        } else {
            cout << "Nothing to undo." << endl;
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(head);
            head = redoStack.top();
            redoStack.pop();
            cout << "Redo successful." << endl;
        } else {
            cout << "Nothing to redo." << endl;
        }
    }

    void displayContactsByGroup(string group) {
        if (groups.find(group) != groups.end()) {
            cout << "Contacts in Group " << group << ":" << endl;
            for (auto contact : groups[group]) {
                cout << "Name: " << contact->name << " | Phone Number: " << contact->phoneNumber << " | Email: " << contact->email << endl;
            }
        } else {
            cout << "No contacts in group " << group << "." << endl;
        }
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
        cout << "5. Undo" << endl;
        cout << "6. Redo" << endl;
        cout << "7. Display Contacts by Group" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                string name, phoneNumber, email, group;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phoneNumber);
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter group: ";
                getline(cin, group);
                phonebook.addContact(name, phoneNumber, email, group);
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
                phonebook.undo();
                break;
            case '6':
                phonebook.redo();
                break;
            case '7': {
                string group;
                cout << "Enter group name: ";
                cin.ignore();
                getline(cin, group);
                phonebook.displayContactsByGroup(group);
                break;
            }
            case '8':
                cout << "Exiting Phonebook." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != '8');

    return 0;
}
