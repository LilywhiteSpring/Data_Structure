//
// Created by 85375 on 2025/12/5.
//

#ifndef QUEUE_SIMULATION_SIMULATION_H
#define QUEUE_SIMULATION_SIMULATION_H
#include <iostream>
#include <queue>
#include <random>
using namespace std;
enum event_Type {
    Arrival,
    Leave,
};
class simulator {
private:
    struct event {
        int time_occur;
        event_Type type;
        char user_name;
        bool operator< (const event& e) const { return time_occur > e.time_occur;}
        //这里有点问题
    };
    struct counter {
        char user_name = '\0';
        int time_rest = 0;
        bool operator !() const {return !user_name;}
    };
    enum command {
        Next_event,
        Next_time,
        Help,
        Print,
        Quit,
    };
    int counter_num;
    int arrival_min;
    int arrival_max;
    int wait_min;
    int wait_max;
    int customer_num;
    counter* counters;

    command enter_operation(int &time) const;
    int random_product(int low , int high);
    counter* find(char user) {
        for (int i = 0 ; i < counter_num ; ++i) {
            if (user == counters[i].user_name)
                return &counters[i];
        }
        return nullptr;
    }
    int wait_num(const queue<event>& tmp) {
        queue<event> another = tmp;
        int num = 0;
        while (!another.empty()) {
            another.pop();
            ++num;
        }
        return num;
    }
public:
    simulator();
    ~simulator(){delete [] counters;}
    double Launcher();
};
#endif //QUEUE_SIMULATION_SIMULATION_H