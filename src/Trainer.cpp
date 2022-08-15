#include "Trainer.h"
#include "Customer.h"
#include "Action.h"
#include <algorithm>
#include <iostream>

using namespace std;


// auto generated , need to check
//Trainer::Trainer(Trainer *pTrainer) {
//
//}

//Trainer constructor
Trainer::Trainer(int t_capacity) {
    this->capacity = t_capacity;
}

int Trainer::getCapacity() const {
    return capacity;
}

void Trainer::addCustomer(Customer *customer) {
    this->customersList.push_back(customer);
}

void Trainer::removeCustomer(int id) {
    for (unsigned int i = 0; i < customersList.size(); i++) {
        if (customersList[i]->getId() == id)
            customersList.erase(customersList.begin() + i);
    }
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return orderList;
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (auto i = workout_ids.begin(); i < workout_ids.end(); i++) {
        for (auto j = workout_options.begin(); j < workout_options.end(); j++) {
            if (i[0] == j->getId())
                orderList.push_back(OrderPair(customer_id, j[0]));
        }
    }
}

void Trainer::openTrainer() {
    if (!open) {
        open = true;
    } else {
        std::cout << "Trainer already opened" << std::endl;
    }
}

void Trainer::closeTrainer() {
    if (open)
        open = false;
    customersList.clear();
    orderList.clear();
}
void Trainer::updateSalary()
{
        int sum = 0;
        for (unsigned int i = 0; i < orderList.size(); i++) {
            sum += (orderList.at(i).second.getPrice());
        }
        salary+=sum;

}

int Trainer::getSalary() {
    return salary;
}

bool Trainer::isOpen() {
    if (open)
        return true;
    else
        return false;
}

void Trainer::addOrder(int id, Workout workout) {
    orderList.push_back(OrderPair(id, workout));
}

Customer *Trainer::getCustomer(int id) {
    return customersList.at((id));
}

void Trainer::deleteAndUpdateOrder(std::vector<OrderPair> tmp) {
    orderList.clear();
    for (unsigned int i = 0; i < tmp.size(); i++) {
        this->addOrder(tmp[i].first, tmp[i].second);
    }
}

//Rule of 5
Trainer::~Trainer(){//destructor
    //customersList
    for(Customer* customer:customersList)
    {
        if(customer)
            delete customer;
    }
    //orderList
    customersList.clear();
} //destructor

    //Copy Constructor:
    Trainer::Trainer(const Trainer &other) :orderList(other.orderList) {
        salary=other.salary;
        capacity = other.capacity;
        open = other.open;

    for(Customer* cust:other.customersList){
            customersList.push_back(cust->kindof());
        }

    }

//Copy Constructor

Trainer & Trainer::operator=(Trainer &other){
    //check for "self assignment" and do nothing in that case
    if(this != &other){
        this->~Trainer();
        open=other.open;
        capacity = other.capacity;
        salary=other.salary;
        for(Customer* cust:other.customersList){
            customersList.push_back(cust->kindof());
        }
        //orderList
        for(unsigned int i=0; i<orderList.size();++i){
            OrderPair new_pair((orderList[i]).first,(orderList[i]).second);
            orderList.push_back(new_pair);
        }


    }
    return *this;

} //Copy Assignment Operator

Trainer::Trainer(Trainer&& other){
    capacity = other.getCapacity();
    open = other.isOpen();
    salary=other.getSalary();
    for(Customer* cust:other.customersList){
        customersList.push_back(cust);
        cust=nullptr;
    }
    for(OrderPair op:other.orderList){
        orderList.push_back(op);
    }
    other.orderList.clear();

} //Move constructor

Trainer & Trainer::operator=(Trainer && other){
    if(this != &other){
        orderList.clear();
        for(Customer* cust: customersList){
            (*cust).~Customer();
        }
        customersList.clear();
        capacity = other.capacity;
        open = other.open;
        for(Customer* cust:other.customersList){
            customersList.push_back(cust);
            cust=nullptr;
        }
        for(OrderPair op:other.orderList){
            orderList.push_back(op);
        }
        other.orderList.clear();
    }
    return *this;
} //Move Assignment Operator









