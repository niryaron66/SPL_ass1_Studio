#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"


class Studio{		
public:
	Studio();
    Studio(const std::string &configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    static void  deleteSpace(std::string line);


    Studio (const Studio& other); //Copy Constructor
    ~Studio(); //destructor
    const Studio & operator=(const Studio &other); //Copy Assignment Operator
    Studio(Studio&& other); //Move constructor
    Studio& operator=(Studio&& other); //Move Assignment Operator


    static int readNumberOfTrainers (std::ifstream &infile);
    void initializeTrainer(std::ifstream &infile, int numOfTrainers);
    void initializeWorkoutOption(std::ifstream &infile);
private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
    static int idGen;

    void ltrim(std::string &s);

    void rtrim(std::string &s);

    void trim(std::string &s);

    std::string trim_copy(std::string s);
};

#endif