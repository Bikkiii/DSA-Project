#include <iostream>
#include <string>
using namespace std;
class Node
{
    public:
    int patient_id;
    string name;
    int age;
    string gender;
    string disease;
    bool status;
    Node* next;
    Node(int id)
    {
        patient_id = id;
        cout<<"Enter Patient Name : "<<endl;
        getline(cin >> ws,name);
        cout<<"Enter Patient Age : "<<endl;
        cin>>age;
        cout<<"Enter Patient Gender : "<<endl;
        cin>>gender;
        cout<<"Enter Patient Disease : "<<endl;
        getline(cin >> ws,disease);
	}
};
void admit_patient(Node*& head, int id) 
 {
    Node* newnode = new Node(id);
    
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
void display_a_patient(Node* head)
{   
    cout<<"Patient ID : "<<head->patient_id<<endl;
    cout<<"Patient Name : "<<head->name<<endl;
    cout<<"Age : "<<head->age<<endl;
    cout<<"Gender : "<<head->gender<<endl;
    cout<<"Disease : "<<head->disease<<endl;
    cout<<"Patient status "<<(head->status ? " Admitted " : " Discharged ")<<endl<<endl;
}
Node* search_patient(Node*head,int id)
{
    Node*temp = head;
    while(temp->patient_id!=id)
    {
        temp = temp->next;
    }
    return temp;
    
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
void discharge_patient(Node*head,int id)
{
    Node* discharged;
    cout<<"Patient : " <<endl;
    discharged = search_patient(head,id);
    display_a_patient(discharged);
    cout<<endl<<"is discharged"<<endl;
    discharged->status=false;
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

int main()
{
    Node* head = NULL;
    int choice;
    int discharge_id;
    int search_id;
    int assigned_id=0;
    do
    {
        cout<<endl<<"Enter 1 to admit a patient : "<<endl;
        cout<<"Enter 2 to discharge a patient : "<<endl;
        cout<<"Enter 3 to display a patient detail : "<<endl;
        cout<<"Enter 4 to display all admitted patients : "<<endl;
        cout<<"Enter 5 to display all discharged patients : "<<endl;
        cout<<"Enter 6 to display all patients : "<<endl;
        cout<<"Enter 7 to delete a patient record : "<<endl;
        cout<<"Enter 8 to exit a patient : "<<endl<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1:         // to admit a patient
            admit_patient(head,++assigned_id);
            cout<<"Assigned patient id is : "<<assigned_id<<endl<<endl;
            break;
            case 2:         // to discharge a patient
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
            case 3:         // to display a patient detail
            cout<<"Enter patient id : ";
            cin>>search_id;
            if(search_id > assigned_id || search_id<=0)
            {
                cout<<"Invalid patient id \n";
            }
            else
            {
                display_a_patient(search_patient(head,search_id));
            }
            break;
            case 4:     // to display all currently admitted patients
            display_all_admitted_patients(head);
            break;
            case 5:     // to display all discharged patients
            display_all_discharged_patients(head);
            break;
            case 6:     // to display all patients of hospital
            display_all_patients(head);
            break;
            case 7:     // to delete a record
            break;
            case 8:     // to terminate the application
            cout<<"\t\t\t EXITING . . . . ";
            break;
            default:
            cout<<"Invalid option \nChoose Again!!";
        }
    }while(choice!=8);
    return 0;
}

