#include <iostream>
#include <string>
#include<cstdlib>
#include<cstdlib>
#include<cctype>
using namespace std;
class Node
{
    public:
    int patient_id;
    string name;
    string age;
    string gender;
    string disease;
    bool status;
    Node* next;
    Node(int id,string name,string age,string gender,string disease)
    {
        patient_id = id;
        this->name=name;
        this->age=age;
        this->gender=gender;
        this->disease=disease;
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

static bool isAgeValid(string age) 
{
    if (age.empty() || age.size() > 3)      // allows 1–3 digits
    {
        return false;
      }  
    for(int i = 0; i < age.size(); i++) {
        if(!isdigit(age[i])) {
            return false;
        }
    }
    return true;
}

bool search_for_duplicate_admission(Node*head,const string& search_name,const string& search_age,const string& search_gender,const string& search_disease)
{
    Node*temp = head;
    while(temp != NULL)
    {
        if(temp->name==search_name && temp->age==search_age  && temp->gender==search_gender && temp->disease==search_disease && temp->status==true)
        {
            return true;
        }
        temp=temp->next;
    }
    return false;
}

bool admit_patient(Node*& head, int id) 
 {
    string name;
    string age;
    string gender;
    string disease;
    cout<<"Enter the name : ";
    getline(cin>>ws,name);
    cout<<"Enter Patient Age : ";
    getline(cin>>ws,age);
    if (isAgeValid(age)!=true) 
    {
        cout<<"Invalid Input!!"<<endl;
        return false;
    }
    cout<<"Enter Patient Gender(M/F) : ";
    getline(cin >> ws,gender);
    cout<<"Enter Patient Disease : ";
    getline(cin >> ws,disease);
    if(search_for_duplicate_admission(head,name,age,gender,disease)==true)
    {
        cout << "Patient with the same name is already admitted.\n";
        return false;
    }
    else
    {
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
    return true;
}

void display_a_patient(Node* head)
{   
    cout<<endl;
    cout << "----------------------------\n";
    cout<<"Patient ID : "<<head->patient_id<<endl;
    cout<<"Patient Name : "<<head->name<<endl;
    cout<<"Age : "<<head->age<<endl;
    cout<<"Gender : "<<head->gender<<endl;
    cout<<"Disease : "<<head->disease<<endl;
    cout<<"Patient status "<<(head->status ? " Admitted " : " Discharged ")<<endl;
    cout << "----------------------------\n";
}

Node* search_patient(Node* head, int id)
{
    Node* temp = head;
    while (temp != NULL && temp->patient_id != id)
    {
        temp = temp->next;
    }
    return temp;            //Return null if patient is not found
}

void display_all_admitted_patients(Node* head)
{   
    Node* temp = head;
    while(temp != NULL)
    {
        if(temp->status)
        {
            
            display_a_patient(temp);
        }
        temp = temp->next;
    }
}

void display_all_discharged_patients(Node* head)
{   
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

void discharge_patient(Node* head, int id)
{
    Node* discharged = search_patient(head, id);
    if (discharged == nullptr)
    {
        cout << "Patient not found."<<endl;
        return;
    }
    cout << "Patient : " << endl;
    display_a_patient(discharged);
    cout << endl << "is discharged" << endl;
    discharged->status = false;
}

void display_all_patients(Node* head)
{   
    Node* temp = head;
    cout<<"\nList of all patients  : \n";
    while(temp != NULL)
    {
        display_a_patient(temp);
        temp = temp->next;
    }
}

void delete_a_patient(Node*& head, int id)
{
    if (head == NULL)
    {
        cout << "Invalid request" << endl;
        return;
    }
    Node* temp = head;
    Node* prev = NULL;
    while (temp != NULL && temp->patient_id != id)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        cout << "Patient with ID " << id << " not found." << endl;
        return;
    }
    display_a_patient(temp);
    cout << "\nRecord is deleted."<< endl;
    
    if (prev == NULL)  // Deleting head
    {
        head = head->next;
    }
    else
    {
        prev->next = temp->next;
    }
    delete temp;
}

void delete_all_patients(Node*& head)
{
    Node* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        cout << "Deleting record of Patient ID: " << temp->patient_id << " (" << temp->name << ")" << endl;
        delete temp;
    }
    cout << "All patient records deleted." << endl;
}



int main()
{
    Node* head = NULL;
    char choice;
    int discharge_id;
    int search_id;
    int assigned_id=0;          //Patient Id
    int delete_id;
    clearScreen();
    do
    {
        cout<<endl;
        cout << "\t     === Hospital Management System ===" << endl;
        cout<<"\tEnter 1 to admit a patient                  "<<endl;
        cout<<"\tEnter 2 to discharge a patient              "<<endl;
        cout<<"\tEnter 3 to display a patient detail         "<<endl;
        cout<<"\tEnter 4 to display all admitted patients    "<<endl;
        cout<<"\tEnter 5 to display all discharged patients  "<<endl;
        cout<<"\tEnter 6 to display all patients             "<<endl;
        cout<<"\tEnter 7 to delete a patient record          "<<endl;
        cout<<"\tEnter 8 to delete all patient record        "<<endl;
        cout<<"\tEnter 9 to exit                             "<<endl;
        cin>>choice;
        switch(choice)
        {
            case '1':
            {
                if (admit_patient(head, assigned_id + 1)) 
                {
                    ++assigned_id;
                    cout << "Assigned patient id is : " << assigned_id << endl << endl;
                }
                break;
            }
            case '2':         // to discharge a patient
            {
                cout<<"Enter patient id : ";
                cin>>discharge_id;
                if (discharge_id > assigned_id || discharge_id <= 0)
                {
                    cout<<"Invalid patient id \n";
                }
                else
                {
                    discharge_patient(head,discharge_id);
                }
                break;
            }
            case '3':         // to display a patient detail
            {
                cout<<"Enter patient id : ";
                cin>>search_id;
                Node* result = search_patient(head, search_id);
                if (result)
                {
                    display_a_patient(result);
                }
                else
                {
                    cout << "Patient not found.\n";
                }
                break;
            }
            case '4':     // to display all currently admitted patients
            {
                cout<<"Admitted Patients are: "<<endl;
                display_all_admitted_patients(head);
                break;
            }
            case '5':     // to display all discharged patients
            {
                display_all_discharged_patients(head);
                break;
            }
            case '6':     // to display all patients of hospital
            {
                display_all_patients(head);
                break;
            }
            case '7':     // to delete a record
            {
                cout<<"Enter the patient id to be deleted : ";
                cin>>delete_id;
                if(delete_id > assigned_id || delete_id<=0)
                {
                    cout<<"Invalid patient id"<<endl;
                }
                else
                {
                    delete_a_patient(head,delete_id);
                }
                break;                
            }
            case '8':     // to delete all records
            {
                delete_all_patients(head);
                break;
            }
            case '9':     // to terminate the application
            {
                cout<<"\t\t\t\t\t\t\tPROGRAM HAS ENDED";
                break;
            }
            default:
            cout<<"Invalid option ";
        }
    }while(choice!='9');
    cout<<"\n\n\n\t\t\t\t\t\t\tProgrammed by :\n \t\t\t\t\t\t\tAPOORVA PAUDEL \n \t\t\t\t\t\t\tBIKASH DHAMI";
    return 0;
}