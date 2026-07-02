#include <iostream>
#include <iomanip>
#include<fstream>
#include <string>
#include <vector>
using namespace std;

const string ClientsFileName = "Clients.txt";

enum enATMOptions { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eLogout = 5 };

enum enQuickWithdrawOptions
{
    Twenty = 1, Fifty = 2, Hundred = 3, TwoHundred = 4, FourHundred = 5, SixHundred = 6,
    EightHundred = 7, Thousand = 8, Exit = 9
};

struct stClientInfo
{
    string AccountNumber;
    string PinCode;
    string FullName;
    string PhoneNumber;
    double AccountBalance;
    bool MarkForDelete = false;
};

stClientInfo CurrentClient;

char SureToDoSomething(string Message)
{
    char Sure;
    cout << Message;
    cin >> Sure;

    return Sure;
}

vector <string> SplitString(string S1, string delim)
{
    vector <string> Splitted;

    short pos = 0;
    string sWord;

    while ((pos = S1.find(delim)) != string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            Splitted.push_back(sWord);
        }

        S1.erase(0, pos + delim.length());
    }

    if (S1 != "")
    {
        Splitted.push_back(S1);
    }

    return Splitted;
}

string JoinString(vector <string> vString, string delim)
{
    string S1 = "";

    for (string& s : vString)
    {
        S1 += s + delim;
    }

    return S1.substr(0, S1.length() - delim.length());
}

short ChooseOperation(short From, short To)
{
    short WhatYouWantToDo;
    do
    {
        printf("Choose what you want to do. [%d to %d]? ", From, To);
        cin >> WhatYouWantToDo;
    } while (WhatYouWantToDo < From || WhatYouWantToDo>To);

    return WhatYouWantToDo;
}

stClientInfo ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    stClientInfo Client;
    vector <string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.FullName = vClientData[2];
    Client.PhoneNumber = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

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

bool FindClientByAccountNumberAndPinCode(string AccountNumber,string PinCode, stClientInfo& Client)
{
    vector <stClientInfo> vClients = LoadClientsDataFromFile(ClientsFileName);

    for (stClientInfo C : vClients)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }
    }
    return false;

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

void LoginHeader()
{
    system("cls");

    cout << "------------------------\n";
    cout << "\tLogin Screen\n";
    cout << "------------------------\n";
}

void ATMHeader()
{
    system("cls");
    cout << "====================================\n";
    cout << "\t\tATM\n";
    cout << "====================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "====================================\n";

}

void QuickWithdrawHeader()
{

    system("cls");
    cout << "=======================================\n";
    cout << "\t\tQuick Withdraw\n";
    cout << "=======================================\n";
    cout << "\t[1] 20  \t[2] 50\n";
    cout << "\t[3] 100 \t[4] 200\n";
    cout << "\t[5] 400 \t[6] 600\n";
    cout << "\t[7] 800 \t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "=======================================\n";
    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;



}

void GoBackToATMScreen()
{
    cout << "\nPress any key to go back to ATM Screen...";
    system("pause>nul");
}

short GetAmountOfOption(enQuickWithdrawOptions Option)
{
    switch (Option)
    {
    case enQuickWithdrawOptions::Twenty:
        return 20;
    case enQuickWithdrawOptions::Fifty:
        return 50;
    case enQuickWithdrawOptions::Hundred:
        return 100;
    case enQuickWithdrawOptions::TwoHundred:
        return 200;
    case enQuickWithdrawOptions::FourHundred:
        return 400;
    case enQuickWithdrawOptions::SixHundred:
        return 600;
    case enQuickWithdrawOptions::EightHundred:
        return 800;
    case enQuickWithdrawOptions::Thousand:
        return 1000;
    }
    
}

bool IsEnoughBalance(short AmountToWithdraw)
{
    if (AmountToWithdraw > CurrentClient.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice\n";
        cout << "Press any key to continue...\n";
        system("pause>nul");
        return false;
    }

    return true;
}

void QuickWithdraw();
void NormalWithdraw();
void Deposit();

void ChangeBalance(short AmountToTransact )
{
    vector <stClientInfo> vClients = LoadClientsDataFromFile(ClientsFileName);


    char S = SureToDoSomething("\n\nAre you sure you want to perform this transaction? y/n . ");

    if (toupper(S) == 'Y')
    {
        
            CurrentClient.AccountBalance += AmountToTransact;

        cout << "Done successfully, New Balance: " << CurrentClient.AccountBalance << endl;

    }

    for (stClientInfo& C : vClients)
    {
        if (C.AccountNumber == CurrentClient.AccountNumber)
            C.AccountBalance = CurrentClient.AccountBalance;
    }

    SaveClientsDataToFile(ClientsFileName, vClients);
}

enQuickWithdrawOptions ChooseAmount()
{
    short NumberOfAmount = 0;

    do
    {
        cout << "Choose the amount you want to withdraw\n";
        cin >> NumberOfAmount;

    } while (NumberOfAmount < 1 || NumberOfAmount>9);

    return (enQuickWithdrawOptions)NumberOfAmount;
}

short ReadNumberMultipleOfFive()
{
    short AmountToWithdraw = 0;

    do
    {
        cout << "Enter an amount that is a multiple of 5 . ";
        cin >> AmountToWithdraw;
    } while (!(AmountToWithdraw % 5 == 0));

    return AmountToWithdraw;
}

void QuickWithdraw()
{
    short AmountToWithdraw = 0;

    do
    {
        QuickWithdrawHeader();

        AmountToWithdraw = GetAmountOfOption(ChooseAmount());

        IsEnoughBalance(AmountToWithdraw);

    } while (AmountToWithdraw > CurrentClient.AccountBalance);

    ChangeBalance(AmountToWithdraw*-1);


}

void NormalWithdraw()
{
    short AmountToWithdraw = 0;
   
    do
    {
        system("cls");
        cout << "=================================================\n";
        cout << "\t\tNormal Withdraw\n";
        cout << "=================================================\n";

        AmountToWithdraw = ReadNumberMultipleOfFive();

        IsEnoughBalance(AmountToWithdraw);
        
    } while (AmountToWithdraw > CurrentClient.AccountBalance);

    ChangeBalance(AmountToWithdraw*-1);

}

void Deposit()
{
    short AmountToDeposit = 0;

    system("cls");
    cout << "===================================\n";
    cout << "\t\tDeposit\n";
    cout << "===================================\n";

    AmountToDeposit = ReadNumberMultipleOfFive();

    ChangeBalance(AmountToDeposit);
}

void ShowBalance()
{
    system("cls");
    cout << "=================================================\n";
    cout << "\t\tBalance\n";
    cout << "=================================================\n";
    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;

}

bool PerformOperation(enATMOptions &Opeartion)
{

    switch(Opeartion)
    {
    case enATMOptions::eQuickWithdraw:
    {
        QuickWithdraw();
        break;
    }
    case enATMOptions::eNormalWithdraw:
    {
        NormalWithdraw();
        break;
    }
    case enATMOptions::eDeposit:
    {
        Deposit();
        break;
    }
    case enATMOptions::eCheckBalance:
    {
        ShowBalance();
        break;
    }
    case enATMOptions::eLogout:
        return 0;
    }

    GoBackToATMScreen();
}

void ATM()
{
    enATMOptions Operation;

    do
    {
        ATMHeader();
        Operation = (enATMOptions)ChooseOperation(1, 5);
        PerformOperation(Operation);

    } while (Operation !=enATMOptions::eLogout);
}

void Login()
{
    bool LoginFailed = false;
    string AccountNumebr, PinCode;

    do
    {
        LoginHeader();

        if (LoginFailed)
            cout << "Invalid account number/PIN\n";

        cout << "Please enter account number.  ";
        cin >> AccountNumebr;
        cout << "Please enter PIN code.  ";
        cin >> PinCode;

        LoginFailed = !FindClientByAccountNumberAndPinCode(AccountNumebr, PinCode , CurrentClient);

    } while (LoginFailed);

    ATM();
}

int main()
{
    while (true)
        Login();

    return 0;
}
