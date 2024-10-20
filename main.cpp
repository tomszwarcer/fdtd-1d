#include <iostream>
#include <array>
#include <math.h>
#include <fstream>

using namespace std;

double E_incident(double time_step, double position, int boundary){
    return exp(-(time_step - position + boundary - 30.)*(time_step - position + boundary - 30.)/100.);
}

int main(){

    //Constants
    const double S_c = 1.;
    const double er = 1.;
    const double mur = 1.;
    const double z0 = 376.7;

    //Number of nodes
    const size_t node_num = 200;

    //E and H arrays
    array<double,node_num> E = {};
    //Note we set H[node_num-1]=0 here.
    array<double,node_num> H = {};

    //number of time steps
    int num_time_steps = 300;

    //position of TFSF boundary
    int boundary = 50;

    ofstream H_file;
    H_file.open("h.csv");
    ofstream E_file;
    E_file.open("e.csv");

    for (int time_step = 0; time_step < num_time_steps; ++time_step){        

        //Update final H node
        H[node_num - 1] = H[node_num - 2];

        //H update
        for (int i = 0; i < node_num - 1; ++i){
            H[i] += + (S_c/(mur*z0))*(E[i+1]-E[i]);
        }

        //Correction for TFSF boundary
        H[boundary - 1] -= (S_c/(mur*z0))*E_incident(time_step - 0.5, boundary, boundary);

        //Update first E node
        E[0] = E[1];

        //E update
        for (int j = 1; j < node_num; ++ j){
            E[j] += (S_c*z0/er)*(H[j]-H[j-1]);
        }

        //Correction for TFSF boundary
        E[boundary] += (S_c/sqrt(er*mur))*E_incident(time_step - 0.5,boundary - 0.5,boundary);

        //Write to files
        E_file << time_step;
        H_file << time_step;
        for (int k = 0; k < node_num; ++k){
            E_file << "," << E[k];
            H_file << "," << H[k];
        }
        E_file << endl;
        H_file << endl;
    }
}

