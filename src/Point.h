#ifndef __POINT_H__
#define __POINT_H__
#include "Segment.h"
#include <vector>
using namespace std;


/**
 * @brief Point class to store the x and y coordinates of the event points
 */
template<class T>
class Point{

    public:
        //x coordinate of the point
        T x;
        //y coordinate of the point
        T y;

        /**
        * @brief Constructor to initialize an event point
        *
        * @param X The x coordinate of the event point
        * @param Y The y coordinate of the event point
        */
        Point(const T& X , const T& Y) : x(X) , y(Y) {}
        vector< Segment<T>* > L; //storing L(p)
        vector< Segment<T>* > C; //storing U(p)
        vector< Segment<T>* > U; //storing C(p)

};

#endif // __POINT_H__