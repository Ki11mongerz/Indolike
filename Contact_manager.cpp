#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Contact {
private:
    string name, phoneNumber, email;
public:
    Contact(string n, string p, string e) : name(n), phoneNumber(p), email(e) {}
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
    string getEmail() const { return email; }
    void setPhoneNumber(string p) { phoneNumber = p; }
    void setEmail(string e) { email = e; }
};

class ContactManager {
private:
    vector<Contact> contacts;
    string fileName;
public:
    ContactManager(string filename) : fileName(filename) { loadFromFile(); }
    void addContact(const Contact& contact) {
        contacts.push_back(contact);
        saveToFile();
    }
    void viewContacts() const {
        for (const auto& contact : contacts) {
            cout << "Name: " << contact.getName() << ", Phone: " << contact.getPhoneNumber() << ", Email: " << contact.getEmail() << "\n";
        }
    }
    void searchContacts(const string& name) const {
        for (const auto& contact : contacts) {
            if (contact.getName() == name) {
                cout << "Found - Name: " << contact.getName() << ", Phone: " << contact.getPhoneNumber() << ", Email: " << contact.getEmail() << "\n";
                return;
            }
        }
        cout << "Contact not found.\n";
    }
    void editContact(const string& name) {
        for (auto& contact : contacts) {
            if (contact.getName() == name) {
                string newPhone, newEmail;
                cout << "Enter new phone: "; cin >> newPhone;
                cout << "Enter new email: "; cin >> newEmail;
                contact.setPhoneNumber(newPhone);
                contact.setEmail(newEmail);
                saveToFile();
                return;
            }
        }
        cout << "Contact not found.\n";
    }
    void deleteContact(const string& name) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->getName() == name) {
                contacts.erase(it);
                saveToFile();
                return;
            }
        }
        cout << "Contact not found.\n";
    }
    void saveToFile() const {
        ofstream file(fileName);
        for (const auto& contact : contacts) {
            file << contact.getName() << "," << contact.getPhoneNumber() << "," << contact.getEmail() << "\n";
        }
    }
    void loadFromFile() {
        ifstream file(fileName);
        contacts.clear();
        string line, name, phone, email;
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, phone, ',');
            getline(ss, email, ',');
            contacts.push_back(Contact(name, phone, email));
        }
    }
};

int main() {
    ContactManager cm("contacts.txt");
    int choice;
    while (true) {
        cout << "1. Add Contact\n2. View Contacts\n3. Search Contact\n4. Edit Contact\n5. Delete Contact\n6. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            string name, phone, email;
            cout << "Enter name: "; cin >> name;
            cout << "Enter phone: "; cin >> phone;
            cout << "Enter email: "; cin >> email;
            cm.addContact(Contact(name, phone, email));
        } else if (choice == 2) {
            cm.viewContacts();
        } else if (choice == 3) {
            string name;
            cout << "Enter name to search: "; cin >> name;
            cm.searchContacts(name);
        } else if (choice == 4) {
            string name;
            cout << "Enter name to edit: "; cin >> name;
            cm.editContact(name);
        } else if (choice == 5) {
            string name;
            cout << "Enter name to delete: "; cin >> name;
            cm.deleteContact(name);
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}