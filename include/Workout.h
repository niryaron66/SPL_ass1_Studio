#ifndef WORKOUT_H_
#define WORKOUT_H_

#include <string>

enum WorkoutType{
    ANAEROBIC, MIXED, CARDIO
};

class Workout{
public:
    Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type);


   // void copy(const int &other_id, const std::string &other_name, const int &other_price,const WorkoutType &other_type);
    void clear();

    int getId() const;
    std::string getName() const;
    int getPrice() const;
    WorkoutType getType() const;
private:
	const int id;
    const std::string name;
    const int price;
    const WorkoutType type;
};


#endif