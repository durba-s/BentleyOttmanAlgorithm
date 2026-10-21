#include "AVL/AVLTree.h"
#include "AVL/AVLNode.h"
#include "Segment.h"
#include "Point.h"
#include<iostream>
#include<vector>
#include <fstream>
using namespace std;

/**
* @brief A small epsilon value used for floating point comparisions
*/
const double eps = 0.0000000001;

/**
* @brief Check if the given segment is horizontal
*
* @param s Pointer to the segment
* @return True if the segment is horizontal
* @return False otherwise
*/
bool isHor(Segment<double>* s);

/**
* @brief Check if the given segment is verical
*
* @param s Pointer to the segment
* @return True if the segment is vertical
* @return False otherwise
*/
bool isVer(Segment<double>* s);

/**
* @brief Check if the point is contained in the segment
*
* @param s Pointer to the segment
* @param p The point to be checked
* @return True if the point is contained in the segment
* @return False otherwise
*/
bool isContained(Segment<double>* s,pair<double,double> p);

/**
* @brief Check if the two segments can intersect
*
* @param Sl Pointer to the first segment
* @param Sr Pointer to the second segment
* @return True if the two segments can intersect
* @return False otherwise
*/
bool doesIntersect(Segment<double>* Sl,Segment<double>* Sr);

/**
* @brief Find x coordinate of point of intersection of a given segment and sweep line
*
* @param s Pointer to the segment
* @return x coordinate of point of intersection of a given segment and sweep line
*/
double sweepIntersection(Segment<double>* s);

/**
* @brief Find point of intersection of two given segments
*
* @param s1 Pointer to the first segment
* @param s2 Pointer to the second segment
* @return An ordered pair which is the point of s1 and s2
*/
pair<double,double> intersection(Segment<double>* s1,Segment<double>* s2);

/**
* @brief Comparator function of the event queue: comparision done on basis of y coordinates first i.e the point with greater y coordinate is the greater one; if y coordinates are equal, the point with lesser x coordinate is the greater one
*
* @param p1 Pointer to first event point
* @param p2 Pointer to second event point
* @return -1 if p1<p2
* @return 0 if p1==p2
* @return 1 if p1>p2
*/
int Q_cmp(Point<double> *p1,Point<double> *p2);

/**
* @brief Comparator function of the status queue: comparision done on basis of x coordinate of points of intersection of the segments with the sweep line
*
* @param s1 Pointer to first segment
* @param s2 Pointer to second segment
* @return -1 if s1<s2
* @return 0 if s1==s2
* @return 1 if s1>s2
*/
int T_cmp(Segment<double> *s1,Segment<double> *s2);

/**
* @brief Find intersections among the given set S of line segments
*
* @param S Set of line segments
* @param n Number of line segments
* @return The number of points of intersection
*/
int findIntersections(vector< Segment<double>* > S, int n);

/**
* @brief Updates the status queue and checks adjacent pairs for intersection; also prints if the given event point is an intersection point
* @param p Pointer to the given event point
*/
void handleEventPoint(Point<double> *p);

/**
* @brief Check if the segments meet to the right of or below the event point; if yes insert intersection point to event queue
*
* @param Sl Pointer to the first segment
* @param Sr Pointer to the second segment
* @param p  Pointer to the event point
*/
void findNewEvent(Segment<double>* Sl,Segment<double>* Sr,Point<double> *p);

/**
* @brief Function to report the intersection point p
*
* @param p  Pointer to the event point
*/
void reportIntersection(Point<double> *p);


int findIntersection(vector< Segment<double>* > S, int n);