/* 
 * File:   main.cpp
 * Author: payrawsa
 *
 * Created on October 8, 2017, 9:37 AM
 */

#include "../include/header.h"
using namespace std;

/*
 * 
 */

Drone drone[10];

void* print_map(void* anything) {
    int temp;
    counter = 1;
    while (finished) {
        wait = pthread_mutex_lock(&lock2);
        cout << "\n \n map update number " << counter << "\n \n " << endl;
        int p;
        int l;
        for (p = 0; p < 50; p++) {
            for (l = 0; l < 50; l++) {
                if (p + l == 0) {
                    map[0][0] = '-';
                }

                cout << map[p][l];
            }
            cout << "\n";
        }

        if (end == temp) {
            finished = false;
        }
        temp = end;
        //   nanosleep((const struct timespec[]){{0, 1L}}, NULL);
        pthread_mutex_unlock(&lock2);
        wait = 100;
        usleep(10);
        counter++;
    }

}

void Drone::update_map(char current_drone, long drone_id) {
    int currentx = drone[drone_id].current_x;
    int currenty = drone[drone_id].current_y;
    int destinationx = drone[drone_id].dest_x;
    int destinationy = drone[drone_id].dest_y;
    while (wait == 0) {

    }
    usleep(1);

    if (drone[drone_id].go_home == false) {
        end++;
        if (currentx < destinationx && currenty < destinationy) {
            drone[drone_id].current_x = currentx + 1;
            drone[drone_id].current_y = currenty + 1;
        } else if (currentx < destinationx) {

            end++;
            drone[drone_id].current_x = currentx + 1;

        } else if (currenty < destinationy) {
            end++;

            drone[drone_id].current_y = currenty + 1;

        }

    }
    if (drone[drone_id].go_home) {

        if (currentx > 0 && currenty > 0) {
            end++;
            drone[drone_id].current_x = currentx - 1;
            drone[drone_id].current_y = currenty - 1;

        } else if (currentx > 0) {
            end++;
            drone[drone_id].current_x = currentx - 1;

        } else if (currenty > 0) {
            end++;
            drone[drone_id].current_y = currenty - 1;
        }

    }
    pthread_mutex_lock(&lock2);
    if (map[currentx][currenty] == current_drone) {
        map[currentx][currenty] = blank;
    }
    map[drone[drone_id].current_x][drone[drone_id].current_y] = current_drone;
    pthread_mutex_unlock(&lock2);
    if (drone[drone_id].current_x == drone[drone_id].dest_x && drone[drone_id].current_y == drone[drone_id].dest_y) {
        end++;
        map[drone[drone_id].current_x][drone[drone_id].current_y] = blank;
        drone[drone_id].go_home = true;
    }

}

void Drone::set_destination(int one, int two) {
    origin_x = 0;
    origin_y = 0;
    dest_x = one;
    dest_y = two;
    current_x = 0;
    current_y = 0;
    go_home = false;
}

void* move(void* input) {
    end++;
    pthread_mutex_lock(&locks);
    long tid;
    tid = (long) input;
    end++;
    int one = rand() % 50;
    int two = rand() % 50;
    end++;

    drone[tid].set_destination(one, two);
    pthread_mutex_unlock(&locks);


    switch (tid) {
        case 0: drone[tid].position = 'A';
            end++;
            break;
        case 1: drone[tid].position = 'B';
            end++;
            break;
        case 2: drone[tid].position = 'C';
            end++;
            break;
        case 3: drone[tid].position = 'D';
            end++;
            break;
        case 4: drone[tid].position = 'E';
            end++;
            break;
        case 5: drone[tid].position = 'F';
            end++;
            break;
        case 6: drone[tid].position = 'G';
            end++;
            break;
        case 7: drone[tid].position = 'H';
            end++;
            break;
        case 8: drone[tid].position = 'I';
            end++;
            break;
        case 9: drone[tid].position = 'J';
            end++;
            break;
        default: cout << "no thread what?" << endl;
            break;

    }
    end++;
    while (drone[tid].current_x != drone[tid].dest_x || drone[tid].current_y != drone[tid].dest_y) {
        drone[tid].locknumber = drone[tid].current_x * 50 + drone[tid].current_y;
        pthread_mutex_lock(&lock[drone[tid].locknumber]);
        drone[tid].update_map(drone[tid].position, tid);
        pthread_mutex_unlock(&lock[drone[tid].locknumber]);

    }

    while (drone[tid].current_x != drone[tid].origin_x || drone[tid].current_y != drone[tid].origin_y) {
        drone[tid].locknumber = drone[tid].current_x * 50 + drone[tid].current_y;
        pthread_mutex_lock(&lock[drone[tid].locknumber]);
        drone[tid].update_map(drone[tid].position, tid);
        pthread_mutex_unlock(&lock[drone[tid].locknumber]);
    }
    pthread_mutex_lock(&lock2);
    cout << "\ndrone " << drone[tid].position << " has succesfully delivered package\n" << endl;
    pthread_mutex_unlock(&lock2);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {

    int p;
    int l;
    cout << "initialize map \n \n" << endl;
    for (p = 0; p < 50; p++) {
        for (l = 0; l < 50; l++) {
            map[p][l] = '-';
            cout << map[p][l];
        }
        cout << "\n";
    }
    end = 0;
    finished = true;
    int rc;
    int i;
    pthread_t threads[NUM_THREADS];
    pthread_t map_updater;
    pthread_create(&map_updater, NULL, print_map, NULL);
    for (i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, move, (void *) i);
    }
    pthread_join(map_updater, NULL);
    for (i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);

    }
    end++;
    pthread_exit(NULL);
    end++;
    return 0;
}
