#include <pthread.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#define NUM_THREADS 10
pthread_mutex_t lock2;
pthread_mutex_t locks;
pthread_mutex_t lock[2500];
char map [50][50];
bool finished;
int counter;
int end;
char blank = '-';
int wait=100;

struct Drone {
    int locknumber;
    int origin_x;
    int origin_y;
    int dest_x;
    int dest_y;
    int current_x;
    int current_y;
    char position;
    bool go_home;

public:
    void set_destination(int one, int two);
    void update_map(char current_drone, long drone_id);

};

