#include <iostream>
#include <stdio.h>
#include <thread>
#include <vector>
#include <string>
#include <ctime> 

using namespace std;

#define STEP_SZ 10
#define H_WINDOWS 800
#define W_WINDOWS 800
#define SPEED 1  // check https://docs.python.org/3/library/turtle.html#turtle.speed

FILE *out;

void print_python_head(){
    fprintf(out,"import turtle\n");
    fprintf(out,"turtle.setup(%d, %d)\n", H_WINDOWS, W_WINDOWS);
    //fprintf(out, "turtle.speed(%d)\n", SPEED);
	fprintf(out, "turtle.tracer(0)\n");
	
}

void print_python_end(){
	fprintf(out, "turtle.update()\n"); 
    fprintf(out, "screen = turtle.Screen()\n"); // EXIT ON CLICK
    fprintf(out, "screen.exitonclick()\n"); // EXIT ON CLICK
}

void hilbert_curve(int n, int angle, vector<string> &saved_dir) {
    if( n==0 ) return;

    string str_angle;

    str_angle = "turtle.right(" + to_string(angle) + ")\n";
    saved_dir.push_back(str_angle);      
    
    hilbert_curve(n-1, -angle,saved_dir);
    
    saved_dir.push_back("turtle.forward(10)\n");
    str_angle = "turtle.left(" + to_string(angle) + ")\n";
    saved_dir.push_back(str_angle);
    
    hilbert_curve(n-1, angle, saved_dir);

    saved_dir.push_back("turtle.forward(10)\n");    
    
    hilbert_curve(n-1, angle, saved_dir);
    
    str_angle = "turtle.left(" + to_string(angle) + ")\n";
    saved_dir.push_back(str_angle);
    saved_dir.push_back("turtle.forward(10)\n");

    hilbert_curve(n-1, -angle, saved_dir);

    str_angle = "turtle.right(" + to_string(angle) + ")\n";
    saved_dir.push_back(str_angle);
}

void hilbert_with_threads(int order, int angle, vector<vector<string>>& my_dirs_){
    thread t0(hilbert_curve, order-1, -angle, ref(my_dirs_[0]));
    thread t1(hilbert_curve, order-1, angle, ref(my_dirs_[1]));
    thread t2(hilbert_curve, order-1, angle, ref(my_dirs_[2]));
    thread t3(hilbert_curve, order-1, -angle, ref(my_dirs_[3]));

    t0.join();
    t1.join();
    t2.join();
    t3.join();
}

void saving_in(vector<vector<string>> my_dirs_, int angle) {
    fprintf(out,"turtle.right(%d)\n", angle);
    for(int j = 0; j < my_dirs_[0].size(); j++) {
        fprintf(out,my_dirs_[0][j].c_str());
    }
    fprintf(out,"turtle.forward(%d)\n", STEP_SZ);
    fprintf(out,"turtle.left(%d)\n", angle);
    for(int j = 0; j < my_dirs_[1].size(); j++) {
        fprintf(out,my_dirs_[1][j].c_str());
    }
    fprintf(out,"turtle.forward(%d)\n", STEP_SZ);
    for(int j = 0; j < my_dirs_[2].size(); j++) {
        fprintf(out,my_dirs_[2][j].c_str());
    }
    fprintf(out,"turtle.left(%d)\n", angle);
    fprintf(out,"turtle.forward(%d)\n", STEP_SZ);
    for(int j = 0; j < my_dirs_[3].size(); j++) {
        fprintf(out,my_dirs_[3][j].c_str());
    }
    fprintf(out,"turtle.right(%d)\n", angle);
}

int main(int argc, char const *argv[]) {
    int order = 5;
    int angle = 90;
    unsigned t0, t1;
    //vector<thread> my_threads;
    vector<vector<string>> my_dirs (4);

    out = fopen("hilbert_turtle.py", "w+");
    print_python_head();

    //Paralelo
    t0=clock();
    hilbert_with_threads(order, angle, my_dirs);    //Funcion que divide la tarea en 4 areas
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    saving_in(my_dirs, angle);                      //Funcion donde se guardan las instrucciones en el archivo .py

    print_python_end();
    fclose(out);

    return 0;
}
