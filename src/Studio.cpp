#include "Studio.h"
#include "Trainer.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;


int Studio::idGen = 0;


Studio::Studio() {}

Studio::Studio(const std::string &configFilePath) {

}


int Studio::readNumberOfTrainers(std::ifstream &infile) {
    std::string line;
    getline(infile, line);
    while (line[0] == '\0') {
        continue;
    }
    //cout <<"number of trainer: " << stoi(line) << endl;
    return stoi(line);
}

void Studio::initializeTrainer(std::ifstream &infile, int numOfTrainers) {
    std::string line;
    getline(infile, line);
    while (line[0] == '\0') {
        getline(infile, line);
    }
    stringstream ss(line);
    int num;
    for (int i = 0; i < numOfTrainers; i++) {
        if (ss.peek() == ',') {
            ss.ignore();
        }
        ss >> num;
        trainers.push_back(new Trainer(num)); //should be new or not ??
    }
}
// trim from start (in place)
 inline void Studio::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
 inline void Studio::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
 inline void Studio::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


// trim from both ends (copying)
 inline std::string Studio::trim_copy(std::string s) {
    trim(s);
    return s;
}

void Studio::initializeWorkoutOption(std::ifstream &infile) {

    while (infile) {
        std::string line;
        getline(infile, line);
        if (line[0] == '\0') getline(infile, line);
        int delimeterIndex1 = line.find(',');
        int delimeterIndex2 = line.find(',', delimeterIndex1 + 1);
        if (delimeterIndex1 == -1) {
            break;
        }
        std::string name = trim_copy(line.substr(0, delimeterIndex1));
        std::string worktype = trim_copy(line.substr(delimeterIndex1 + 1, delimeterIndex2 - (delimeterIndex1 + 1)));
        int price = stoi(trim_copy(line.substr(delimeterIndex2 + 1, line.find(' ', delimeterIndex2 + 2))));
        WorkoutType enumType;
        if (worktype==("Anaerobic"))
            enumType = ANAEROBIC;
        else if (worktype ==("Mixed"))
           enumType = MIXED;
        else if (worktype ==("Cardio"))
            enumType = CARDIO;
        workout_options.push_back(Workout(idGen, name, price, enumType)); //need to be new??
        idGen++;
    }
}


void Studio::deleteSpace(std::string line) {
    while (line[0] == ' ') {

        line.erase(0, 1);
    }
}


string BaseAction::getType(string line) {
    string command = line.substr(0, line.find(" "));
    line.erase(0, command.size() + 1);
    // cout <<line << endl;
    return command;
}

int BaseAction::getTrainerId(string line) {
    deleteSpace(line);
    std::string command = line.substr(0, line.find(" "));
    line.erase(0, command.size());
    return stoi(command);

}

vector<Customer *> BaseAction::getCustomers(string line) {
    std::vector<Customer *> customers;
    int c_id = 0;
    size_t found = line.find(",");
    std::string first;
    std::string second;
    while (line[0] == ' ')
        line.erase(0, 1);
    while (found != std::string::npos) {

        first = line.substr(0, found);
        line.erase(0, first.size() + 1);
        second = line.substr(0, 3);// get 3 word strategy
        line.erase(0, 3);
        if (second == "swt") {
            customers.push_back(new SweatyCustomer(first, c_id)); //DELETE!!!!!!!!!!!!
            c_id++;
        }
        if (second == "chp") {
            customers.push_back(new CheapCustomer(first, c_id)); //DELETE!!!!!!!!!!!!
            c_id++;
        }
        if (second == "fbd") {
            customers.push_back(new FullBodyCustomer(first, c_id)); //DELETE!!!!!!!!!!!!
            c_id++;
        }
        if (second == "mcl") {
            customers.push_back(new HeavyMuscleCustomer(first, c_id)); //DELETE!!!!!!!!!!!!
            c_id++;
        }
        while (line[0] == ' ')
            line.erase(0, 1);
        found = line.find(",");
    }
    return customers;
}

//open 2 Shalom,swt
BaseAction *buildAction(std::string line) {
    std::string cIn=line;
    string actionType = BaseAction::getType(line);
    line.erase(0, actionType.size());
    while (line[0] == ' ')
        line.erase(0, 1);
    // cout <<line << endl;

    if (actionType == "open") {
        int trainerId = BaseAction::getTrainerId(line);
        line.erase(0, to_string(trainerId).size());
        while (line[0] == ' ')
            line.erase(0, 1);
        vector<Customer *> customers = BaseAction::getCustomers(line);
        return  new OpenTrainer(trainerId, customers); //NEED TO DELETE ALL CUSTOMERS INCLUDING WHAT NOT IN USE
    }
    if (actionType == "order") {
        int trainerId = BaseAction::getTrainerId(line);
        line.erase(0, to_string(trainerId).size());
        return new Order(trainerId);

    }
    if (actionType == "move") {
        std::stringstream ss(line);
        std::vector<int> numbers;
        for (int i = 0; ss >> i;) {
            numbers.push_back(i);
        }
        return new MoveCustomer(numbers.at(0), numbers.at(1), numbers.at(2));
    }
    if (actionType == "close") {
        int trainerId = BaseAction::getTrainerId(line);
        return  new Close(trainerId);
    }
    if (actionType == "closeall") {

        return new CloseAll();
    }
    if (actionType == "workout_options") {

        return new PrintWorkoutOptions();
    }
    if(actionType == "status")
    {
        int trainerId = BaseAction::getTrainerId(line);
        return new PrintTrainerStatus(trainerId);

    }
    if(actionType== "log")
        return new  PrintActionsLog();

    if(actionType=="backup")
        return new  BackupStudio();

    if(actionType == "restore")
        return new  RestoreStudio();



    return nullptr;
}


void Studio::start() {
    open = true;
    std::cout << "Studio is now open!" << std::endl;



    char command[500];
    while (true) {

        std::cin.getline(command, 500);
        BaseAction* act = buildAction(command);
        actionsLog.push_back(act);
        act->Setc_IN(command);
        act->act(*this);
        if (std::string(command) == "closeall")
            break;
    }

}

int Studio::getNumOfTrainers() const {
    return trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    return trainers[tid];
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}


std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}



Studio:: Studio(const Studio& other):
        open(other.open),workout_options(other.workout_options)
{
    for(BaseAction* ba: other.actionsLog){
        actionsLog.push_back(ba->kindOf());
    }
    for(Trainer* t:other.trainers){
        trainers.push_back(new Trainer(*t));
    }

    for(Workout wa:other.workout_options) {
        Workout new_wa(wa.getId(),wa.getName(),wa.getPrice(),wa.getType());
        workout_options.push_back(wa);
    }
}
Studio:: ~Studio(){
    open = false;
    for(Trainer* tr: trainers){
        if(tr)
        (*tr).~Trainer();
    }
    trainers.clear();
    for(BaseAction* ba:actionsLog){
        (*ba).~BaseAction();
    }
    actionsLog.clear();

}

const Studio& Studio::operator=(const Studio& other) {
    if (this != &other) {
        this->~Studio();
        open=other.open;
        for (Trainer *t: other.trainers) {
            trainers.push_back(new Trainer(*t));
        }
        for (BaseAction *ba: other.actionsLog) {
            actionsLog.push_back(ba->kindOf());
        }
        for(Workout wa:other.workout_options)
       {
           Workout new_wa(wa.getId(),wa.getName(),wa.getPrice(),wa.getType());
           workout_options.push_back(new_wa);
       }
    }

    return *this;
}
Studio:: Studio(Studio&& other)://Move constructor
        open(other.open),
        trainers(other.trainers),
        workout_options(other.workout_options),
        actionsLog(other.actionsLog)
{
    other.workout_options.clear();
    other.trainers.clear();
    other.actionsLog.clear();
}


Studio& Studio:: operator=(Studio&& other) {//Move assignment operator
    for (Trainer *tr: trainers) {
        (*tr).~Trainer();
    }
    trainers.clear();

    for (Workout w: workout_options) {
        w.~Workout();
    }
    workout_options.clear();

    for (BaseAction *ba: actionsLog) {
        (*ba).~BaseAction();
    }
    actionsLog.clear();

    open = other.open;
    std::vector<Trainer*> trainers;
    for (unsigned int i = 0 ; i<  other.trainers.size() ; i++) {
        Trainer* tra = new Trainer(*(other.trainers.at(i))); //trainer copy constructor is called
        trainers.push_back(tra);
    }
    std::vector<Workout> workout_options;
    for (Workout a: other.workout_options) {
        int id = a.getId();
        string name = a.getName();
        int price = a.getPrice();
        WorkoutType type = a.getType();
        Workout work(id, name, price, type);
        workout_options.push_back(work);
    }

    actionsLog = other.actionsLog;
    other.workout_options.clear();
    other.trainers.clear();
    other.actionsLog.clear();

    return *this;
}

