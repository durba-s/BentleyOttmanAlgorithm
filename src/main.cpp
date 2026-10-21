#include "utils.h"
#include <time.h>
#include<ctime>
#include <sys/types.h>
#include <iostream>
#include <stdlib.h>

/**
* @brief Function to get the current time
*
* @return The current time
*/
struct timespec get_time() {
    struct timespec tm;
    if (timespec_get(&tm, TIME_UTC) != TIME_UTC) {
        fprintf(stderr, "ERROR: call to timespec_get failed \n");
        exit(EXIT_FAILURE);
    }

    return tm;
}

/**
* @brief Function to get the time difference between two given times
*
* @param st Staring time
* @param et Ending time
* @return Time Difference in seconds between the given times
*/
double get_time_diff(struct timespec st, struct timespec et) {
    return et.tv_sec - st.tv_sec + (double)(et.tv_nsec - st.tv_nsec) / 1000000000LL;
}

int main(){
    //int t;
    FILE* input = fopen("./src/input.txt", "r");
    //fscanf(input,"%d",&t);
    //while(t--){
    int n; //number of line segments
    //cin>>n;
    //fscanf(input,"%d",&n);

    scanf("%d",&n);

    //vector of segments to store input
    vector< Segment<double>* > S;

    //reading input segments
    for(int i=0;i<n;i++){
        pair<double,double> p1,p2;
        cin>>p1.first>>p1.second>>p2.first>>p2.second;
        double f1,f2,f3,f4;
        /*
        fscanf(input,"%lf",&f1);
        fscanf(input,"%lf",&f2);
        fscanf(input,"%lf",&f3);
        fscanf(input,"%lf",&f4);

        p1.first = f1;
        p1.second = f2;
        p2.first = f3;
        p2.second = f4;
        */
        S.push_back(new Segment<double>(p1,p2));
    }
    fclose(input);
    struct timespec strt = get_time();

    //call to the function to find intersections
    int noi = findIntersections(S,n);

    struct timespec ed = get_time();
    double tdiff = get_time_diff(strt,ed);

    //log the time statistics
    FILE* ta = fopen("stats.csv", "a");
    fprintf(ta,"%d,%d,%09lf\n",n,noi,tdiff);
    fclose(ta);

    //log segment data for plots
    FILE* inp_file = fopen("segs.csv", "w");
    fprintf(inp_file ,"x1,x2,y1,y2\n");
    for(int i=0;i<n;i++){
        fprintf(inp_file ,"%09lf,%09lf,%09lf,%09lf\n",S[i]->pl.first,S[i]->pu.first,S[i]->pl.second,S[i]->pu.second);
    }

    fclose(inp_file);
    //}
    system("python algov.py");
}
