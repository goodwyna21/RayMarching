#include "configsIn.h"
const string rendLoc = "/Users/goodwyna21/Desktop/renderer/";

void data(Camera& c){
    Table t(cout,"Camera",4);
    t.add({"","X","Y","Z"});
    t.add(toTableEntry("Camera",c.pos));
    t.add(toTableEntry("Target",c.target));
    t.add(toTableEntry("Scr TL",c.screen(-10,10)));
    t.add(toTableEntry("Scr BR",c.screen(10,-10)));
    t.sep="";
    t.show(false,false,false);
    t.clear();
    cout<<"\n";

    t.title = "Distances";
    t.add("Top Left",c.screen(-10,10).dist(c.pos));
    t.add("Bot Right",c.screen(10,-10).dist(c.pos));
    t.show(false,false,false);
}

void run(string conf_fname) {
    string fname,path;
    int img_width,img_height,frames,scene_w,scene_h,scene_d;
    double fov_x,fov_y;
    Vec light,cam_pos,cam_targ;
    Color background,diffuse;
    vector<Body*> objects;
    vector<vector<Body*>> keyframes;
    
    popVars(conf_fname,fname,path,frames,img_width,img_height,scene_w,scene_h,scene_d,
        background,diffuse,light,cam_pos,cam_targ,fov_x,fov_y,objects,keyframes);

    Scene * s = new Scene(scene_w,scene_h,scene_d,background,diffuse);
    s->source = Lamp(light);
    s->objects = objects;
    Camera cam(cam_pos,cam_targ,fov_x,fov_y,s);
    
    //time render
    auto start = chrono::high_resolution_clock::now(); 
    Image img = cam.render(img_width,img_height);
    double dur = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count(); 
    img.savePPM(fname);
    delete s;
    cout << "\n\nTime to render: " << niceDeci(dur/1000.0) << "s";
    
    data(cam);
}

int main(){
	Scene* s = new Scene(400, 400, 400, { 244,164,66 });
	s->source = Lamp({ 0,0,0 });





    return 0;
}
