#ifndef CONFIGSIN_H
#define CONFIGSIN_H

#include "Camera.h"

const vector<Body *> defaultAxis = {
        new Sphere({ 0, 0, 0},12,{255,255,255}),//center white
        new Sphere({ 100,0,0},12,{255,0,0}),    //pos x  red
        new Sphere({-100,0,0},12,{255,255,0}),  //neg x  yellow
        new Sphere({0, 100,0},12,{0,255,0}),    //pos y  green
        new Sphere({0,-100,0},12,{0,255,255}),  //neg y  cyan
        new Sphere({0,0, 100},12,{0,0,255}),    //pos z  blue
        new Sphere({0,0,-100},12,{255,0,255}),  //neg z  purple
        
        new Segment({-100,0,0},{100,0,0},{255,0,0}), //x  red
        new Segment({0,-100,0},{0,100,0},{0,255,0}), //y  green
        new Segment({0,0,-100},{0,0,100},{0,0,255})  //z  blue
};

const string DEF_FILENAME="Test";
const string DEF_FILEPATH="Saves/";
const int DEF_IMAGE_WIDTH=200;
const int DEF_IMAGE_HEIGHT=200;

const int DEF_SCENE_WIDTH=400;
const int DEF_SCENE_HEIGHT=400;
const int DEF_SCENE_DEPTH=400;
const Color DEF_BACKGROUND={0,200,200};
const Color DEF_DIFFUSE={0,200,200};

const Vec DEF_LIGHT={200,0,0};
const Vec DEF_CAMERA={0,0,-200};
const Vec DEF_CAM_TARGET={0,0,0};
const double DEF_FOV_X=(pi/2);
const double DEF_FOV_Y=(pi/2);

const vector<Body*> DEF_BODIES=defaultAxis;
const int DEF_FRAMES=1;
const vector<vector<Body*>> DEF_KEYFRAMES;

HashTable<string,string,20>& parseConfig(string fname){
    ifstream f(fname,ios::in);
    string line;
    int n;
    HashTable<string,string,20> vals;
    while(getline(f,line)){
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        if(line[0]!='#' && line.size()>0 && (n=line.find('='))!=line.size()-1){
            vals.push(line.substr(0,n),line.substr(n+1,line.size()-(n+1)));
        }
    }
    return vals;
}

template <typename T>
void parseList(string str,initializer_list<T*> variables){
    if(str[0]=='{')str.erase(0,1); //remove braces
    if(str[str.size()-1]=='}')str.erase(str.size()-1,1);
    stringstream ss(str);
    vector<string> result;
    vector<T*> vars = variables;
    while(ss.good()){
        string substr;
        getline(ss,substr,',');
        result.push_back( substr );
    }
}


void popVars(string conf_fname,
        string& fname,string& path,int& frames,
        int& img_width,int& img_height,
        int& scene_w,int& scene_h,int& scene_d,
        Color& background,Color& diffuse,
        Vec& light,Vec& cam_pos,Vec& cam_targ,
        double& fov_x,double& fov_y,
        vector<Body*>& objects,vector<vector<Body*>>& keyframes){
    HashTable<string,string,20> paras = parseConfig(conf_fname);
    
    try{ //string fname
        fname=paras["FILENAME"];
    }catch(out_of_range& err){
        fname=DEF_FILENAME;
    }
    try{ //string path
        path=paras["FILEPATH"];
    }catch(out_of_range& err){
        path=DEF_FILEPATH;
    }
    try{ //int frames
        frames=stoi(paras["FRAMES"]);
    }catch(out_of_range& err){
        frames=DEF_FRAMES;
    }
    try{ //int img_width
        img_width=stoi(paras["IMAGE_WIDTH"]);
    }catch(out_of_range& err){
        img_width=DEF_IMAGE_WIDTH;
    }
    try{ //int img_height
        img_height=stoi(paras["IMAGE_HEIGHT"]);
    }catch(out_of_range& err){
        img_height=DEF_IMAGE_HEIGHT;
    }
    try{ //int scene_w, scene_h, scene_d
        string temp=paras["SCENE_SIZE"];
        stringstream ss( "1,1,1,1, or something else ,1,1,1,0" );
        vector<string> result;

        while( ss.good() )
        {
            string substr;
            getline( ss, substr, ',' );
            result.push_back( substr );
        }
        
    }catch(out_of_range& err){
        //fname=DEF_ FILENAME;
    }
    try{ //Color background
        fname=paras["BACKGROUND"];
    }catch(out_of_range& err){
        fname=DEF_BACKGROUND;
    }
    try{ //Color diffuse
        fname=paras["DIFFUSE"];
    }catch(out_of_range& err){
        fname=DEF_DIFFUSE;
    }
    try{ //Vec light
        fname=paras["LIGHT"];
    }catch(out_of_range& err){
        fname=DEF_LIGHT;
    }
    try{ //Vec cam_pos
        fname=paras["CAMERA"];
    }catch(out_of_range& err){
        fname=DEF_CAMERA;
    }
    try{ //Vec cam_targ
        fname=paras["CAM_TARGET"];
    }catch(out_of_range& err){
        fname=DEF_CAM_TARGET;
    }
    try{ //double fov_x
        fname=paras["FOV_X"];
    }catch(out_of_range& err){
        fname=DEF_FOV_X;
    }
    try{ //double fov_y
        fname=paras["FOV_Y"];
    }catch(out_of_range& err){
        fname=DEF_FOV_Y;
    }
    try{ //vector<Body*> objects
        fname=paras["OBJECTS"];
    }catch(out_of_range& err){
        fname=DEF_OBJECTS;
    }
    try{ //vector<vector<Body*>> keyframes
        fname=paras["KEYFRAMES"];
    }catch(out_of_range& err){
        fname=DEF_KEYFRAMES;
    }
}

#endif /* CONFIGSIN_H */

