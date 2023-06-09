#include <iostream>
#include <stdio.h>
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

void hilbert_curve(int n, int angle) {
    if( n==0 ) return;
    fprintf(out,"turtle.right(%d)\n", angle);
    
    hilbert_curve(n-1, -angle);
    
    fprintf(out,"turtle.forward(%d)\n", STEP_SZ);
    fprintf(out,"turtle.left(%d)\n", angle);
    
    hilbert_curve(n-1, angle);

    fprintf(out,"turtle.forward(%d)\n", STEP_SZ);
    
    hilbert_curve(n-1, angle);

    fprintf(out,"turtle.left(%d)\n", angle);
    fprintf(out,"turtle.forward(%d)\n", STEP_SZ);

    hilbert_curve(n-1, -angle);
    
    fprintf(out,"turtle.right(%d)\n", angle);
}

int main(int argc, char const *argv[]) {
    out = fopen("hilbert_turtle1.py", "w+");
    print_python_head();

    int order = 4;
    int angle = 90;
    unsigned t0, t1;

    t0=clock();
    hilbert_curve(order, angle);
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
    
    print_python_end();
    fclose(out);
    return 0;
}
