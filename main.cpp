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

    //max number of time steps
    int max_time = 250;

    ofstream H_file;
    H_file.open("h.csv");
    ofstream E_file;
    E_file.open("e.csv");

    for (int time_step = 0; time_step < max_time; ++time_step){
        E_file << time_step << ",";
        H_file << time_step << ",";

        //hard-wired E source
        E[0] = exp(-(time_step - 30.)*(time_step - 30.)/100.);
        E_file << E[0];

        //H update
        for (int i = 0; i < node_num - 1; ++i){
            H[i] = H[i] + (S_c/(mur*z0))*(E[i+1]-E[i]);
            H_file << H[i] << ",";
        }
        H_file << H[node_num - 1] << endl;

        //E update
        for (int j = 1; j < node_num; ++ j){
            E[j] = E[j] + (S_c*z0/er)*(H[j]-H[j-1]);
            E_file << "," << E[j];
        }
        E_file << endl;
    }

}

