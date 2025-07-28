#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <memory>
#include <chrono>
#include <thread>

using namespace std;

class Node {
    public:
    int patient_id;
    string name;
    int age;
    char gender;
    string disease;
    bool status;
    Node* next;

    Node(int id) {
        patient_id = id;
	}

    Node(int id, string name, int age, char gender, string disease) {
        patient_id = id;
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->disease = disease;
        status = true;
        next = NULL;
	}
};

void clearScreen() {
    // Check the operating system
    #ifdef _WIN32
        system("cls"); // Clear screen for Windows
    #else
        system("clear"); // Clear screen for Unix/Linux/Mac
    #endif
}

void admit_patient(Node*& head, int id) {
    string name,disease;
    char gender;
    int age;

    cout<<"Enter Patient Name         : ";
    getline(cin, name);
    cout<<"Enter Patient Age          : ";
    cin>>age;
    cout<<"Enter Patient Gender (M/F) : ";
    cin >> gender;
    cout<<"Enter Patient Disease      : ";
    // getline(cin, disease);
    cin >> disease;
    Node* newnode = new Node(id,name,age,gender,disease);
    
    if (head == NULL) 
    {
        head = newnode;
    } 
    else 
    {
        Node* temp = head;
        while (temp->next != NULL) 
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
    newnode->status=true;
}

void display_a_patient(Node* head) {   
    cout<<"Patient ID     : "<<head->patient_id<<endl;
    cout<<"Patient Name   : "<<head->name<<endl;
    cout<<"Age            : "<<head->age<<endl;
    cout<<"Gender         : "<<head->gender<<endl;
    cout<<"Disease        : "<<head->disease<<endl;
    cout<<"Patient status : "<<(head->status ? "Admitted " : "Discharged ")<<endl<<endl;
}

Node* search_patient(Node*head,string name) {
    Node* temp = head;
    while(temp->name !=name)
    {
        temp = temp->next;
    }
    return temp;
    
}

void display_all_admitted_patients(Node* head) {   
    if(head == NULL) {
        return;
    }
    display_a_patient(head);
    cout << "--------------------------" << endl;
    display_all_admitted_patients(head->next);
}

void display_all_discharged_patients(Node* head) {   
    Node* temp = head;
    while(temp != NULL)
    {
        if(!temp->status)
        {
            display_a_patient(temp);
        }
        temp = temp->next;
    }
}

void discharge_patient(Node*head,string name) {
    Node* discharged;
    cout<<"Patient : " <<endl;
    discharged = search_patient(head,name);
    display_a_patient(discharged);
    cout<<endl<<"is discharged"<<endl;
    discharged->status=false;
}

void display_all_patients(Node* head) {   
    Node* temp = head;
    cout<<"\nList of all patients  : \n";
    while(temp != NULL)
    {
        display_a_patient(temp);
        temp = temp->next;
    }
}

int main()
{
    Node* head = NULL;
    string name;
    char choice;
    // int discharge_id;
    // int search_id;
    int assigned_id=1;
    bool loop = true;
    while(loop) {
        clearScreen();
        cout << "=== Hospital Management System ===" << endl;
        cout << "1) Admit a patient"<<endl;
        cout << "2) Discharge a patient"<<endl;
        cout << "3) Display patient detail"<<endl;
        cout << "4) Display all admitted patients"<<endl;
        cout << "5) Display all discharged patients"<<endl;
        cout << "6) Display patient"<<endl;
        cout << "7) Delete a patient"<<endl;
        cout << "8) Exit"<<endl<<endl;
        cout << "Enter a choice : ";
        cin>>choice;
        // Ignore the newline character left in the input buffer
        // cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');   
        
        switch(choice)
        {
            case '1':         // to admit a patient
                clearScreen();
                cout << "Patient id is               : " << assigned_id << endl;
                admit_patient(head,assigned_id++);
                
                break;
            case '2':         // to discharge a patient
                clearScreen();
                cout<<"Enter patient name   : ";
                cin>>name;
                if (search_patient(head,name) == NULL) {
                    cout<<"Patient not found \n";
                } else {
                    discharge_patient(head,name);
                }
                break;
            case '3':         // to display a patient detail
                clearScreen();
                cout<<"Enter patient name   : ";
                getline(cin, name);
                if(search_patient(head, name) == NULL) {
                    cout<<"Invalid patient id \n";
                } else {
                    display_a_patient(search_patient(head,name));
                }
                break;
            case '4':     // to display all currently admitted patients
                clearScreen();
                display_all_admitted_patients(head);
                cout << "------ Press Enter To Continue -------" << endl;
                cin.get();
                break;
            case '5':     // to display all discharged patients
                clearScreen();
                display_all_discharged_patients(head);
                break;
            case '6':     // to display all patients of hospital
                clearScreen();
                display_all_patients(head);
                break;
            case '7':     // to delete a record
                break;
            case '8':     // to terminate the application
                cout<<"\t\t\t EXITING . . . . \n";
                loop = false;
                break;
            default:
                cout<<"Invalid option Choose Again!!";
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    }
    return 0;
}