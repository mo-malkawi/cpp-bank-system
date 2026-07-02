#include <iostream>
#include <iomanip>
#include "MyLib.h"
using namespace std;

const string ClientsFileName = "Clients.txt";

const string UsersFileName = "Users.txt";

enum enMainMenuOptions
{
    ShowClientList = 1,
    AddClient = 2,
    DeleteClient = 3,
    UpdateClientInfo = 4,
    FindClient = 5,
    Transactions = 6,
    enManageUsers = 7,
    Logout = 8
};

enum enTransactionsMenuOptions { enDeposit = 1, enWithdraw = 2, TotalBalances = 3, enMainMenu = 4 };

enum enMangeUsersOptions
{
    ListUsers = 1,
    AddUser = 2,
    DeleteUser = 3,
    UpdateUser = 4,
    FindUser = 5,
    MainMenu = 6,
};

struct stUser
{
    string Username;
    short Password=0;
    short Permissions=0;
    bool MarkForDeletion = 0;
};

stUser CurrentUser;

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
    cout << "\t[3] Delet Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "====================================\n";


}

short ChooseOperation(short From , short To)
{
    short WhatYouWantToDo;
    do
    {
        printf("Choose what you want to do. [%d to %d]? ", From, To);
        cin >> WhatYouWantToDo;
    } while (WhatYouWantToDo < From || WhatYouWantToDo>To);

    return WhatYouWantToDo;
}

stUser ConvertLineToUser(string Line, string Seperator = "#//#")
{
    stUser User;
    vector <string> vUserData;

    vUserData = Strings::SplitString(Line, Seperator);

    User.Username = vUserData[0];
    User.Password = stoi(vUserData[1]);
    User.Permissions = stoi(vUserData[2]);

    return User;

}

string ConvertUserToLine(stUser User, string Seperator = "#//#")
{
    string stUserRecord = "";

    stUserRecord += User.Username + Seperator;
    stUserRecord += to_string(User.Password) + Seperator;
    stUserRecord += to_string(User.Permissions);
    

    return stUserRecord;


}

vector <stUser> LoadUsersDataFromFile(string FileName)
{
    vector <stUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertLineToUser(Line);

            vUsers.push_back(User);
        }
        MyFile.close();
    }
    return vUsers;
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

void Deposit(string Accountnumber, vector <stClientInfo>& vClients)
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

void PerformTransactions(enTransactionsMenuOptions WhatToDo, vector <stClientInfo>& vClients)
{
    switch (WhatToDo)
    {
    case enTransactionsMenuOptions::enDeposit:
    {
        TransactionsSecondaryScreen(WhatToDo);
        string AccountNumber = ReadAccountNumber("Please enter account number. ");
        ShowClientByAccountNumber(AccountNumber, vClients);
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

void GoBackToManageUsers()
{
    cout << "Press any key to go back to manage users menu...\n";
    system("pause>nul");
}

bool FindUserByUsernameAndPassword(string Username, short Password, stUser& User)
{
    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    for (stUser U : vUsers)
    {

        if (U.Username == Username && U.Password == Password)
        {
            User = U;
            return true;
        }

    }
    return false;
}

void ManageUsersHeader()
{
    system("cls");
    cout << "===================================\n";
    cout << "        Manage User Menu\n";
    cout << "===================================\n";
    cout << "\t[1]List Users.\n";
    cout << "\t[2]Add New User.\n";
    cout << "\t[3]Delete User.\n";
    cout << "\t[4]Update User.\n";
    cout << "\t[5]Find User.\n";
    cout << "\t[6]Main Menu.\n";
    cout << "===================================\n";
}

void UsersListHeader(short NumberOfUsers)
{
    cout << "\t\t\t\t\tUsers List (" << NumberOfUsers << ") User(s)";
    cout << "\n__________________________________________________";
    cout << "________________________________________________\n\n";

    cout << "| " << left << setw(15) << "Username";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";

    cout << "\n__________________________________________________";
    cout << "________________________________________________\n\n";

}

void PrintUserRecord(stUser &User)
{

    cout << "| " << left << setw(15) << User.Username;
    cout << "| " << left << setw(10) << User.Password;
    cout << "| " << left << setw(40) << User.Permissions;

}

void PrintAllUsersData(vector <stUser> &vUsers)
{
    system("cls");

    UsersListHeader(vUsers.size());

    for (stUser User : vUsers)
    {
        PrintUserRecord(User);
        cout << endl;
    }

    cout << "__________________________________________________";
    cout << "________________________________________________\n";


}

bool UserExistsByUsername(string Username, string FileName)
{
    vector <stUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertLineToUser(Line);
            if (User.Username == Username)
            {
                MyFile.close();
                return true;
            }

            vUsers.push_back(User);
        }
        MyFile.close();
    }
    return false;
}

struct stPermissions
{
    char ShowClientList;
    char AddNewClinent;
    char DeleteClient;
    char UpdateClient;
    char FindClient;
    char Transactions;
    char ManageUsers;


};

void GivePermissions(stPermissions &ToCheck , short &Permissions)
{
    if (ToCheck.ShowClientList == 'y' || ToCheck.ShowClientList == 'Y')
        Permissions |= (1 << (enMainMenuOptions::ShowClientList -1));

    if (ToCheck.AddNewClinent == 'y' || ToCheck.AddNewClinent == 'Y')
        Permissions |= (1 << (enMainMenuOptions::AddClient - 1));

    if (ToCheck.DeleteClient == 'y' || ToCheck.DeleteClient == 'Y')
        Permissions |= (1 << (enMainMenuOptions::DeleteClient - 1));

    if (ToCheck.UpdateClient == 'y' || ToCheck.UpdateClient == 'Y')
        Permissions |= (1 << (enMainMenuOptions::UpdateClientInfo - 1));

    if (ToCheck.FindClient == 'y' || ToCheck.FindClient == 'Y')
        Permissions |= (1 << (enMainMenuOptions::FindClient - 1));

    if (ToCheck.Transactions == 'y' || ToCheck.Transactions == 'Y')
        Permissions |= (1 << (enMainMenuOptions::Transactions - 1));

    if (ToCheck.ManageUsers == 'y' || ToCheck.ManageUsers == 'Y')
        Permissions |= (1 << (enMainMenuOptions::enManageUsers - 1));

}

short ReadPermissions()
{
    short Permissions = 0;
    stPermissions ToCheck;

    char WantToGiveFullAccess = SureToDoSomething("\n\nDo you want to give full access? Y/N  ");

    if (WantToGiveFullAccess == 'y' || WantToGiveFullAccess == 'Y')
    {
        Permissions = -1;
        return Permissions;
    }

    cout << "\nDo you want to give access to:\n";

    cout << "\nShow client list? Y/N  ";
    cin >> ToCheck.ShowClientList;

    cout << "\nAdd New Client? Y/N  ";
    cin >> ToCheck.AddNewClinent;

    cout << "\nDelete Client? Y/N  ";
    cin >> ToCheck.DeleteClient;

    cout << "\nUpdate Client? Y/N  ";
    cin >> ToCheck.UpdateClient;

    cout << "\nFind Client? Y/N  ";
    cin >> ToCheck.FindClient;

    cout << "\nTransactions? Y/N  ";
    cin >> ToCheck.Transactions;

    cout << "\nManage Users? Y/N  ";
    cin >> ToCheck.ManageUsers;

    GivePermissions(ToCheck,Permissions);

    return Permissions;

}

stUser ReadNewUser()
{
    stUser User;

    cout << "\n\nEnter Username: ";
    // ws will extract all the whitespace characters
    getline(cin >> ws, User.Username);

    while (UserExistsByUsername(User.Username, UsersFileName))
    {
        cout << "\nUser with username[" << User.Username << "] already exists, enter another username. ";
        getline(cin >> ws, User.Username);
    }

    cout << "Enter Password. ";
    cin >> User.Password;

    User.Permissions = ReadPermissions();
       
    
    return User;
}

string ReadUsername()
{
    string s;

    cout << "Please enter username. ";
    getline(cin >>ws, s);

    return s;
}

void AddNewUser()
{
    stUser User;
    User = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertUserToLine(User));

}

void AddUsers()
{

    system("cls");
    cout << "-----------------------------\n";
    cout << "    Add new user screen\n";
    cout << "-----------------------------\n";


    char MoreClients = 'Y';

    do
    {
        cout << "Adding New User:";
        AddNewUser();

        cout << "\nUser Added Successfully, do you want to add more users? Y/N ";
        cin >> MoreClients;

    } while (MoreClients == 'y' || MoreClients == 'Y');

}

void PrintUserCard(stUser User)
{
    cout << "\nThe following are the User details:";
    cout << "\n---------------------------------------";
    cout << "\nUsername     : " << User.Username;
    cout << "\nPassword     : " << User.Password;
    cout << "\nPermissions  : " << User.Permissions;
    cout << "\n---------------------------------------\n";

}

void SaveUsersDataToFile(string FileName, vector <stUser>& vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (stUser& C : vUsers)
        {
            if (C.MarkForDeletion == false)
            {
                DataLine = ConvertUserToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

}

bool MarkUserForDeletionByUsername(string Username, vector <stUser>& vUsers)
{
    for (stUser& C : vUsers)
    {
        if (C.Username == Username)
        {
            C.MarkForDeletion = true;
            return true;
        }
    }

    return false;
}

bool DeleteUserByUsername(vector <stUser>& vUsers)
{
    system("cls");
    cout << "-----------------------------\n";
    cout << "     Delete user screen\n";
    cout << "-----------------------------\n";
    string Username = ReadUsername();

    if (Username == "Admin")
    {
        cout << "\nAdmin can not be deleted!!!\n";
        return 0;
    }

    stUser User;
    char DeleteClient = 'n';

    if (FindUserByUsernameAndPassword(Username, User.Password, User))
    {
        PrintUserCard(User);

        cout << "\nAre you sure you want to delete this User?  y/n   ";
        cin >> DeleteClient;

        if (DeleteClient == 'y' || DeleteClient == 'Y')
        {
            MarkUserForDeletionByUsername(Username, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);

            //Refresh Clients
            vUsers = LoadUsersDataFromFile(UsersFileName);

            cout << "\n\nUser Deleted Successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "\nUser with username (" << Username << ") is Not Found!\n";
        return false;
    }

}

stUser ChangeUserRecord(string Username)
{
    stUser User;

    User.Username = Username;

    cout << "\nEnter Password: ";
    cin >> User.Password;

    User.Permissions = ReadPermissions();

    return User;

}

bool UpdateUserByUsername( vector <stUser>& vUsers)
{
    system("cls");
    cout << "-----------------------------\n";
    cout << "     Update user screen\n";
    cout << "-----------------------------\n";

    string Username = ReadUsername();
    
    stUser User;
    char UpdateClient = 'n';

    if (FindUserByUsernameAndPassword(Username, User.Password, User))
    {
        PrintUserCard(User);

        cout << "\nAre you sure you want to update this User?  y/n   ";
        cin >> UpdateClient;

        if (UpdateClient == 'y' || UpdateClient == 'Y')
        {
            for (stUser& C : vUsers)
            {
                if (C.Username == Username)
                {
                    C = ChangeUserRecord(Username);
                    break;
                }
            }

            SaveUsersDataToFile(UsersFileName, vUsers);

            cout << "\n\nUser Updated Successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "\nUser with username (" << Username << ") is Not Found!";
        return false;
    }

}

void ShowUserByUsername( vector <stUser> &vUsers)
{
    system("cls");
    cout << "-----------------------------\n";
    cout << "     Find user screen\n";
    cout << "-----------------------------\n";
    string Username = ReadUsername();

    stUser User;

    while (!FindUserByUsernameAndPassword(Username, User.Password, User))
    {
        cout << "\nUser with username (" << Username << ") is Not Found!\n";
        Username = ReadUsername();
    }

    PrintUserCard(User);

}

bool ManageUsers(enMangeUsersOptions WhatToDo)
{
    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    switch (WhatToDo)
    {
    case enMangeUsersOptions::ListUsers:
    {
        PrintAllUsersData(vUsers);
        break;
    }
    case enMangeUsersOptions::AddUser:
    {
        AddUsers();
        break;
    }
    case enMangeUsersOptions::DeleteUser:
    {
        
        DeleteUserByUsername(vUsers);
        break;
    }
    case enMangeUsersOptions::UpdateUser:
    {
        UpdateUserByUsername(vUsers);
        break;
    }
    case enMangeUsersOptions::FindUser:
    {
        
        ShowUserByUsername(vUsers);
        break;
    }
    case enMangeUsersOptions::MainMenu:
    {
        return 0;
    }
    }

    GoBackToManageUsers();
}

bool DoesUserHavePermission( enMainMenuOptions ToDo)
{
    return (CurrentUser.Permissions & (1 << (ToDo - 1))) != 0;
}

void AccessDenied()
{
    system("cls");
    cout << "---------------------------------------\n";
    cout << "Access denied,\nYou do not have the permission to do this,\nPlease contact your admin\n";
    cout << "---------------------------------------\n";
    GoBackToMainMenu();
    
}

bool ExecuteUsersCommand(enMainMenuOptions WhatToDo)
{
    vector <stClientInfo> vClients = LoadClientsDataFromFile(ClientsFileName);
    enTransactionsMenuOptions Choice;
    enMangeUsersOptions Option;
    if(WhatToDo != enMainMenuOptions::Logout)
    {
        if (!DoesUserHavePermission( WhatToDo))
        {
            AccessDenied();
            return 0;
        }
    }
    
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
            Choice = (enTransactionsMenuOptions)ChooseOperation(1, 4);
            PerformTransactions(Choice, vClients);
        } while (Choice != enTransactionsMenuOptions::enMainMenu);
    }
    case enMainMenuOptions::enManageUsers:
    {

        do
        {
            ManageUsersHeader();
            Option = (enMangeUsersOptions)ChooseOperation(1, 6);
            ManageUsers(Option);
        } while (Option != enMangeUsersOptions::MainMenu);

    }
    case enMainMenuOptions::Logout:
    {
        return 0;
    }

    }
    GoBackToMainMenu();
}

void EnterMainMenu()
{
    enMainMenuOptions WhatToDo;

    do
    {
        DisplayMainMenu();
        WhatToDo = (enMainMenuOptions)ChooseOperation(1,8);
        ExecuteUsersCommand(WhatToDo);
    } while (WhatToDo != enMainMenuOptions::Logout);


}




bool LoadUserInfo(string Username, short Password)
{
    if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
        return true;
    else
        return false;

}

void LogIn()
{

    bool LoginFailed = false;
    string Username;
    short Password;

    do
    {
        system("cls");

        cout << "------------------------------\n";
        cout << "         Login Screen\n";
        cout << "------------------------------\n";

        if (LoginFailed)
        {
            cout << "Ivalid Username/Password!\n";
        }

        cout << "Enter Username.  ";
        cin >> Username;
        cout << "Enter Password.  ";
        cin >> Password;

        LoginFailed = !LoadUserInfo(Username, Password);

    } while (LoginFailed);

    
    EnterMainMenu();

}

int main()
{
    while(true)
    LogIn();

    return 0;
}
