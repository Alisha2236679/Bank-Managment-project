#include <iostream>
#include <fstream>
using namespace std;

int numberOfAccounts = 0;
int id;
string FILE_NAME = "bank.dat";
string countOfAccounts = "account.dat";
struct Banks
{
    int balance;
    int age;
    int accountnumber;
    string name;
} customer[100];

void customerDetails();
void openAccount();
bool checkAccount();
void depositMoney();
void withdrawMoney();
void printAccountInfo();
void deleteAccount();
void write();
void read();

void write()
{
    ofstream file, file1;
    file.open(countOfAccounts, ios::out);
    file.write((char *)&numberOfAccounts, sizeof(numberOfAccounts));
    file.close();

    file1.open(FILE_NAME, ios::out);
    file1.write((char *)&customer, sizeof(customer));
    file1.close();
}

void read()
{
    ifstream file;
    file.open(countOfAccounts, ios::in);
    file.read((char *)&numberOfAccounts, sizeof(numberOfAccounts));
    file.close();

    file.open(FILE_NAME, ios::in);
    file.read((char *)&customer, sizeof(customer));
    file.close();
}

int main()
{
    int userInput = 0;
    read();

    while (userInput == 0)
    {
        cout << endl
             << "Enter your choice " << endl;
        cout << "1. Open Account " << endl;
        cout << "2. Deposit money " << endl;
        cout << "3. Withdraw money" << endl;
        cout << "4. Display account" << endl;
        cout << "5. Delete account" << endl; 
        cout << "6. Exit" << endl;

        int choiceforbankaccount;
        cin >> choiceforbankaccount;
        switch (choiceforbankaccount)
        {
        case 1:
            openAccount();
            break;
        case 2:
            depositMoney();
            break;
        case 3:
            withdrawMoney();
            break;
        case 4:
            printAccountInfo();
            break;
        case 5:
            deleteAccount(); // New case
            break;
        case 6:
            userInput = 1;
            write();
            customerDetails();
            break;
        default:
            cout << "Invalid choice !! Try again ";
        }
    }
    return 0;
}

void openAccount()
{

    if (numberOfAccounts >= 100)
    {
        cout << "Cannot open more accounts. The bank is full." << endl;
        return;
    }
    else
    {
        cout << "Your account number: ";
        cin >> customer[numberOfAccounts].accountnumber;

        for (int i = 0; i < numberOfAccounts; i++)
        {
            if (customer[i].accountnumber == customer[numberOfAccounts].accountnumber)
            {
                cout << "Account number already exists. Choose another account number." << endl;
                openAccount();
                return;
            }
        }

        cout << "Enter your name: ";
        cin >> customer[numberOfAccounts].name;
        cout << "Enter your age: ";
        cin >> customer[numberOfAccounts].age;
        cout << "Enter how much you want to deposit: ";
        cin >> customer[numberOfAccounts].balance;
        customer[numberOfAccounts].balance = customer[numberOfAccounts].balance;
        numberOfAccounts++;
    }
}
void customerDetails()
{
    ofstream details;
    details.open("Bank details.txt", ios::app);
    for (int i = 0; i < numberOfAccounts; i++)
    {
        details << "-------CUSTOMER ID-----" << endl;
        details << "Customer Account Number is " << customer[i].accountnumber << endl;
        details << "Customer Name is " << customer[i].name << endl;
        details << "Customer Age is " << customer[i].age << endl;
        details << "Customer Balance is " << customer[i].balance << endl
                << endl;
    }
    details.close();
}

bool checkAccount()
{
    int accountNumber;
    cout << "Enter your account number: ";
    cin >> accountNumber;
    for (int iterator = 0; iterator < numberOfAccounts; iterator++)
    {
        if (accountNumber == customer[iterator].accountnumber)
        {
            id = iterator;
            return true;
        }
    }

    return false;
}

void depositMoney()
{
    int deposit1;
    bool result = checkAccount();
    if (result)
    {
        cout << "How much you want to deposit: ";
        cin >> deposit1;
        customer[id].balance = customer[id].balance + deposit1;
        cout << "Your balance is " << customer[id].balance << endl;
    }
    else
    {
        cout << "Account does not found " << endl;
    }
}

void withdrawMoney()
{
    int withdraw;
    bool result = checkAccount();
    if (result)
    {
        cout << "How much you want to withdraw: ";
        cin >> withdraw;
        if (customer[id].balance < withdraw)
        {
            cout << "You don't have sufficient balance in your account " << endl;
        }
        else
        {
            customer[id].balance = customer[id].balance - withdraw;
            cout << "Your balance is " << customer[id].balance << endl;
        }
    }
    else
    {
        cout << "Account does not found " << endl;
    }
}

void printAccountInfo()
{
    bool result = checkAccount();
    if (result)
    {
        cout << "Name of account holder is " << customer[id].name << endl;
        cout << "Age of account holder is " << customer[id].age << endl;
        cout << "Balance of this account is " << customer[id].balance << endl;
    }
    else
    {
        cout << "Account does not found " << endl;
    }
}
void deleteAccount()
{
    bool result = checkAccount();
    if (result)
    {
        for (int i = id; i < numberOfAccounts - 1; i++)
        {
            customer[i] = customer[i + 1];
        }
        numberOfAccounts--;
        cout << "Account deleted successfully." << endl;
    }
    else
    {
        cout << "Account does not found " << endl;
    }
}