#include <iostream>
#include <array>
#include <math.h>
#include <fstream>

using namespace std;

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
    int num_time_steps = 500;

    ofstream H_file;
    H_file.open("h.csv");
    ofstream E_file;
    E_file.open("e.csv");

    for (int time_step = 0; time_step < num_time_steps; ++time_step){
        
        //First column of CSV
        E_file << time_step << "," << E[0];
        H_file << time_step << ",";

        //Update final H node
        H[node_num - 1] = H[node_num - 2];

        //H update
        for (int i = 0; i < node_num - 1; ++i){
            H[i] = H[i] + (S_c/(mur*z0))*(E[i+1]-E[i]);
            H_file << H[i] << ",";
        }
        
        H_file << H[node_num - 1] << endl;

        //Additive E source
        E[node_num/2] += exp(-(time_step - 30.)*(time_step - 30.)/100.);

        //Update first E node
        E[0] = E[1];

        //E update
        for (int j = 1; j < node_num; ++ j){
            E[j] = E[j] + (S_c*z0/er)*(H[j]-H[j-1]);
            E_file << "," << E[j];
        }
        E_file << endl;
    }
}

