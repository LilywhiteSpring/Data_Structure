//
// Created by 85375 on 2025/12/5.
//
#include "simulation.h"

int  simulator::random_product(int low , int high) {
    random_device rd;
    static mt19937 generator;
    generator.seed(rd());
    uniform_int_distribution<int> dst(low , high);
    int time =  dst(generator);
    return time;
}
simulator::simulator() {
    cout<<"这是莉莉牌排队（坐牢）模拟机，接下来请根据指示输入内容，开始模拟捏~\n";
    cout<<"请输入模拟的顾客数(小于20)：\n";
    int tmp;
    cin>>tmp;
    while ( tmp >= 20) {
        cout<<"真是的，明明咱已经说了输入小于二十的数了awa，乖乖听话哟~：\n";
        cin>>tmp;
    }
    customer_num = tmp;
    cout<<"请输入柜台数（小于 6 哟）：\n";
    cin>>counter_num;
    cout<<"请输入顾客到达时间间隔的上界：\n";
    cin>>arrival_max;
    cout<<"请输入顾客到达时间间隔的下界：\n";
    cin>>arrival_min;
    cout<<"请输入时间处理时间的上界：\n";
    cin>>wait_max;
    cout<<"请输入时间处理时间的下界：\n";
    cin>>wait_min;
    counters = new counter [counter_num];
    if (counters)
        cout<<"构造成功！接下来请调用“Launcher函数开始模拟！”\n";
}
simulator::command simulator::enter_operation(int &time) const {
    char tmp = '\0';
    cout<<"请输入接下来的操作~："<<endl
    <<"输入“n”表示进行下一步操作"<<endl
    <<"输入“t”表示跳过一定时间间隔，并输入该间隔"<<endl
    <<"输入“p”表示再次打印当前状态\n"<<endl;
    cin>>tmp;
    switch (tmp) {
        case 'p': return Print;
        case 'q': delete [] counters ;  return Quit;
        case 't': cout<<"请输入跳过的时间间隔:\n" ;
            int ts ; cin>>ts ;
            if (ts <= 0 )
                time = 1;
            else
                time = ts;
            return Next_time;
        case 'n':
            default:
            return Next_event ;
    }
}
double simulator::Launcher() {
    int current_time = 0;
    int counters_avail = counter_num;
    int Total_time = 0;
    int pass_time;
    event current;
    counter* tmp_counter;
    priority_queue<event> Events;
    queue<event> wait , another;
    current.time_occur = 0;
    for (int i=1 ; i <= customer_num ; ++i) {
        current.time_occur += random_product(arrival_min , arrival_max);
        current.type = Arrival;
        current.user_name = 'A' - 1 + i;
        Events.push(current);
    }

    command cmd ;
    while (!Events.empty()) {
        cmd = enter_operation(pass_time);
        switch (cmd) {
            case Next_event: {
                current = Events.top();
                Events.pop();


                //依次处理柜台中的时间数据
                for (int i = 0 ; i < counter_num ; ++i) {
                    if (counters[i].user_name) {
                        if (current.time_occur - current_time <= counters[i].time_rest) {
                            counters[i].time_rest -= current.time_occur - current_time;
                        }
                        // else {
                        //     counters[i].time_rest = 0;
                        // }
                    }
                }
                Total_time += wait_num(wait) * (current.time_occur - current_time);
                current_time = current.time_occur;

                if (Arrival == current.type) {
                     if (counters_avail > 0) {
                         for (int i = 0 ; i <counter_num ; ++i) {
                            if (!counters[i]) {
                                counters_avail--;
                                counters[i].user_name = current.user_name;
                                counters[i].time_rest = random_product(wait_min , wait_max);
                                current.time_occur = current_time + counters[i].time_rest;
                                current.type = Leave;
                                Events.push(current);
                                break;
                            }
                         }
                     }
                    else {
                        wait.push(current);
                    }

                }
                else {
                    counters_avail++;
                    tmp_counter = find(current.user_name);
                    tmp_counter-> time_rest = 0;
                    tmp_counter-> user_name = '\0';
                    if (!wait.empty()) {
                        counters_avail--;
                        current = wait.front();
                        wait.pop();
                        tmp_counter-> user_name = current.user_name;
                        tmp_counter-> time_rest = random_product(wait_min , wait_max);
                        current.type = Leave;
                        current.time_occur = current_time + tmp_counter-> time_rest;
                        Events.push(current);
                    }
                }
            }
                break;

            case Next_time: {



            }
                break;

            case Print: break;
            case Quit:
            default:
                cout<<"出错啦！\n";
                return -1;
        }

        //输出阶段(这里为了减少调用直接卸载了函数体内部)
        cout<<"当前时间是："<<current_time<<endl;
        cout<<"队列中："<<endl;
        int num = wait_num(wait);
        if (0 == num) {
            cout<<"当前队列为空！！"<<endl;
        }
        else {
            while (!another.empty()) {
                current = another.front();
                cout<<"客户"<<current.user_name<<" 已经等待"<<current_time - current.time_occur<<"分钟"<<endl;
                another.pop();
            }
            cout<<"当前等待的队伍长度是： "<<num<<endl;
        }
        for (int i = 0 ; i < counter_num ; ++i) {
            cout<<"柜台"<<i + 1<<"当前状态："<<endl;
            if (!!counters[i]) {
                cout<<"客户"<<counters[i].user_name<<"  剩余服务时长： "<<counters[i].time_rest<<endl;
            }
            else
                cout<<"目前处于空闲状态！"<<endl;
        }
        cout<<endl;
    }
    cout<<"队列中顾客等待的平均时长是： "<<(Total_time / customer_num)<<endl;
    return static_cast<double>(Total_time) / customer_num;
}