#pragma once
#include <iostream>
#include <string>
#include "personlibrary/clsPerson.h"
#include "stringlibrary/clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNew = 2 };
    enMode _Mode;


    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete = false; 

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> _Vclients;
        fstream MyFile;

        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;

            while (getline(MyFile, line))
            {
               clsBankClient client = _ConvertLinetoClientObject(line);
                _Vclients.push_back(client);

            }
            MyFile.close();

        }

        return _Vclients;
    }

    static string _ConvertRecordToLine(clsBankClient clientData, string seperator = "#//#")
    {
        string ClientRecord = "";

        ClientRecord += clientData.FirstName + seperator;
        ClientRecord += clientData.LastName + seperator;
        ClientRecord += clientData.Email + seperator;
        ClientRecord += clientData.Phone + seperator;
        ClientRecord += clientData.AccountNumber() + seperator;
        ClientRecord += clientData.PinCode + seperator;
        ClientRecord += to_string(clientData.AccountBalance);

        return ClientRecord;
    }

    static void _DeleteAndSaveClientDataTofile( vector <clsBankClient> _Vclients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        string line;

        if (MyFile.is_open())
        {
            for (clsBankClient C : _Vclients)
            {
                if (C._MarkForDelete == false)
                {
                  line = _ConvertRecordToLine(C);
                  MyFile << line << endl;
                }
            }
            MyFile.close();

        }
    }

    static void _SaveDataToFile(vector <clsBankClient>& _Vclients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        string line;

        if (MyFile.is_open())
        {
            for (clsBankClient C : _Vclients)
            {
                    line = _ConvertRecordToLine(C);
                    MyFile << line << endl;
            }
            MyFile.close();

        }
    }

    void _Update()
    {
        vector <clsBankClient> _Vclient;
        _Vclient = _LoadClientsDataFromFile();

        for (clsBankClient& C : _Vclient)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveDataToFile(_Vclient);
    }

    void _Addnew()
    {
        addDataToFile(_ConvertRecordToLine(*this));
    }

    void addDataToFile( string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
       
    }

    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }


    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string Username)
    {
        string stDataline = _PrepareTransferLogRecord(Amount, DestinationClient, Username);

        fstream Myfile;
        Myfile.open("TransferLog.txt", ios::out | ios::app);
        if (Myfile.is_open())
        {
            Myfile << stDataline << endl;
            Myfile.close();
        }

    }


    struct stTrnsferLogRecord;

    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTrnsferLogRecord TrnsferLogRecord;
       
        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;

    }



public:



    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;

    };

    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        return (!Client1.IsEmpty());
    }

    enum enSaveResult {svFailedEmptyObject = 0, svSucceded = 1, svFailedAccountNumberExicts = 2};

    enSaveResult Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            return enSaveResult::svFailedEmptyObject;
        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResult::svSucceded;
            break;
        }
        case enMode::AddNew:
        {
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return clsBankClient::enSaveResult::svFailedAccountNumberExicts;
            }
            else
            {
                _Addnew();
                _Mode = enMode::UpdateMode;
                return enSaveResult::svSucceded;
            }
            break;
        }
        }
    }
  
    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNew, "", "", "", "", AccountNumber, "", 0);
    }

    bool DeleteClient()
    {
        vector <clsBankClient> _Vclient;
        _Vclient = _LoadClientsDataFromFile();

        for (clsBankClient& C : _Vclient)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkForDelete = true;
                break;

            }
        }
        _DeleteAndSaveClientDataTofile(_Vclient);
        *this = _GetEmptyClientObject();

         return true;
    }

    static vector <clsBankClient> GetClientList()
    {
            return _LoadClientsDataFromFile(); 
    }

    static double GetTotalClientBalance()
    {

        vector <clsBankClient> VclientData = GetClientList();

        double TotalBalance = 0;

        for (clsBankClient& C : VclientData)
        {
            TotalBalance += C.AccountBalance;

        }

       return TotalBalance;
       

    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }
    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }

    }

    bool Transfer(float Amount, clsBankClient& DestinationClient, string Username)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
       _RegisterTransferLog(Amount, DestinationClient, Username);
        return true;
    }

    static  vector <stTrnsferLogRecord> GetTransfersLogList()
    {
        vector <stTrnsferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stTrnsferLogRecord TransferRecord;

            while (getline(MyFile, Line))
            {

                TransferRecord = _ConvertTransferLogLineToRecord(Line);

                vTransferLogRecord.push_back(TransferRecord);

            }

            MyFile.close();

        }

        return vTransferLogRecord;

    }



};

