
#include "Customer.h"
#include "iostream"

Customer::Customer(std::string c_name, int c_id) : name(c_name), id(c_id) {}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

//swt
SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> SweatyCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector<int> swtVector;
    for (unsigned int i = 0; i < workout_options.size(); i++) {
        if (workout_options[i].getType() == CARDIO) {
            swtVector.push_back(workout_options[i].getId());
        }
    }
    return swtVector;
}

std::string SweatyCustomer::toString() const {
    return "Complete"; //MODIFY!!
}

Customer* SweatyCustomer::kindof() {
    return new SweatyCustomer(*this);
}

//
CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> CheapCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector<int> chpVector;
        int cheapestWorkout = workout_options.at(0).getPrice();
        int cheapestWorkoutID = workout_options.at(0).getId();
        for (unsigned int i = 0; i < workout_options.size(); i++) {
            if (workout_options.at(i).getPrice() < cheapestWorkout) {
                cheapestWorkout = workout_options.at(i).getPrice();
                cheapestWorkoutID = workout_options.at(i).getId();
            }
        }
        chpVector.push_back(cheapestWorkoutID);
        return chpVector;


}

std::string CheapCustomer::toString() const {
    return "Complete"; //MODIFY!!
}

Customer *CheapCustomer::kindof() {
    return new CheapCustomer(*this);
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {


}

std::vector<int> HeavyMuscleCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector<int> mclVector;
    for (unsigned int i = 0; i < workout_options.size(); i++) {
        if (workout_options[i].getType() == ANAEROBIC) {
            mclVector.push_back(workout_options[i].getId());
        }
    }
    return mclVector;
}

std::string HeavyMuscleCustomer::toString() const {
    return "Complete"; //MODIFY!!
}

Customer *HeavyMuscleCustomer::kindof() {
    return new HeavyMuscleCustomer(*this);
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> FullBodyCustomer::order(const std::vector <Workout> &workout_options) {
    std::vector <Workout> tmp;
    std::vector<int> fbdVector;

    for (unsigned int i = 0; i < workout_options.size(); i++) {
        if (workout_options[i].getType() == CARDIO) {
            tmp.push_back(workout_options[i]);
        }
    }
    if (!tmp.empty()) {
        std::cout << workout_options.size() << std::endl;

        int CheapestCardio = tmp.at(0).getPrice();
        int CheapestCardioID = tmp.at(0).getId();
        for (unsigned int i = 0; i < tmp.size(); i++) {
            if (tmp.at(i).getPrice() < CheapestCardio) {
                CheapestCardio = tmp.at(i).getPrice();
                CheapestCardioID = tmp.at(i).getId();
            }

        }
        fbdVector.push_back(CheapestCardioID);
    }
    std::vector <Workout> tmp2;
    for (unsigned int i = 0; i < workout_options.size(); i++) {
        if (workout_options[i].getType() == MIXED) {
            tmp2.push_back(workout_options[i]);
        }
    }
    if (!tmp.empty() && !tmp2.empty()) {
        int ExpensiveMixed = tmp2.at(0).getPrice();
        int ExpensiveMixedID = tmp2.at(0).getId();
        for (unsigned int i = 0; i < tmp2.size(); i++) {
            if (tmp2.at(i).getPrice() > ExpensiveMixed) {
                ExpensiveMixedID = tmp2.at(i).getId();
            }
        }
        fbdVector.push_back(ExpensiveMixedID);
    }
    std::vector <Workout> tmp3;
    for (unsigned int i = 0; i < workout_options.size(); i++) {
        if (workout_options[i].getType() == ANAEROBIC) {
            tmp3.push_back(workout_options[i]);
        }
    }
    if (!tmp.empty() && !tmp2.empty() && !tmp3.empty()) {
        int CheapestAnaerobic = tmp3.at(0).getPrice();
        int CheapestAnaerobicID = tmp3.at(0).getId();
        for (unsigned int i = 0; i < tmp3.size(); i++) {
            if (tmp3.at(i).getPrice() < CheapestAnaerobic) {
                CheapestAnaerobic = tmp3.at(i).getPrice();
                CheapestAnaerobicID = tmp3.at(i).getId();
            }
        }
        fbdVector.push_back(CheapestAnaerobicID);
    }

    return fbdVector;
}

std::string FullBodyCustomer::toString() const {
    return "Complete";
}

Customer *FullBodyCustomer::kindof() {
    return new FullBodyCustomer(*this);
}
