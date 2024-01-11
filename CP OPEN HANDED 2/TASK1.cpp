#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<iostream>
using namespace std;

struct books
{
    string title;
    int year;
    string genre;
};

books data[6];

void main_menu();
void take_input_of_books();
bool compareBooks(const books& a, const books& b);
void readDataFromFile(const string& fileName);

int main()
{
    main_menu();
    return 0;
}

void take_input_of_books()
{
    int user_input;
    for (int i = 0; i < 6; i++)
    {
        if (i == 0)
        {
            cout << "\n\t Enter Data For The Book.\n" << endl;
        }
        if (i != 0)
        {
            cout << "\n\tNow Enter Data For The Next Book.\n" << endl;
        }
        cout << "Enter Book Title Name : ";
        getline(cin, ::data[i].title);
        cout << "Enter The Publication Year : ";
        cin >> ::data[i].year;
        cin.ignore();
        cout << "Enter The Genre Of The Book (Fiction Or Non Fiction) : ";
        getline(cin, ::data[i].genre);
    }
    cout << "\n\nPress 1 to get back to main menu and save books : ";
    cin >> user_input;
    if (user_input == 1)
    {
        system("cls");
        main_menu();
        exit(0);
    }
}

void writeDataToFile(const string& fileName, const string& genre)
{
    int user_input;
    ofstream outFile(fileName);
    if (outFile.is_open())
    {
        for (int i = 0; i < 6; i++)
        {
            if (::data[i].genre == genre)
            {
                outFile << ::data[i].title << "\n";
                outFile << ::data[i].year << "\n";
                outFile << ::data[i].genre << "\n";
            }
        }

        outFile.close();
        cout << "Data has been written to the file: " << fileName << endl;
    }
    else
    {
        cout << "Unable to open the file: " << fileName << endl;
    }
    cout << "\n\nPress 1 to get back to main menu : ";
    cin >> user_input;
    if (user_input == 1)
    {
        system("cls");
        main_menu();
        exit(0);
    }
}
bool compareBooks(const books& a, const books& b)
{
    return a.year < b.year;
}

void readDataFromFile(const string& fileName)
{
    int user_input;
    ifstream inFile(fileName);
    if (inFile.is_open())
    {
        vector<books> booksList; // Store books in a vector

        string title;
        int year;
        string genre;

        while (getline(inFile, title) && inFile >> year >> ws && getline(inFile, genre))
        {
            booksList.push_back({ title, year, genre });
        }

        inFile.close();

        // Sort the books based on the publication year
        sort(booksList.begin(), booksList.end(), compareBooks);

        // Display the sorted books
        cout << "\nData from " << fileName << " (sorted by publication year):\n" << endl;
        for (const auto& book : booksList)
        {
            cout << "Title: " << book.title << "\tYear: " << book.year << "\tGenre: " << book.genre << endl;
        }
    }
    else
    {
        cout << "Unable to open the file: " << fileName << endl;
    }
    cout << "\n\nPress 1 to get back to the main menu: ";
    cin >> user_input;
    if (user_input == 1)
    {
        system("cls");
        main_menu();
        exit(0);
    }
}


void main_menu()
{
    char user_choice;
    cout << "\n\t Welcome To Mudassir Book System\n" << endl;
    cout << "1. Enter Data For Books\n2. Save Fiction Books to File\n3. Save Non-Fiction Books to File\n4. Display Fiction Books\n5. Display Non-Fiction Books\n6. Any Key to Exit\nChoose Your Action(1-6) : ";
    cin >> user_choice;
    cin.ignore();
    switch (user_choice)
    {
    case '1':
        system("cls");
        take_input_of_books();
        break;
    case '2':
        system("cls");
        writeDataToFile("fiction_books.txt", "Fiction");
        break;
    case '3':
        system("cls");
        writeDataToFile("non_fiction_books.txt", "Non Fiction");
        break;
    case '4':
        system("cls");
        readDataFromFile("fiction_books.txt");
        break;
    case '5':
        system("cls");
        readDataFromFile("non_fiction_books.txt");
        break;
    default:
        cout << "Good Bye !" << endl;
        exit(0);
    }
}