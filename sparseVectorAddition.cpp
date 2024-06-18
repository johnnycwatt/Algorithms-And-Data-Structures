//Implements vector addition for sparse vectors. 

//Reads in two sparse vectors from standard input, adds them, and prints the resulting vector to standard output. 

#include <iostream>
using namespace std;

struct Node{
    int index;
    int value;
    Node* next;
    Node(int indx, int val): index(indx), value(val), next(NULL){}
};

void addNode(Node*& head, int index, int value){
    Node* newNode = new Node(index, value);
    
    if(!head or (index < head->index)){
        newNode->next = head;
        head = newNode;
    }else{
        Node* current = head;
        while(current->next and current->next->index < index){
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
    }
}

Node* readSparseVector(){
    Node* head = NULL;
    int input;
    int index;
    int value;
    
    cin >> input;
    for(int i = 0; i < input; i++){
        cin >> index >> value;
        addNode(head, index, value);
    }
    return head;
}

Node* addSparseVectors(Node* vector1, Node* vector2){
    Node* result = NULL;
    Node* current1 = vector1;
    Node* current2 = vector2;

  //Traverse both vectors
    while(current1 or current2){
        if(current1 != NULL and (!current2 or current2->index > current1->index)){
            addNode(result, current1->index, current1->value);
            current1 = current1->next;
        }else if(current2 != NULL and (!current1 or current1->index > current2->index)){
            addNode(result, current2->index, current2->value);
            current2 = current2->next;
        }else{
            //Add sum of both nodes if indices are equal
            int total = current1->value + current2->value;
            if(total != 0){
                addNode(result, current1->index, total);
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    return result;
}

void printSparseVector(Node* head){
    int nonZero = 0;
    Node* current = head;

  //count the non-zero elements
    while(current){
        if(current->value != 0){
            ++nonZero;
        }
        current = current->next;
    }
    cout << nonZero;
    current = head;

  //Print the index and value of non-zero elements
    while(current){
        if(current->value != 0){
            cout << " " << current->index << " " << current->value;
        }
        current = current->next;
    }
    cout << endl;
}

void deleteSparseVector(Node*& head){
    while(head){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main(){
    Node* vector1 = readSparseVector();
    Node* vector2 = readSparseVector();
    Node* result = addSparseVectors(vector1, vector2);
    printSparseVector(result);
    
    deleteSparseVector(vector1);
    deleteSparseVector(vector2);
    deleteSparseVector(result);
    return 0;
}
