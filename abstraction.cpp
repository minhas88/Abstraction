#include <iostream>
#include <string.h>
#include <algorithm>

class reg
{
    virtual void split() = 0; 
};

class splitWise:reg
{
private:
    double perHead;
    unsigned int numPeople, numPayee;
    double *total_amount;
    double *amountPerHead;
    std::string *payee;
    std::string *members;

public:
    splitWise(int payee, int people);
    ~splitWise();
    void set_amount(double *paisa, int i);
    void set_numPeople(int *num);
    int get_numPeople();
    void set_numPayee(int *num);
    int get_numPayee();
    void set_payee(std::string *name, int i);
    std::string get_payee(int i);
    void set_members(std::string *names, int i);
    std::string get_members(int i);
    double get_amountPerHead(int i);
    void split();
};

struct PaymentAdjustment {
    int from;   
    int to;     
    double amount;
};

splitWise::splitWise(int paye, int people)
{
    numPeople = people;
    numPayee = paye;
    perHead = 0;
    total_amount = new double[numPayee];
    amountPerHead = new double[numPeople];
    payee = new std::string[numPayee];
    members = new std::string[numPeople];
}

splitWise::~splitWise()
{
    delete[]total_amount;
    delete[]amountPerHead;
    delete[]payee;
    delete[]members;
    total_amount = NULL;
    amountPerHead = NULL;
    payee = NULL;
    members = NULL;
}

void splitWise::set_amount(double *paisa, int i){
    total_amount[i] = *paisa;
}

void splitWise::set_numPeople(int *num){
    numPeople = *num;
}

int splitWise::get_numPeople(){
   return numPeople; 
}

void splitWise::set_numPayee(int *num){
    numPayee = *num;
}

int splitWise::get_numPayee(){
   return numPayee; 
}

void splitWise::set_payee(std::string *name, int i){
    payee[i] = *name;
}

std::string splitWise::get_payee(int i){
    return payee[i];
}

void splitWise::set_members(std::string *names, int i){
    members[i] = *names;
}

std::string splitWise::get_members(int i){
    return members[i];
}

double splitWise::get_amountPerHead(int i){
    return amountPerHead[i];
}

void splitWise::split(){
    for (int i = 0; i <get_numPayee(); i++)
    {
        perHead += total_amount[i]/get_numPeople();
    }

    for (int i = 0; i < get_numPeople(); i++)
    {
        amountPerHead[i] = perHead;
    }
    
    for (int i = 0; i <get_numPayee(); i++)
    {
        for (int j = 0; j < get_numPeople(); j++)
        {
            if(payee[i] == members[j]){
                amountPerHead[j] = perHead - total_amount[i];
            }
        } 
    }
}

int main(){
    int numofpayee, numofpeople, index;
    double amount; 
    std::string name, memnames; 
    std::cout << "Enter the total number of payees: ";
    std::cin >> numofpayee;
    std::cout << "Enter the total number of members: ";
    std::cin >> numofpeople;
    splitWise splitting(numofpayee, numofpeople);
    splitting.set_numPayee(&numofpayee);
    splitting.set_numPeople(&numofpeople);
    double balance[splitting.get_numPeople()];

    for (int i = 0; i < splitting.get_numPayee(); i++)
    {
        std::cout << "Enter the names of payees: ";
        std::cin >> name;
        splitting.set_payee(&name, i);
    }   
    for (int i = 0; i < splitting.get_numPayee(); i++)
    {
        std::cout << "Enter the amount paid by " << splitting.get_payee(i) <<" : ";
        std::cin >> amount;
        splitting.set_amount(&amount, i);
    }
    for (int i = 0; i < (splitting.get_numPeople() - splitting.get_numPayee()); i++)
    {
        index =i;
        std::cout << "Enter the names of members (other than payees): ";
        std::cin >> memnames;
        splitting.set_members(&memnames, i);
    }
    for (int i = 0; i < splitting.get_numPayee(); i++)
    {
        index += 1;
        memnames = splitting.get_payee(i);
        splitting.set_members(&memnames, index);
    }

    splitting.split();
    std::cout << std::endl;
    for (int i = 0; i < splitting.get_numPeople(); i++)
    {
        if(splitting.get_amountPerHead(i) > 0)
            std::cout << splitting.get_members(i) << " owes " << splitting.get_amountPerHead(i) << std::endl;
        else if(splitting.get_amountPerHead(i) < 0)
            std::cout << splitting.get_members(i) << " has to be returned " << (splitting.get_amountPerHead(i) * -1) << " amount " << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < splitting.get_numPeople(); i++)
    {
        balance[i] = splitting.get_amountPerHead(i);
    }
    for (int i = 0; i < splitting.get_numPeople(); i++)
    {
        if (balance[i] < 0)
        {
            for (int j = 0; j < splitting.get_numPeople(); j++)
            {
                if(balance[j] > 0){
                    double transfer = __min(-balance[i], balance[j]);
                    balance[i] += transfer;
                    balance[j] -= transfer;
                    std::cout << splitting.get_members(j) << " needs to pay " << splitting.get_members(i) << " the amount of " << transfer << std::endl;
                    if (balance[i] == 0)
                    {
                        break;
                    }
                    
                }
            }
            
        }
        
    } 

    std::cout << "press any key to exit...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}