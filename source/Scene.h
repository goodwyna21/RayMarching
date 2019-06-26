#ifndef SCENE_H
#define SCENE_H

#include "Bodies.h"

struct _distWrapper{
    double dist;
    Body * obj;
    string toString(){
        return to_string(dist) + " " + ((obj==nullptr)?"nullptr":obj->type());
    }
};

struct Scene{
    vector<Body* > objects;
    Color background;
    Color diffuse;
    Lamp source;
    Vec FTL,BBR; //front top left, bottom back right
    Scene(){}
    ~Scene(){
        for(int i = 0; i < objects.size(); i++){
            delete objects.at(i);
        }
    }
    Scene(double width, double height, double depth, Color bkg={255,255,255}, Color dfse={0,0,0}){
        FTL = {-0.5*width,0.5*height,-0.5*depth};
        BBR = {0.5*width,-0.5*height,0.5*depth};
        background=bkg;
        diffuse=dfse;
    }
    Scene& setLamp(Lamp l){
        source = l;
        return *this;
    }
    Scene& setObjects(initializer_list<Body* > objs){
        objects = objs;
        return *this;
    }
    void addObject(Body * obj){
        objects.push_back(obj);
    }
    _distWrapper minDist(Vec v){
        if(objects.size()==0){return {0,nullptr};}
        double min = INT_MAX;
        Body * coll = nullptr;
        double d;
        for(int i = 0; i < objects.size(); i++){
            d = objects.at(i)->dist(v);
            if(d < min){
                min = d;
                coll = objects.at(i);
            }
        }
        return {min,coll};
    }
    
    bool inbounds(Vec v){
        return (v[x] > FTL[x] && v[x] < BBR[x] &&
                v[y] < FTL[y] && v[y] > BBR[y] &&
                v[z] > FTL[z] && v[z] < BBR[z]);
    }
};
#endif /* SCENE_H */

