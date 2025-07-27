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
}
void display_patients(Node* head){   //To display list of patients
    Node* temp = head;
    while(temp != NULL){
        cout<<"Patient ID : "<<temp->patient_id<<endl;
        cout<<"Patient Name : "<<temp->name<<endl;
        cout<<"Age : "<<temp->age<<endl;
        cout<<"Gender : "<<temp->gender<<endl;
        cout<<"Disease : "<<temp->disease<<endl;

        temp = temp->next;
    }
}
int main()
{
    Node* head = NULL;
    admit_patient(head,101);
    admit_patient(head,102);
    admit_patient(head,103);
    display_patients(head);
    return 0;
}

