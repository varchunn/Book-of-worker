#include <iostream>
#include <filesystem>
#include <cstring>
#include <cstdio>
#pragma warning(disable : 4996)

using namespace std;
struct worker
{
    char* surname;
    char* name;
    char* number;
    double salary;
};
bool isValidPhoneNumber(const char* phoneNumber) {
    if (strlen(phoneNumber) != 13) {
        return false;
    }
    if (phoneNumber[0] != '(' || phoneNumber[4] != ')' || phoneNumber[5] != ' ') {
        return false;
    }
    for (int i = 1; i <= 3; ++i) {
        if (!isdigit(phoneNumber[i])) {
            return false;
        }
    }
    for (int i = 6; i <= 12; ++i) {
        if (!isdigit(phoneNumber[i])) {
            return false;
        }
    }
    return true;
}

void inputPhoneNumber(char* phoneNumber, int size) {
    do {
        cout << "Please, enter the worker's phone number in format (xxx) xxxxxxx: ";
        cin.getline(phoneNumber, size);

        if (!isValidPhoneNumber(phoneNumber)) {
            cout << "Invalid phone number format! Please try again." << endl;
        }
    } while (!isValidPhoneNumber(phoneNumber));
}

worker create()
{
    worker st;
    char* surname = new char[120];
    char* name=new char[120];
    char* number = new char[100];
    cout << "Please, enter the surname of the worker"<<endl;
    cin.ignore();
    cin.getline(surname,120);
    int size = strlen(surname);
    st.surname = new char[size + 1];
    strcpy(st.surname, surname);
    /*for (int i = 0; i < size; i++)
    {
     st.surname[i] = surname[i];
    }*/
    cout << "Please, enter the name of the worker"<<endl;
    cin.getline(name,120);
    int size1 = strlen(name);
    st.name = new char[size1 + 1];
    strcpy(st.name, name);
    /*for (int i = 0; i < size1; i++)
    {
     st.name[i] = name[i];
    }*/
    cout << "Please, enter the number of the worker"<<endl;
    inputPhoneNumber(number, 100);
    int size2 = strlen(number);
    st.number = new char[size2 + 1];
    strcpy(st.number, number);
    /*for (int i = 0; i < size2; i++)
    {
     st.number[i] = number[i];
    }*/
    cout << "And please add salary of the worker"<<endl;
    cin >> st.salary;
    delete[]surname;
    delete[]name;
    delete[]number;
    return st;
}

void showorker(worker st)
{
    cout << endl;
    cout << "The name of your worker is - "<<st.name<<endl;
    cout << "The surname of your worker is - "<<st.surname<<endl;
    cout << "The number of your worker is - "<<st.number<<endl;
    cout << "Salary of your worker is - "<<st.salary<<endl;
    cout << "-----------------------------------------------------------"<<endl;
}
void arrayWorker(worker* workerArray, int n)
{
    for (int i = 0; i < n; i++)
    {
     showorker(workerArray[i]);
    }
}
void createArray(worker* workerArray, int &n)
{
    for (int i = 0; i < n; i++)
     {
      workerArray[i] = create();
     }
     arrayWorker(workerArray, n);
}
void sortBySurname(worker* workerArray, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(workerArray[j].surname, workerArray[j + 1].surname) > 0)
            {
                worker с = workerArray[j];
                workerArray[j] = workerArray[j + 1];
                workerArray[j + 1] = с;
            }
        }
    }
}
worker* searchSurname(worker* workerArray, int n, char*find)
{
    for (int i=0; i <n; i++)
    {
        if (strcmp(find, workerArray[i].surname)==0)
        {
            return &workerArray[i];
        }
    }
    return nullptr;
}
worker* searchSalary(worker* workerArray, int size, double salary)
{
    for (int i = 0; i < size; i++)
    {
        if (workerArray[i].salary == salary)
        {
            return &workerArray[i];
        }
    }
    return nullptr;
}


void deleteWorker(worker& st)//Я видаляю динамічну пам'ять котра була виділена під прізвище, ім'я та номер. В кінці програми функція в циклі буде викличена
{
    delete[] st.surname;
    delete[] st.name;
    delete[] st.number;
}
worker* addWorker(worker* workerArray, int& n)
{
    worker* newArray = new worker[n + 1];

    for (int i = 0; i < n; i++)
    {
        newArray[i] = workerArray[i];
    }

    newArray[n] = create();
    n++;

    delete[] workerArray;
    return newArray;
}

bool confirmDeletion() {
    char choice;
    do {
        cout << "Are you sure you want to delete this worker? (Yes - 1 or No - 2): ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                return true;
            }
            case 2:
            {
                return false;
            } default:
            {
                cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
            }
        }
    } while (true);

    return false;
}

worker* deleteWorkerBySurname(worker* workerArray, int& n, const char* surnameToDelete)
{
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(workerArray[i].surname, surnameToDelete) == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Worker with surname " << surnameToDelete << " not found!" << endl;
        return workerArray;
    }
    if (confirmDeletion()) {
            deleteWorker(workerArray[index]);

            for (int i = index; i < n - 1; i++) {
                workerArray[i] = workerArray[i + 1];
            }

            n--; // Зменшуємо розмір масиву
            worker* newArray = new worker[n];
            for (int i = 0; i < n; i++) {
                newArray[i] = workerArray[i];
            }

            delete[] workerArray;
            cout << "Worker deleted." << endl;
            return newArray;
        } else {
            cout << "Deletion cancelled." << endl;
            return workerArray;
        }
}
worker* loadFromFile(worker* workerArray, int& n)
{
    FILE* file = fopen("/Users/varaminenkova/Documents/programm/Book of workers/", "r");
    if (!file)
    {
        cout << "Error! Unable to open file." << endl;
        return workerArray;
    }
    char buffer[200];
    while (fgets(buffer, sizeof(buffer), file))
    {
        worker newWorker;
        char* token = strtok(buffer, "-");
        if (token != nullptr)
        {
            newWorker.surname = new char[strlen(token) + 1];
            strcpy(newWorker.surname, token);
        }

        token = strtok(nullptr, "-");
        if (token != nullptr)
        {
            newWorker.name = new char[strlen(token) + 1];
            strcpy(newWorker.name, token);
        }

        token = strtok(nullptr, "-");
        if (token != nullptr)
        {
            newWorker.number = new char[strlen(token) + 1];
            strcpy(newWorker.number, token);
        }

        token = strtok(nullptr, "-");
        if (token != nullptr)
        {
            newWorker.salary = atof(token);  // Перетворення рядка в число
        }
        workerArray = addWorker(workerArray, n);
    }

    fclose(file);
    return workerArray;
}
void saveToFile(worker* workerArray, int n)
{
    FILE* file = fopen("/Users/varaminenkova/Documents/programm/Book of workers/", "w");
    if (!file)
    {
        cout << "Error! Unable to open file." << endl;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "-\n", workerArray[i].surname, workerArray[i].name, workerArray[i].number, workerArray[i].salary);
    }

    fclose(file);
}

void deleteArray(worker* workerArray, int n)
{
    for (int i = 0; i < n; i++)
    {
        deleteWorker(workerArray[i]);
    }
    delete[] workerArray;
}
int main()
{
    
    int choice,n;
    worker* workerArray = nullptr;
 do
 {
 cout << "Hello! You are in book's menu. Please, choose an option" << endl;
 cout << "1 - Download information from file" << endl;
 cout << "2 - Download something into file" << endl;
 cout << "3 - Demonstration of all infromation from the book" << endl;
 cout << "4 - search information by surname" << endl;
 cout << "5 - search information by salary" << endl;
 cout << "6 - sort by surname" << endl;
 cout << "7 - add new worker" << endl;
 cout << "8 - delete worker" << endl;
 cout << "9 - End of programm" << endl;
 cin >> choice;
  switch (choice)
  {
  case 1:
  {
      workerArray = loadFromFile(workerArray, n);
                  cout << "Information loaded from file." << endl;
                  break;
  }
  case 2:
  {
      saveToFile(workerArray, n);
                  cout << "Information saved to file." << endl;
                  break;
  }
  case 3:
      {
          cout << "Please, enter how many workers in the book you will have" << endl;
              cin >> n;
              workerArray = new worker[n];
              createArray(workerArray, n);
              if (n > 0)
              {
                  arrayWorker(workerArray, n);
              }
              else
              {
                  cout << "The book is empty, please add workers first." << endl;
              }
              break;
  }
  case 4:
  {
      char* find = new char[125];
      cin.ignore();
      cout << endl;
      cout << "Enter please surname of worker you wanna find - ";
      cin.getline(find, 125);
      worker* result = searchSurname(workerArray, n, find);
      if (result != nullptr)
      {
          cout << "There is your worker:" << endl << "*************************************" << endl;
          showorker(*result);
      }
      else
      {
          cout << "Not found!" << endl;
      }
      delete[] find;
      break;
  }
  case 5:
  {
      double find;
      cout << endl;
      cout << "Enter please salary of worker you wanna find - ";
      cin >> find;
      worker* result = searchSalary(workerArray, n, find);
      
      if (result != nullptr)
      {
          cout << "There is your worker:" << endl << "*************************************" << endl;
          showorker(*result);
      }
      else
      {
          cout << "Not found!" << endl;
      }
      break;
  }
  case 6:
  {
      if (workerArray != nullptr && n > 0)
      {
          sortBySurname(workerArray, n);
          cout << "Workers sorted by surname." << endl;
          arrayWorker(workerArray, n);
      }
      else
                      {
                          cout << "There are noone in book, Please, fool book first" << endl;
                      }
   break;
  }
  case 7:
  {
      workerArray = addWorker(workerArray, n);
                  cout << "Worker added." << endl;
                  break;
  }
  case 8:
  {
      if (n > 0)
                  {
                      char surnameToDelete[125];
                      cin.ignore();
                      cout << "Enter the surname of the worker to delete: ";
                      cin.getline(surnameToDelete, 125);
                      workerArray = deleteWorkerBySurname(workerArray, n, surnameToDelete);
                      cout << "Worker deleted." << endl;
                  }
                  else
                  {
                      cout << "The book is empty, no workers to delete." << endl;
                  }
                  break;
  }
  case 9:
  {
      if (workerArray != nullptr)
          {
              deleteArray(workerArray, n);
          }
          cout << "Bye bye! Have a nice day!" << endl;
          return 0;
  }
  default:
  {
   cout << "incorrect, try again!";
   break;
  }
  }
 } while (true);
}


