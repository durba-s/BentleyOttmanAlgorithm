#include "utils.h"

int noi = 0; //number of intersections
double a = 0; //sweepLine : y = a
FILE* pt_file;

bool isHor(Segment<double>* s){
	return  abs((s->pl.second)-(s->pu.second))<=eps;
}
bool isVer(Segment<double>* s){
	return  abs((s->pl.first)-(s->pu.first))<=eps;
}
bool isContained(Segment<double>* s,pair<double,double> p){
    //cout<<"[test]: "<<endl;
    if(isHor(s)){
        //printf("[pt]: %lf, %lf [line]: %lf %lf and %lf %lf",p.first,p.second,s->pl.first,s->pl.second,s->pu.first,s->pu.second);
        if((p.first <= (s->pl.first)) && (p.first >= (s->pu.first))){
            //cout<<" 1"<<endl;
            return true;
        }
		    //return true;
        else{
            //cout<<" 2"<<endl;
            return false;
        }
    }
    else{
        if((p.second <= ((s->pu.second))) && (p.second >= (s->pl.second)))
            return true;
        else
            return false;
    }
}


bool doesIntersect(Segment<double>* Sl,Segment<double>* Sr){
    //eqn of line through (x1,y1) and (x2,y2) is (y2-y1)x + (x1-x2)y + x2y1 - x1y2 = 0
    //lines a1x+b1y+c1 = 0 and a2x+b2y+c1 = 0 are parallel if a1b2 = a2b1
    double x11 = Sl->pl.first;
    double x12 = Sl->pu.first;
    double y11 = Sl->pl.second;
    double y12 = Sl->pu.second;
    double x21 = Sr->pl.first;
    double x22 = Sr->pu.first;
    double y21 = Sr->pl.second;
    double y22 = Sr->pu.second;

    double a1 = y12 - y11;
    double b1 = x11 - x12;
    double a2 = y22 - y21;
    double b2 = x21 - x22;

    return !(abs(a1*b2 - a2*b1)<=eps);
}

pair<double,double> intersection(Segment<double>* s1,Segment<double>* s2){
    //eqn of line through (x1,y1) and (x2,y2) is (y2-y1)x + (x1-x2)y + x2y1 - x1y2 = 0
    double x11 = s1->pl.first;
    double x12 = s1->pu.first;
    double y11 = s1->pl.second;
    double y12 = s1->pu.second;
    double x21 = s2->pl.first;
    double x22 = s2->pu.first;
    double y21 = s2->pl.second;
    double y22 = s2->pu.second;

    double a1 = y12 - y11;
    double b1 = x11 - x12;
    double c1 = (x12*y11) - (x11*y12);
    double a2 = y22 - y21;
    double b2 = x21 - x22;
    double c2 = (x22*y21) - (x21*y22);

    double x = (b1*c2 - b2*c1)/(a1*b2 - a2*b1);
    double y = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);

    return make_pair(x,y);
}

double sweepIntersection(Segment<double>* s){
    if(isHor(s)){
        return s->pl.first;
    }
    else{
        double x1 = s->pl.first;
        double x2 = s->pu.first;
        double y1 = s->pl.second;
        double y2 = s->pu.second;

        a-=eps;
        double x = (((a*(x2-x1))-((x2*y1)-(x1*y2)))/(y2-y1));
        a+=eps;
        return x;
    }
}
int Q_cmp(Point<double> *p1,Point<double> *p2){
    if(((abs(p1->x - p2->x))<=eps) && ((abs(p1->y - p2->y))<=eps))
        return 0;
    else if((abs(p1->y - p2->y))<=eps){
        if(p1->x < p2->x)
            return 1;
        else
            return -1;
    }
    else{
        if(p1->y < p2->y)
            return -1;
        else
            return 1;
    }
}

int T_cmp(Segment<double> *s1,Segment<double> *s2){
    if((abs(s1->pu.first - s2->pu.first)<=eps) && 
        (abs(s1->pl.second - s2->pl.second)<=eps) &&
        (abs(s1->pu.first - s2->pu.first)<=eps) &&
        (abs(s1->pl.second - s2->pl.second)<=eps)){
            return 0;
        }
   else if(isHor(s1) && !isHor(s2)){
       return 1;
   }
   else if(!isHor(s1) && isHor(s2)){
       return -1;
   }
   else if(isHor(s1) && isHor(s2)){
       if(abs(s1->pu.first - s2->pu.first)<=eps){
           if((s1->pl.first) < (s2->pl.first)){
                return -1;
            }
            else if((s1->pl.first) > (s2->pl.first)){
                return 1;
            }
       }
       else if((s1->pu.first) < (s2->pu.first)){
           return -1;
       }
       else{
           return 1;
       }
   }
   else{
        double px1 = sweepIntersection(s1);
        double px2 = sweepIntersection(s2);
        if(px1 < px2){
            return -1;
        }
        else{
            return 1;
        }
   }
}

AVLTree<Point<double>* > Q(Q_cmp); //initialize an empty event queue
AVLTree<Segment<double>* > T(T_cmp); //initialize an empty status queue

int findIntersections(vector< Segment<double>* > S, int n){
    /*Insert the segment endpoints into Q; when an upper endpoint is inserted, the corresponding segment should
    be stored with it*/
    vector<Segment<double>* > horz;

    for(int i=0;i<n;i++){
        Point<double> *lp = new Point<double>(S[i]->pl.first,S[i]->pl.second);
        Point<double> *up = new Point<double>(S[i]->pu.first,S[i]->pu.second);
        if(isHor(S[i])){
            horz.push_back(S[i]);
        }
        Q.insert(lp); //insert lower endpoint to Q
        Q.insert(up); //insert upper endpoint to Q
        auto nup = Q.search(up);
        nup->data->U.push_back(S[i]); //store corresponding segment with the upper endpoint
        auto nlp = Q.search(lp);
        nlp->data->L.push_back(S[i]); //store corresponding segment with the upper endpoint
    }

    pt_file = fopen("pts.csv", "w");
    fprintf(pt_file ,"x,y\n");
    /*while Q is not empty
        do Determine the next event point p in Q and delete it.
            handleEventPoint(p)*/
    while(Q.root!=NULL){
        auto eventpoint = Q.findMax(Q.root);
        if(eventpoint!=NULL){
            auto p = eventpoint->data;
            //cout<<"\n\n[EVENTPT]"<<p->x<<" "<<p->y<<endl;
            handleEventPoint(p);
            Q.remove(p);
        }
    }
    fclose(pt_file);
    return noi;
}

void handleEventPoint(Point<double> *p){

/*Let U(p) be the set of segments whose upper endpoint is p; these segments
are stored with the event point p. (For horizontal segments, the upper
endpoint is by definition the left endpoint.)*/

/*Find all segments stored in T that contain p; they are adjacent in T. Let
L(p) denote the subset of segments found whose lower endpoint is p, and
let C(p) denote the subset of segments found that contain p in their interior.*/

    //Find all segments stored in T that contain p


    vector<Segment<double>* > LuC;
    vector<Segment<double>* > UuC;
    vector<Segment<double>* > LuUuC;
    //printf("\n[L(p): ]");
    for(int i = 0;i < p->L.size();i++){
        //printf("(%lf,%lf) and (%lf,%lf) ; ",p->L[i]->pl.first,p->L[i]->pl.second,p->L[i]->pu.first,p->L[i]->pu.second);
            LuC.push_back(p->L[i]);
            LuUuC.push_back(p->L[i]);

    }
    //printf("\n[U(p): ]");
    for(int i = 0;i < p->U.size();i++){
        //printf("(%lf,%lf) and (%lf,%lf) ; ",p->U[i]->pl.first,p->U[i]->pl.second,p->U[i]->pu.first,p->U[i]->pu.second);
            LuUuC.push_back(p->U[i]);
            UuC.push_back(p->U[i]);
    }
    //printf("\n[C(p): ]");
    for(int i = 0;i < p->C.size();i++){
        //printf("(%lf,%lf) and (%lf,%lf) ; ",p->C[i]->pl.first,p->C[i]->pl.second,p->C[i]->pu.first,p->C[i]->pu.second);
            LuC.push_back(p->C[i]);
            LuUuC.push_back(p->C[i]);
            UuC.push_back(p->C[i]);
    }

    LuC.erase( unique( LuC.begin(), LuC.end() ), LuC.end() );
    UuC.erase( unique( UuC.begin(), UuC.end() ), UuC.end() );
    LuUuC.erase( unique(  LuUuC.begin(),  LuUuC.end() ),  LuUuC.end() );


/*if L(p)∪U(p)∪C(p) contains more than one segment
    then Report p as an intersection, together with L(p), U(p), and C(p).*/
    if(LuUuC.size() >1){
        noi = noi+1;
        reportIntersection(p);
    }


/*Delete the segments in L(p)∪C(p) from T.*/
    if(T.root!=NULL){
        for(int i = 0;i<LuC.size();i++){
            T.remove(LuC[i]);
        }
    }
    a = p->y; //update sweep line


/*Insert the segments in U(p)∪C(p) into T. The order of the segments in T
should correspond to the order in which they are intersected by a sweep
line just below p. If there is a horizontal segment, it comes last among all
segments containing p.
(∗ Deleting and re-inserting the segments of C(p) reverses their order. ∗)*/
    

    Segment<double> *s_leftmost=NULL,*s_rightmost=NULL;
    if(UuC.size()>0){
        s_leftmost=UuC[0];
        s_rightmost=UuC[0];
        for(int i = 0;i<UuC.size();i++){
            T.insert(UuC[i]);
            if(i>0){
                if(T_cmp(s_leftmost,UuC[i])>0){
                    s_leftmost = UuC[i];
                }
                if(T_cmp(s_rightmost,UuC[i])<0){
                    s_rightmost = UuC[i];
                }

            }
        }
    }

//assume that sl and sr actually exist, otherwise corresponding steps should not be performed.

/*if U(p)∪C(p) = null-set
    then Let sl and sr be the left and right neighbors of p in T.
    FINDNEWEVENT(sl,sr, p)*/

    if(UuC.size()==0){
        Segment<double> *s=new Segment<double>(make_pair((p->x),(p->y)+1),make_pair((p->x),(p->y)-1));
        auto sl = T.find_left(T.root,s);
        auto sr = T.find_right(T.root,s);
        if((sl!=NULL) && (sr!=NULL)){
            //printf("UUC size 0 Sl (%lf,%lf) and (%lf,%lf) ; \n",sl->data->pl.first,sl->data->pl.second,sl->data->pu.first,sl->data->pu.second);
            //printf("UUC size 0 Sl (%lf,%lf) and (%lf,%lf) ; \n",sr->data->pl.first,sr->data->pl.second,sr->data->pu.first,sr->data->pu.second);
            findNewEvent(sl->data,sr->data,p);
        }
    }
/*else
    Let s be the leftmost segment of U(p)∪C(p) in T.
    Let sl be the left neighbor of s in T.
    FINDNEWEVENT(sl,s, p)
    Let s be the rightmost segment of U(p)∪C(p) in T.
    Let sr be the right neighbor of s in T.
    FINDNEWEVENT(s,sr, p)*/
    else{
        if(s_leftmost!=NULL){
            //printf("UUC not null S' (%lf,%lf) and (%lf,%lf) ; \n",s_leftmost->pl.first,s_leftmost->pl.second,s_leftmost->pu.first,s_leftmost->pu.second);
            auto sl=T.predecessor(T.root,new AVLNode<Segment<double> *>(s_leftmost));
            if(sl!=NULL){
                //printf("UUC not null Sl (%lf,%lf) and (%lf,%lf) ; \n",sl->data->pl.first,sl->data->pl.second,sl->data->pu.first,sl->data->pu.second);
                findNewEvent(sl->data,s_leftmost,p);
            }
        }
        if(s_rightmost!=NULL){
            //printf("UUC not null S'' (%lf,%lf) and (%lf,%lf) ; \n",s_rightmost->pl.first,s_rightmost->pl.second,s_rightmost->pu.first,s_rightmost->pu.second);
            auto sr=T.successor(T.root,new AVLNode<Segment<double> *>(s_rightmost));
            if(sr!=NULL){
                //printf("UUC not null Sr (%lf,%lf) and (%lf,%lf) ; \n",sr->data->pl.first,sr->data->pl.second,sr->data->pu.first,sr->data->pu.second);
                findNewEvent(sr->data,s_rightmost,p);
            }
        }

    }


}


void findNewEvent(Segment<double>* Sl,Segment<double>* Sr,Point<double> *p){
    /*if sl and sr intersect below the sweep line, or on it and to the right of the
    current event point p, and the intersection is not yet present as an
    event in Q
    then Insert the intersection point as an event into Q.
    update C(p) */

    if(doesIntersect(Sl,Sr)){
        pair<double,double> poi = intersection(Sl,Sr);
        if(isContained(Sl,poi) && isContained(Sr,poi)){
        //if(isContained(Sl,poi) && isContained(Sr,poi) && ((poi.second <= (a)) || ((eps+poi.first) >= p->x))){
            auto pt = new Point<double>(poi.first,poi.second);
            Q.insert(pt);
            auto ppi = Q.search(pt);
            ppi->data->C.push_back(Sl);
            ppi->data->C.push_back(Sr);
        }
    }
}

void reportIntersection(Point<double> *p){
    cout<<"[Intersection] "<<noi<<endl;
    cout<< p->x <<","<< p->y <<endl;
    fprintf(pt_file ,"%09lf,%09lf\n",p->x,p->y);
    /*
    for(int i = 0;i < p->L.size();i++){
        cout<<"[SEG]: ";
        cout<<p->L[i]->pl.first<<","<<p->L[i]->pl.second<<" and ";
        cout<<p->L[i]->pu.first<<","<<p->L[i]->pu.second<<endl;
    }
    for(int i = 0;i < p->C.size();i++){
        cout<<"[SEG]: ";
        cout<<p->C[i]->pl.first<<","<<p->C[i]->pl.second<<" and ";
        cout<<p->C[i]->pu.first<<","<<p->C[i]->pu.second<<endl;
    }
    for(int i = 0;i < p->U.size();i++){
        cout<<"[SEG]: ";
        cout<<p->U[i]->pl.first<<","<<p->U[i]->pl.second<<" and ";
        cout<<p->U[i]->pu.first<<","<<p->U[i]->pu.second<<endl;
    }*/


}














































































int findIntersection(vector< Segment<double>* > S, int n){
    pt_file = fopen("pts.csv", "w");
    fprintf(pt_file ,"x,y\n");
    for(int i=0;i<n;i++){
        for(int j = i+1;j<n;j++){
            if(doesIntersect(S[i],S[j])){
                pair<double,double> poi = intersection(S[i],S[j]);
                if(isContained(S[i],poi) && isContained(S[j],poi)){
                    noi++;
                    //cout << "[hi]"<<endl;
                    //printf("[pt]: %lf, %lf \n[line1]: %lf %lf and %lf %lf\n",poi.first,poi.second,S[i]->pl.first,S[i]->pl.second,S[i]->pu.first,S[i]->pu.second);
                    //printf("line2]: %lf %lf and %lf %lf\n",poi.first,poi.second,S[j]->pl.first,S[j]->pl.second,S[j]->pu.first,S[j]->pu.second);
                    printf("[Intersection: ]%d\n %09lf,%09lf\n",noi,poi.first,poi.second);
                    fprintf(pt_file ,"%09lf,%09lf\n",poi.first,poi.second);
                }
            }
        }
    }
    fclose(pt_file);
    return noi;
}
