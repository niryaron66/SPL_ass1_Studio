#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Customer.h"
#include "Workout.h"

typedef std::pair<int , Workout> OrderPair;


class Trainer{
public:
    Trainer(int t_capacity);
  //  Trainer(const Trainer& other); //copy constuctor
 //  Trainer(Trainer *pTrainer);//need to check auto generate


    //RO5
    Trainer(const Trainer& trainer); //Copy Constructor
    Trainer& operator=(Trainer& trainer); //Copy Assignment Operator
    ~Trainer(); //destructor
    Trainer(Trainer&& other); //Move constructor
    Trainer& operator=(Trainer&& other); //Move Assignment Operator


    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    bool isOpen();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary();
    void updateSalary();


    void addOrder(int id, Workout workout);
    void deleteAndUpdateOrder(std::vector<OrderPair>);

private:
    int capacity;
    bool open= false;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
    int salary=0;

};


#endif