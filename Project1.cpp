//Jasmine Lawrence
//Project 1: This program will read each line from the text file, and display employee's information by employee ID. All infromation is stored in a sorted linked list. 

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//Defines the Employee attributes and types
struct Employee
{
    int employeeId;
    string firstName;
    string lastName;
    string phoneNumber;
    string emailAddress;
    double salary;
};

struct Node {
  Employee info;          //stores one employee's information
  Node* next;             //pointer to next node
};

//Defines the Linked List class to store Employee's information
class EmployeeList {
  private:
  Node* head;             //pointer that stores address of the first node in the list 
  public:
  EmployeeList(){         //constructor to initialize the head pointer to nullptr when function is called
    head = nullptr;
  }

  void insert(Employee employee){
    Node* newNode = new Node;  //create a new node and allocate memory for the new node
    newNode->info = employee;  //store copied employee information in the new node
    newNode->next = nullptr;   //initialize the next pointer to nullptr

    if(head == nullptr)       //checks if list is empty
    {
      head = newNode;         //if it is empty the new node becomes the first node in the list
    }
    else if (employee.employeeId < head->info.employeeId)     //checks if there is a smaller employee ID that should go first
    {
      newNode->next=head;             //if true then it takes the new node to the old first node
      head = newNode;                 //makes the new node the first node in the list
    }
    else {                                //if neither condition is true then find a position in the list for the new node to be inserted
      Node* current = head;                 //start at the first node in the list
      while(current->next != nullptr)       //continues to search through list while the the other node is still pointing to another node
      {
        if(current->next->info.employeeId > employee.employeeId)      //checks if the next ID is larger 
        {
          break;        //stops the search if the new node is supposed to go before the node with the larger ID
        }
        current = current->next;      //goes to the next node in the list
      }
      newNode->next = current->next;      //links the new node to the next node in the list
      current->next = newNode;            //links the current node to the new node
    }
  }

  void display()                        //displays all the employee information in the sorted linked list
  {
    Node* current = head;                       //starts at the beginning node
    cout << "Employee Information"<< endl;    
    while(current != nullptr){                                      //prints all the employee information by attribute until there are no more nodes
      cout<< "Employee ID: " << current->info.employeeId << endl;
      cout << "First Name: " << current->info.firstName << endl;
      cout << "Last Name: " << current->info.lastName << endl;
      cout << "Phone Number: " << current->info.phoneNumber << endl;
      cout << "Email Address: " << current->info.emailAddress << endl;
      cout << "Salary: " << current->info.salary << endl;
      current = current->next;
    }
  }

~EmployeeList() {           //deconstructor to free memory when list goes out of scope until every node is deleted
  while(head != nullptr){
    Node* oldNode = head;       //save the first node 
    head = head->next;          //move to next node
    delete oldNode;             //delete the old node's memore that was allocated
  }
}
};

//Begin Program execution in main function
int main(){

  ifstream inputFile("Week 1-employeeDataset_Project 1.txt");      //opens the text file to read employee information

  if (!inputFile) {             //checks if the file can be opened
    cout << "Could not open the file." << endl;
    return 1;               // Exit the program if the file cannot be opened 
  }

  EmployeeList employees;     //create empty linked list for employees
  Employee employee;          //create employee object to store the information being read from the file

while (inputFile >> employee.employeeId >> employee.firstName >> employee.lastName >> employee.phoneNumber >> employee.emailAddress >> employee.salary) 
{
  employees.insert(employee);       //insert the employee info into the linked list
}

if (!inputFile.eof()){
  cout<<"Error reading the file"<<endl;
  return 1;      // exit the program if there is an error reading the file
}

inputFile.close();        //close the file after reading all the information
employees.display();     //display the employee information in the sorted linked list format
return 0;       //exit the program successfully

}