#include <iostream>
#include<stdio.h>
#include<string.h>
#include <conio.h>
#include <fstream>

using namespace std;

//bill - DBMS
//price - dept(s)
//code -id
//show - displayAll
//add -insert
//search - select
//edit - update
//del - delete_
//invoice - database
//menu - login

class DBMS
{
    private: 
        int id;
        string dept;
        string name;
        
    public: 
        void login(); //Done
        void admin(); //Done
        void insert(); //Done
        void select(); //Done
        void update(); //Done
        void delete_(); //Done
        void displayAll(); //Done
};

//Login
void DBMS :: login()
{
p:
    system("cls");
    int choice;
    char ch;
    string username, pass;
    cout << "\n\n\t\t\tSQL Workspace:";
    cout << "\n\n 1.Admin";
    cout << "\n 2.Exit";
    cout << "\n\n Enter your choice : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        system("cls");
        cout << "\n\n\t\t\tLogin System";
        cout << "\n\n Username : ";
        cin >> username;
        cout << "\n\n Password :";
        
        for (int i = 1; i <= 6; i++)
        {
            ch = getch();
            pass += ch;
            cout << "+";
        }
        
        if (username == "123" && pass == "123456")
        {
            admin();
        }
        
        else
        {
            cout << "\n\n Invalid Username & Password";
        }
        break; //Go to case 2 if no break
    case 2:
        exit(0);
    
    default:
        cout << "\n\nInvalid value...Please try again";
    }
    
    getch();
    goto p;
}

//Admin
void DBMS :: admin()
{
p:
    int choice;

    system("cls");
    cout << "\n\n\t\t\tAdmin Panel";
    cout << "\n\n 1. INSERT";
    cout << "\n 2. SELECT";
    cout << "\n 3. UPDATE";
    cout << "\n 4. DELETE";
    cout << "\n 5. SELECT *";
    cout << "\n 6. LOGOUT";
    cout << "\n\n Enter your choice : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        insert();
        break;
    case 2:
        select();
        break;
    case 3:
        update();
        break;
    case 4:
        delete_();
        break;
    case 5:
        displayAll();
        break;
    case 6:
        login();
    default:
        cout << "\n\n Invalid value...Please try again";
    }
    getch();
    goto p;
}

//INSERT
void DBMS :: insert()
{
p:
    system("cls");

    fstream file;
    int i, found = 0;
    string d;
    string n;
    cout << "\n\n\t\t\tInsert Entry";
    cout << "\n\n id : ";
    cin >> id;
    cout << "\n\n Name : ";
    cin >> name;
    cout << "\n\n Dept. : ";
    cin >> dept;

    file.open("data.txt", ios::in);
    if (!file)
    {
        file.open("data.txt", ios::app | ios::out); // if file doesnt exist,send the records to file
        file << " " << id << " " << name << " " << dept << "\n";
        file.close();
    }

    else
    {
        file >> i >> n >> d;
        while (!file.eof())
        {
            if (i == id)
            {
                found++;
            }
            file >> i >> n >> d;
        }
        
        file.close();
        if (found == 1)
        {
            goto p;
        }

        else
        {
            file.open("data.txt", ios::app|ios::out);
            file << " " << id << " " << name << " " << dept<< "\n";
            file.close();
        }
    }
    cout << "\n\n\t\t Insert Successful";
}

//SELECT
void DBMS :: select()
{
    system("cls");
    fstream file;
    int i, found = 0;
    cout << "\n\n\t\t\tSelect Entry";
    cout << "\n\n id : ";
    cin >> i;
    file.open("data.txt", ios::in);
    
    if (!file)
    {
        cout << "\n\n File Opening Error";
    }
    
    else
    {
        file >> id >> name >> dept;
        while (!file.eof())
        {
            if (i == id)
            {
                system("cls");
                cout << "\n\n\t\t\tSearch Item";
                cout << "\n\n id : " << id;
                cout << "\n\n Name : " << name;
                cout << "\n\n Dept. : " << dept;
                found++;
            }
            file >> id >> name >> dept;
        }
        file.close();
        if (found == 0)
            cout << "\n\n Record Can't Found";
    }
}

//UPDATE
void DBMS :: update()
{
    system("cls");

    fstream file, file1;
    int i, found = 0, c;
    string d;
    string n;
    
    cout << "\n\n\t\t\tUpdate Entry";
    cout << "\n\n id : ";
    cin >> i;
    file.open("data.txt", ios::in);
    
    if (!file)
    {
        cout << "\n\n File Opening Error";
    }

    else
    {
        file1.open("data1.txt", ios::app | ios::out);
        while (!file.eof())
        {
            if (i == id)
            {
                cout << "\n\n id : ";
                cin >> c;
                cout << "\n\n Name : ";
                cin >> n;
                cout << "\n\n Dept. : ";
                cin >> d;
                file1 << " " << c << " " << n << " " << d << " " << "\n";
                cout << "\n\n\n\t\t Update Successful";
                found++;
            }

            else
            {
                file1 << " " << id << " " << name << " " << dept << " " << "\n";
            }

            file >> id >> name >> dept;
        }

        file.close();
        file1.close();
        remove("data.txt");
        rename("data1.txt", "data.txt");
        if (found == 0)
            cout << "\n\n Record Can't Found";
    }
}

//DELETE
void DBMS :: delete_()
{
    system("cls");
    fstream file, file1;
    int i, found = 0;
    cout << "\n\n\t\t\tDelete Entry";
    cout << "\n\n id : ";
    cin >> i;
    file.open("data.txt", ios::in);
    
    if (!file)
    {
        cout << "\n\n File openning error...";
    }

    else
    {
        file1.open("data1.txt", ios::app | ios::out);
        file >> id >> name >> dept;
        while (!file.eof())
        {
            if (id == i)
            {
                cout << "\n\n Delete Successful";
                found++;
            }

            else
            {
                file1 << " " << id << " " << name << " " << dept << "\n";
            }
            file >> id >> name >> dept;
        }
        file.close();
        file1.close();
        remove("data.txt");
        rename("data1.txt", "data.txt");
        
        if (found == 0)
            cout << "\n\n Record Cant Found";
    }
}

//DisplayAll
void DBMS :: displayAll()
{
    system("cls");

    fstream file;
    cout << "\n\n\t\t\tTABLE";
    file.open("data.txt", ios::in);
    if (!file)
    {
        cout << "\n\n File opening errror...";
    }
    else
    {
        cout << "\n\n id\t\tName\t\tDept.";
        file >> id >> name >> dept;
        while (!file.eof())
        {
            cout << "\n " << id << "\t\t" << name << "\t\t" << dept;
            file >> id >> name >> dept;
        }
        file.close();
    }
}

int main()
{
    DBMS dbms;
    dbms.login();
}
