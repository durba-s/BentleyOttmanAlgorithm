#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include<stdlib.h>
#include<limits>
using namespace std;
/**
 * @brief Class to store a segment
*/
template<class T>
class Segment{

    public:
        //2 pairs indicating the lower and upper end points of the segment
        pair<T,T> pl , pu;

        /**
        * @brief constructor which sets the lower and upper end points of the segment
        * 
        * @param p1 The first ordered pair
        * @param p2 The second ordered pair
        */
        Segment(pair<T,T> p1 ,pair<T,T> p2){
            if(abs(p1.second-p2.second)<=0.00000005){ //if y coordinates are equal
                if(p1.first<p2.first){
                    pu=p1;  //upper point is the one with smaller x coordinate
                    pl=p2;
                }
                else{
                    pu=p2; //upper point is the one with smaller x coordinate
                    pl=p1;
                }
            }
            else{ //when y coordinates are distinct
                if(p1.second<p2.second){
                    pu=p2; //upper point is the one with larger y coordinate
                    pl=p1;
                }
                else{
                    pu=p1; //upper point is the one with larger y coordinate
                    pl=p2;
                }
            }
        }
};


#endif