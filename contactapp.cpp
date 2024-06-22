#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <regex>
#include <fstream>
#include <iomanip>

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};

std::unordered_map<std::string, Contact> contacts;

bool isValidPhone(const std::string &phone) {
    std::regex phoneRegex(R"(\d{10})");
    return std::regex_match(phone, phoneRegex);
}

bool isValidEmail(const std::string &email) {
    std::regex emailRegex(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
    return std::regex_match(email, emailRegex);
}

void addContact() {
    std::string name, phone, email;
    std::cout << "Enter name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter phone: ";
    std::cin >> phone;
    if (!isValidPhone(phone)) {
        std::cout << "Invalid phone number. Please enter a 10-digit number." << std::endl;
        return;
    }
    std::cout << "Enter email: ";
    std::cin >> email;
    if (!isValidEmail(email)) {
        std::cout << "Invalid email address." << std::endl;
        return;
    }
    contacts[name] = {name, phone, email};
    std::cout << "Contact added." << std::endl;
}

void displayContacts() {
    std::vector<Contact> sortedContacts;
    for (const auto &pair : contacts) {
        sortedContacts.push_back(pair.second);
    }
    std::sort(sortedContacts.begin(), sortedContacts.end(), [](const Contact &a, const Contact &b) {
        return a.name < b.name;
    });
    std::cout << std::left << std::setw(20) << "Name" << std::setw(15) << "Phone" << std::setw(30) << "Email" << std::endl;
    for (const auto &contact : sortedContacts) {
        std::cout << std::left << std::setw(20) << contact.name << std::setw(15) << contact.phone << std::setw(30) << contact.email << std::endl;
    }
}

void searchContact() {
    std::string name;
    std::cout << "Enter name to search: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    auto it = contacts.find(name);
    if (it != contacts.end()) {
        std::cout << "Name: " << it->second.name << ", Phone: " << it->second.phone << ", Email: " << it->second.email << std::endl;
    } else {
        std::cout << "Contact not found. Here are some suggestions:" << std::endl;
        for (const auto &pair : contacts) {
            if (pair.first.find(name) != std::string::npos) {
                std::cout << pair.first << std::endl;
            }
        }
    }
}

void deleteContact() {
    std::string name;
    std::cout << "Enter name of contact to delete: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    if (contacts.erase(name)) {
        std::cout << "Contact deleted." << std::endl;
    } else {
        std::cout << "Contact not found." << std::endl;
    }
}

void updateContact() {
    std::string name, phone, email;
    std::cout << "Enter name of contact to update: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    auto it = contacts.find(name);
    if (it != contacts.end()) {
        std::cout << "Enter new phone: ";
        std::cin >> phone;
        if (!isValidPhone(phone)) {
            std::cout << "Invalid phone number. Please enter a 10-digit number." << std::endl;
            return;
        }
        std::cout << "Enter new email: ";
        std::cin >> email;
        if (!isValidEmail(email)) {
            std::cout << "Invalid email address." << std::endl;
            return;
        }
        it->second = {name, phone, email};
        std::cout << "Contact updated." << std::endl;
    } else {
        std::cout << "Contact not found." << std::endl;
    }
}

void exportContacts() {
    std::ofstream outFile("contacts.txt");
    if (!outFile) {
        std::cout << "Error opening file for writing." << std::endl;
        return;
    }
    for (const auto &pair : contacts) {
        outFile << pair.second.name << " " << pair.second.phone << " " << pair.second.email << std::endl;
    }
    outFile.close();
    std::cout << "Contacts exported to contacts.txt." << std::endl;
}

void importContacts() {
    std::ifstream inFile("contacts.txt");
    if (!inFile) {
        std::cout << "Error opening file for reading." << std::endl;
        return;
    }
    std::string name, phone, email;
    while (inFile >> name >> phone >> email) {
        if (isValidPhone(phone) && isValidEmail(email)) {
            contacts[name] = {name, phone, email};
        }
    }
    inFile.close();
    std::cout << "Contacts imported from contacts.txt." << std::endl;
}

int main() {
    int choice;
    do {
        std::cout << "\n1. Add Contact" << std::endl;
        std::cout << "2. Display Contacts" << std::endl;
        std::cout << "3. Search Contact" << std::endl;
        std::cout << "4. Delete Contact" << std::endl;
        std::cout << "5. Update Contact" << std::endl;
        std::cout << "6. Export Contacts" << std::endl;
        std::cout << "7. Import Contacts" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                updateContact();
                break;
            case 6:
                exportContacts();
                break;
            case 7:
                importContacts();
                break;
            case 8:
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 8);
    return 0;
}
