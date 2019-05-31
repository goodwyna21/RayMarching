#ifndef BODIES_H
#define BODIES_H

#include "Constants.h"

struct Lamp{
    Vec pos;
    Color color;
    Lamp(){pos={0,0,0};color={255,255,255};}
    Lamp(Vec p, Color c={255,255,255}){
        pos = p;
        color=c;
    }
};

struct Body{
    Vec center;
    Color color;
    Body(){
        center={0,0,0};
        color={255,0,0};
    }
    virtual ~Body(){}
    virtual string type(){
        return "Body";
    }
    virtual double distSquared(Vec v){
        bp("distSquared not defined");
        throw runtime_error("Distance squared function not defined");
    }
    virtual double dist(Vec v){
        bp("dist not defined");
        throw runtime_error("Distance function not defined");
    }
};

struct Union : virtual Body{
    vector<Body *> bodies;
    Union(){
        center={0,0,0};
        color={255,0,0};
    }
    Union(initializer_list<Body *> Bodies,Color c={255,0,0}){
        bodies = Bodies;
        double avgx, avgy, avgz;
        for(int i = 0; i < bodies.size(); i++){
            avgx+=bodies[i]->center[x];
            avgy+=bodies[i]->center[y];
            avgz+=bodies[i]->center[z];
        }
        center={avgx,avgy,avgz};
        center/=bodies.size();
        color={255,0,0};
    }
    ~Union(){
        for(int i = 0; i < bodies.size(); i++){
            delete bodies[i];
        }
    }
    string type(){
        string ret = "Union of ";
        for(int i = 0; i < bodies.size(); i++){
            ret += bodies[i]->type();
            if(i+1 < bodies.size()){
                ret += ", ";
            }
        }
        return ret;
    }
    double dist(Vec v){
        vector<double> dists(bodies.size());
        for(int i = 0; i < bodies.size(); i++){
            dists[i]=bodies[i]->dist(v);
        }
        return *min_element(dists.begin(),dists.end());
    }
    double distSquared(Vec v){
        return pow(dist(v),2);
    }
};

struct Intersect : virtual Body{
    vector<Body *> bodies;
    Intersect(){
        center={0,0,0};
        color={255,0,0};
    }
    Intersect(initializer_list<Body *> Bodies,Color c={255,0,0}){
        bodies = Bodies;
        double avgx, avgy, avgz;
        for(int i = 0; i < bodies.size(); i++){
            avgx+=bodies[i]->center[x];
            avgy+=bodies[i]->center[y];
            avgz+=bodies[i]->center[z];
        }
        center={avgx,avgy,avgz};
        center/=bodies.size();
        color={255,0,0};
    }
    ~Intersect(){
        for(int i = 0; i < bodies.size(); i++){
            delete bodies[i];
        }
    }
    string type(){
        string ret = "Intersection of ";
        for(int i = 0; i < bodies.size(); i++){
            ret += bodies[i]->type();
            if(i+1 < bodies.size()){
                ret += ", ";
            }
        }
        return ret;
    }
    double dist(Vec v){
        vector<double> dists(bodies.size());
        for(int i = 0; i < bodies.size(); i++){
            dists[i]=bodies[i]->dist(v);
        }
        return *max_element(dists.begin(),dists.end());
    }
    double distSquared(Vec v){
        return pow(dist(v),2);
    }
};

struct Cutout : virtual Body{
    vector<Body *> bodies;
    Cutout(){
        center={0,0,0};
        color={255,0,0};
    }
    Cutout(initializer_list<Body *> Bodies,Color c={255,0,0}){
        bodies = Bodies;
        double avgx, avgy, avgz;
        for(int i = 0; i < bodies.size(); i++){
            avgx+=bodies[i]->center[x];
            avgy+=bodies[i]->center[y];
            avgz+=bodies[i]->center[z];
        }
        center={avgx,avgy,avgz};
        center/=bodies.size();
        color={255,0,0};
    }
    ~Cutout(){
        for(int i = 0; i < bodies.size(); i++){
            delete bodies[i];
        }
    }
    string type(){
        string ret = "Union of ";
        for(int i = 0; i < bodies.size(); i++){
            ret += bodies[i]->type();
            if(i+1 < bodies.size()){
                ret += ", ";
            }
        }
        return ret;
    }
    double dist(Vec v){
        vector<double> dists(bodies.size());
        for(int i = 0; i < bodies.size(); i++){
            dists[i]=((i>0)?-1:1)*bodies[i]->dist(v);
        }
        return *max_element(dists.begin(),dists.end());
    }
    double distSquared(Vec v){
        return pow(dist(v),2);
    }
};

struct Sphere : virtual Body{
    double radius;
    Sphere(){
        center={0,0,0};
        color={255,0,0};
        radius=25;
    }
    Sphere(Vec cent, double r, Color c={255,0,0}){
        center = cent;
        color = c;
        radius = r;
    }
    ~Sphere(){}
    string type(){
        return "Sphere";
    }
    double dist(Vec v){
        return center.dist(v) - radius;
    }
    double distSquared(Vec v){
        return pow(dist(v),2);
    }
};

struct Cube : virtual Body{
    double length;
    Cube(){
        center={0,0,0};
        length=10;
        color={255,0,0};
    }
    Cube(Vec cent, double len, Color c={255,0,0}){
        center = cent;
        length=len;
        color=c;
    }
    ~Cube(){}
    string type(){
        return "Cube";
    }
    double dist(Vec v){
        double dx = (v[x]-center[x])/length;
        double dy = (v[y]-center[y])/length;
        double dz = (v[z]-center[z])/length;
        
        return sqrt(pow(max(0.0,abs(dx)-1),2) + 
                    pow(max(0.0,abs(dy)-1),2) + 
                    pow(max(0.0,abs(dz)-1),2)) * length;
    }
    double distSquared(Vec v){
        double dx = (v[x]-center[x]);
        double dy = (v[y]-center[y]);
        double dz = (v[z]-center[z]);
        
        return (pow(max(0.0,abs(dx)-1),2) + 
                pow(max(0.0,abs(dy)-1),2) + 
                pow(max(0.0,abs(dz)-1),2)) * length; 
    }
};

struct Segment : virtual Body{
    Vec p1;
    Vec p2;
    Segment(){}
    ~Segment(){}
    string type(){
        return "Segment";
    }
    Segment(Vec P1, Vec P2, Color c={255,0,0}){
        center = {P1[x] + (P2[x]-P1[x])/2,
                  P1[y] + (P2[y]-P1[y])/2,
                  P1[z] + (P2[z]-P1[z])/2};
        color = c;
        p1=P1;
        p2=P2;
    }
    double getT(Vec p){
        return 0.5 + ((pow(p1.dist(p),2)-pow(p2.dist(p),2))/(2*pow(p1.dist(p2),2)));
    }
    Vec closestPnt(Vec p){
        double t = getT(p);
        if(t > 1){
            return p2;
        }else if(t < 0){
            return p1;
        }else{
            return {p1[x] + t*(p2[x] - p1[x]),
                    p1[y] + t*(p2[y] - p1[y]),
                    p1[z] + t*(p2[z] - p1[z])};
        }
    }
    double dist(Vec p){
        return closestPnt(p).dist(p);}
    double distSquared(Vec p){
        return closestPnt(p).distSquared(p);}
};

struct Cylinder : Segment{
    double radius;
    string type(){
        return "Cylinder";
    }
    Cylinder(Vec P1, Vec P2, double r, Color c={255,0,0}) 
            : Segment(P1,P2,c){
        radius = r;
    }
    double dist(Vec p){
        return Segment::dist(p) - radius;
    }
    double distSquared(Vec p){
        return pow(dist(p),2);
    }
};

#endif