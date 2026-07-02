#include <iostream>
#include <iomanip>
#include "MyLib.h"
using namespace std;

const string ClientsFileName = "Clients.txt";

enum enMainMenuOptions
{
    ShowClientList = 1,
    AddClient = 2,
    DeleteClient = 3,
    UpdateClientInfo = 4,
    FindClient = 5,
    Transactions = 6,
    Exit = 7
};

enum enTransactionsMenuOptions { enDeposit = 1, enWithdraw = 2, TotalBalances = 3, MainMenu = 4 };

struct stClientInfo
{
    string AccountNumber;
    string PinCode;
    string FullName;
    string PhoneNumber;
    double AccountBalance;
    bool MarkForDelete = false;
};

void DisplayMainMenu()
{

    system("cls");
    cout << "====================================\n";
    cout << "\tMain Menu Screen\n";
    cout << "====================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "====================================\n";


}

short ChooseOperation()
{
    short WhatYouWantToDo;
    do
    {
        cout << "Choose what you want to do. [1 to 7]  ";
        cin >> WhatYouWantToDo;
    } while (WhatYouWantToDo < 1 || WhatYouWantToDo>7);

    return WhatYouWantToDo;
}

stClientInfo ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    stClientInfo Client;
    vector <string> vClientData;

    vClientData = Strings::SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.FullName = vClientData[2];
    Client.PhoneNumber = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;

}

vector <stClientInfo> LoadClientsDataFromFile(string FileName)
{
    vector <stClientInfo> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClientInfo Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);

            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintHeader(short NumberOfClients)
{
    cout << "\t\t\t\t\tClient List (" << NumberOfClients << ") Client(s)";
    cout << "\n__________________________________________________";
    cout << "________________________________________________\n\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Clinet Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n__________________________________________________";
    cout << "________________________________________________\n\n";

}

void PrintClientRecord(stClientInfo Client)
{

    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.FullName;
    cout << "| " << left << setw(12) << Client.PhoneNumber;
    cout << "| " << left << setw(12) << Client.AccountBalance;

}

void PrintAllClientsData(vector <stClientInfo> vClients)
{

    PrintHeader(vClients.size());

    for (stClientInfo Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }

    cout << "__________________________________________________";
    cout << "________________________________________________\n";


}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    vector <stClientInfo> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClientInfo Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }

            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return false;
}

stClientInfo ReadNewClient()
{
    stClientInfo Client;

    cout << "\n\nEnter Account Number: ";
    // ws will extract all the whitespace characters
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with[" << Client.AccountNumber << "] already exists, enter another account number";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode: ";
    getline(cin, Client.PinCode);

    cout << "Enter Name: ";
    getline(cin, Client.FullName);

    cout << "Enter Phone Number: ";
    getline(cin, Client.PhoneNumber);

    cout << "Enter Account Balance: ";
    cin >> Client.AccountBalance;


    return Client;
}

string ConvertRecordToLine(stClientInfo Client, string Seperator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.FullName + Seperator;
    stClientRecord += Client.PhoneNumber + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;


}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewClient()
{
    stClientInfo Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddClients()
{
    char MoreClients = 'Y';

    do
    {
        cout << "Adding New Client:";
        AddNewClient();

        cout << "\nClient Added Successfully, do you want to add more clients? Y/N ";
        cin >> MoreClients;

    } while (MoreClients == 'y' || MoreClients == 'Y');

}

bool FindClientByAccountNumber(string AccountNumber, vector <stClientInfo>& vClients, stClientInfo& Client)
{

    for (stClientInfo C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;

}

void PrintClientCard(stClientInfo Client)
{
    cout << "\nThe following are the client details:";
    cout << "\n---------------------------------------";
    

    cout << "\nAccount Number  : " << Client.AccountNumber;
    cout << "\nPin Code        : " << Client.PinCode;
    cout << "\nName            : " << Client.FullName;
    cout << "\nPhone Number    : " << Client.PhoneNumber;
    cout << "\nAccount balance : " << Client.AccountBalance;
    cout << "\n---------------------------------------";

}

string ReadAccountNumber(string Message)
{
    string AccountNumber;

    cout << Message;
    cin >> AccountNumber;

    return AccountNumber;
}

void SaveClientsDataToFile(string FileName, vector <stClientInfo>& vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (stClientInfo& C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }


}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClientInfo>& vClients)
{
    for (stClientInfo& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClientInfo>& vClients)
{

    stClientInfo Client;
    char DeleteClient = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want to delete this Client?  y/n   ";
        cin >> DeleteClient;

        if (DeleteClient == 'y' || DeleteClient == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            //Refresh Clients
            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "\nClient with account number (" << AccountNumber << ") is Not Found!\n";
        return false;
    }




}

stClientInfo ChangeClientRecord(string AccountNumber)
{
    stClientInfo Client;

    Client.AccountNumber = AccountNumber;

    cout << "\nEnter PinCode: ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name: ";
    getline(cin, Client.FullName);

    cout << "Enter Phone Number: ";
    getline(cin, Client.PhoneNumber);

    cout << "Enter Account Balance: ";
    cin >> Client.AccountBalance;

    return Client;

}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClientInfo>& vClients)
{

    stClientInfo Client;
    char UpdateClient = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want to update this Client?  y/n   ";
        cin >> UpdateClient;

        if (UpdateClient == 'y' || UpdateClient == 'Y')
        {
            for (stClientInfo& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "\nClient with account number (" << AccountNumber << ") is Not Found!";
        return false;
    }




}

void GoBackToMainMenu()
{
    cout << "\nPress any key to go back to main menu...";
    system("pause>nul");
}

void DisplaySecondaryScreen(enMainMenuOptions WhatToDo)
{
    system("cls");
    cout << "----------------------------------\n";

    switch (WhatToDo)
    {
    case enMainMenuOptions::AddClient:
        cout << "\tAdd Client Screen\n";
        break;
    case enMainMenuOptions::DeleteClient:
        cout << "\tDelete Client Screen\n";
        break;
    case enMainMenuOptions::UpdateClientInfo:
        cout << "\tUpdate Client Info Screen\n";
        break;
    case enMainMenuOptions::FindClient:
        cout << "\tFind Client Screen\n";
        break;
    case enMainMenuOptions::Exit:
        cout << "\tProgram Ends :-)\n";
    }

    cout << "----------------------------------\n\n";

}

void ShowClientByAccountNumber(string AccountNumber, vector <stClientInfo> vClients)
{
    stClientInfo Client;

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with account number (" << AccountNumber << ") is Not Found!\n";
        AccountNumber = ReadAccountNumber("\nPlease enter Account Number. ");
    }

        PrintClientCard(Client);

}

void ShowTransactionMenu()
{
    system("cls");
    cout << "====================================\n";
    cout << "\tTransactions Menu Screen\n";
    cout << "====================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "====================================\n";

}

short ChooseTransactionOption()
{
    short Choice = 0;
    do
    {
        cout << "Choose what do you want to do [1 to 4] ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 4);

    return Choice;

}

void ShowTotalBalances(vector <stClientInfo> vClients)
{
    system("cls");
    short TotalBalances = 0;

    cout << "\t\t\t\t\tClient List (" << vClients.size() << ") Client(s)";
    cout << "\n__________________________________________________";
    cout << "________________________________________________\n\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Clinet Name";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n__________________________________________________";
    cout << "________________________________________________\n\n";

    for (stClientInfo Client : vClients)
    {
        cout << "| " << left << setw(15) << Client.AccountNumber;
        cout << "| " << left << setw(40) << Client.FullName;
        cout << "| " << left << setw(12) << Client.AccountBalance;
        TotalBalances += Client.AccountBalance;
        cout << endl;
    }

    cout << "__________________________________________________";
    cout << "________________________________________________\n\n";

    cout << "\t\t\t\t\tTotal Balances = " << TotalBalances << endl;

}

void TransactionsSecondaryScreen(enTransactionsMenuOptions WhatToDo)
{
    system("cls");
    cout << "----------------------------------\n";
    switch (WhatToDo)
    {
    case enTransactionsMenuOptions::enDeposit:
    {
        cout << "\tDeposit Screen\n";
        break;
    }
    case enTransactionsMenuOptions::enWithdraw:
    {
        cout << "\tWithdraw Screen\n";
        break;
    }
    }
    cout << "----------------------------------\n\n";

}

void GoBackToTransactions()
{
    cout << "\n\nPress any key to go back to transactions menu...";
    system("pause>0");
}

char SureToDoSomething(string Message)
{
    char Sure;
    cout << Message;
    cin >> Sure;

    return Sure;
}

void Deposit(string Accountnumber, vector <stClientInfo> &vClients)
{
    short DepositAmount = 0;
    cout << "\n\nPlease enter deposit amount. ";
    cin >> DepositAmount;


    if (toupper(SureToDoSomething("\nAre you sure you want to perform this transaction? Y/N  ")) == 'Y')
    {
        for (stClientInfo& C : vClients)
        {
            if (C.AccountNumber == Accountnumber)
            {
                C.AccountBalance += DepositAmount;
                cout << "\nDone successfully , New balance : " << C.AccountBalance << endl;
                break;
            }
        }
        
    }

    SaveClientsDataToFile(ClientsFileName, vClients);
}

void Withdraw(string Accountnumber, vector <stClientInfo>& vClients)
{
    short WithdrawAmount = 0;
    cout << "\n\nEnter withdraw amount. ";
    cin >> WithdrawAmount;

    {
        for (stClientInfo& C : vClients)
        {
            if (C.AccountNumber == Accountnumber)
            {
                while (WithdrawAmount > C.AccountBalance)
                {
                    cout << "\nAmount exceeds rhe balance, you can withdraw up to : " << C.AccountBalance;
                    cout << "\n\nPlease enter another amount. ";
                    cin >> WithdrawAmount;
                }
                if (toupper(SureToDoSomething("\nAre you sure you want to perform this transaction? Y/N  ")) == 'Y')
                {
                    C.AccountBalance -= WithdrawAmount;
                    cout << "\nDone successfully , New balance : " << C.AccountBalance << endl;
                    break;
                }
            }
        }
        SaveClientsDataToFile(ClientsFileName, vClients);
    }
}

void PerformTransactions(enTransactionsMenuOptions WhatToDo , vector <stClientInfo> &vClients)
{
    switch (WhatToDo)
    {
    case enTransactionsMenuOptions::enDeposit:
    {
        TransactionsSecondaryScreen(WhatToDo);
        string AccountNumber = ReadAccountNumber("Please enter account number. ");
        ShowClientByAccountNumber(AccountNumber,vClients);
        Deposit(AccountNumber, vClients);
        GoBackToTransactions();
        break;
    }
    case enTransactionsMenuOptions::enWithdraw:
    {
        TransactionsSecondaryScreen(WhatToDo);
        string AccountNumber = ReadAccountNumber("Please enter account number. ");
        ShowClientByAccountNumber(AccountNumber, vClients);
        Withdraw(AccountNumber, vClients);
        GoBackToTransactions();
        break;
    }
    case enTransactionsMenuOptions::TotalBalances:
    {
        ShowTotalBalances(vClients);
        GoBackToTransactions();
        break;
    }
    }

    
}


bool ExecuteUsersCommand(enMainMenuOptions WhatToDo)
{
    vector <stClientInfo> vClients = LoadClientsDataFromFile(ClientsFileName);
    enTransactionsMenuOptions Choice;

    switch (WhatToDo)
    {
    case enMainMenuOptions::ShowClientList:
    {
        system("cls");
        PrintAllClientsData(vClients);
        break;
    }
    case enMainMenuOptions::AddClient:
    {
        DisplaySecondaryScreen(WhatToDo);
        AddClients();
        break;
    }
    case enMainMenuOptions::DeleteClient:
    {
        DisplaySecondaryScreen(WhatToDo);
        string AccountNumber = ReadAccountNumber("Please enter account number.  ");
        DeleteClientByAccountNumber(AccountNumber, vClients);
        break;
    }
    case enMainMenuOptions::UpdateClientInfo:
    {
        DisplaySecondaryScreen(WhatToDo);
        string AccountNumber = ReadAccountNumber("Please enter account number.  ");
        UpdateClientByAccountNumber(AccountNumber, vClients);
        break;
    }
    case enMainMenuOptions::FindClient:
    {
        DisplaySecondaryScreen(WhatToDo);
        string AccountNumber = ReadAccountNumber("Please enter account number.  ");
        ShowClientByAccountNumber(AccountNumber, vClients);
        break;
    }
    case enMainMenuOptions::Transactions:
    {
        do
        {
            ShowTransactionMenu();
            Choice = (enTransactionsMenuOptions)ChooseTransactionOption();
            PerformTransactions(Choice, vClients);
        } while (Choice!=enTransactionsMenuOptions::MainMenu);
    }
    case enMainMenuOptions::Exit:
    {

        DisplaySecondaryScreen(WhatToDo);
        return 0;
    }

    }
    GoBackToMainMenu();
}

void StartProgram()
{
    enMainMenuOptions WhatToDo;

    do
    {
        DisplayMainMenu();
        WhatToDo = (enMainMenuOptions)ChooseOperation();
        ExecuteUsersCommand(WhatToDo);
    } while (WhatToDo != enMainMenuOptions::Exit);


}

int main()
{
    StartProgram();

    return 0;
}
