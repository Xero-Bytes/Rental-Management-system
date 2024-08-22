#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User {
private:
    string username;
    string password;

public:
    User(const string &user, const string &pass) : username(user), password(pass) {}

    bool verifyCredentials(const string &user, const string &pass) {
        return (username == user && password == pass);
    }
};

class RentalRecord {
private:
    string CustomerName;
    string CustomerContact;
    string CustomerAddress;
    string RentalStartDate;
    string RentalEndDate;
    string CarDetails;

public:
    void inputDetails() {
        cout << "Enter customer name: ";
        getline(cin, CustomerName);
        cout << "Enter customer contact: ";
        getline(cin, CustomerContact);
        cout << "Enter customer address: ";
        getline(cin, CustomerAddress);
        cout << "Enter rental start date (YYYY-MM-DD): ";
        getline(cin, RentalStartDate);
        cout << "Enter rental end date (YYYY-MM-DD): ";
        getline(cin, RentalEndDate);
        cout << "Enter car details: ";
        getline(cin, CarDetails);
    }

    void displayDetails() const {
        cout << "Customer Name: " << CustomerName << endl;
        cout << "Customer Contact: " << CustomerContact << endl;
        cout << "Customer Address: " << CustomerAddress << endl;
        cout << "Rental Start Date: " << RentalStartDate << endl;
        cout << "Rental End Date: " << RentalEndDate << endl;
        cout << "Car Details: " << CarDetails << endl;
    }

    void SaveToFile(ofstream &file) const {
        file << CustomerName << endl
             << CustomerContact << endl
             << CustomerAddress << endl
             << RentalStartDate << endl
             << RentalEndDate << endl
             << CarDetails << endl
             << "----------" << endl;
    }

    static void SearchRecordsByName(const string &searchName) {
        ifstream inFile("rental_record.txt");
        string line;
        bool found = false;

        if (inFile) {
            while (getline(inFile, line)) {
                if (line == searchName) {
                    found = true;
                    cout << "Rental record for " << searchName << " found:" << endl;
                    cout << line << endl; // CustomerName

                    for (int i = 0; i < 5; ++i) { // Read next 5 lines
                        if (getline(inFile, line)) {
                            cout << line << endl;
                        }
                    }
                    cout << "----------" << endl;
                    break; // Stop searching after finding the record
                } else {
                    // Skip 6 lines (current line + 5 details + delimiter)
                    for (int i = 0; i < 6; ++i) {
                        if (!getline(inFile, line)) {
                            break; // Stop if end of file is reached
                        }
                    }
                }
            }
            if (!found) {
                cout << "No records found for " << searchName << "." << endl;
            }
            inFile.close();
        } else {
            cout << "Error opening file for reading." << endl;
        }
    }

    static void update_record(const string &searchName) {
        ifstream inFile("rental_record.txt");
        ofstream outFile("temp_rental_record.txt");
        string line;
        bool found = false;

        if (inFile && outFile) {
            while (getline(inFile, line)) {
                if (line == searchName) {
                    found = true;
                    cout << "Updating record for " << searchName << endl;
                    cout << "Enter new details:" << endl;

                    RentalRecord updatedRecord;
                    updatedRecord.inputDetails();
                    updatedRecord.SaveToFile(outFile);

                    // Skip the remaining lines of the old record
                    for (int i = 0; i < 6; ++i) {
                        if (!getline(inFile, line)) break; // Prevent reading beyond EOF
                    }
                } else {
                    outFile << line << endl;
                }
            }

            if (found) {
                cout << "Record updated successfully." << endl;
            } else {
                cout << "No record found for " << searchName << "." << endl;
            }

            inFile.close();
            outFile.close();

            remove("rental_record.txt");
            rename("temp_rental_record.txt", "rental_record.txt");
        } else {
            cout << "Error opening file for reading or writing." << endl;
        }
    }
};
class CalculateRentalCharges:public RentalRecord{
int car=100;
if(car==toyyotta){
car=car+100;

}
};

void displayMenu() {
    cout << "         Welcome To The Car Rental Management System         " << endl;
    cout << "        -------------------------------------------         " << endl;
    cout << endl;
    cout << "                          _ _ _ _                         " << endl;
    cout << "                         :       :                         " << endl;
    cout << "                         : MENU  :                         " << endl;
    cout << "                         :_ _ _ _:                         " << endl;
    cout << endl;
    cout << endl;
    cout << "1. Add Rental Record" << endl;
    cout << "2. Search Rental Records" << endl;
    cout << "3. Update Rental Records" << endl;
    cout<<"4. Calculate Rental Charges"<<endl;
    cout << "5. Exit" << endl;
    cout << endl;
    cout << "Enter your choice: ";
}

int main() {
    User admin("Taqdees", "1234");
    string inputUser, inputPass;
    bool loggedIn = false;

    while (!loggedIn) {
        cout << "Please enter username: ";
        cin >> inputUser;
        cin.ignore(); 
        cout << "Please enter password: ";
        cin >> inputPass;
        cin.ignore(); 
        if (admin.verifyCredentials(inputUser, inputPass)) {
            cout << "Login Successful!" << endl;
            loggedIn = true;
        } else {
            cout << "Login Failed! Please check your username and password." << endl;
            cout << "Do you want to try again? (y/n): ";
            char retry;
            cin >> retry;
            cin.ignore(); 
            if (retry == 'n' || retry == 'N') {
                cout << "Exiting the system!" << endl;
                return 0; 
            } else if (retry != 'y' && retry != 'Y') {
                cout << "Invalid input. Exiting the system!" << endl;
                return 0; 
            }
        }
    }

    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); 
        if (choice == 1) {
            RentalRecord rental;
            rental.inputDetails();
            ofstream outFile("rental_record.txt", ios::app);
            if (outFile) {
                rental.SaveToFile(outFile);
                cout << "\n(Rental Details)" << endl;
                rental.displayDetails();
            } else {
                cout << "Error opening file for writing." << endl;
            }
        } else if (choice == 2) {
            cout << "Enter customer name to search: ";
            string searchName;
            getline(cin, searchName);
            RentalRecord::SearchRecordsByName(searchName);
        } else if (choice == 3) {
            cout << "Enter customer name to update: ";
            string searchName;
            getline(cin, searchName);
            RentalRecord::update_record(searchName);
        }
        else if(choice==4){

        }
         else if (choice == 5) {
            cout << "Exiting the system!" << endl;
            break;
        } else {
            cout << "Invalid Choice!" << endl;
        }
    }

    return 0;
}
