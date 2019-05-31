#include "Camera.h"
const string rendLoc = "/Users/goodwyna21/Desktop/renderer/";

vector<Body *> axis(){
    return {
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
}

vector<Body*> anim(uint, uint);

void run(string fname, const uint width, const uint height, uint n=1, uint tot=1) {
    Vec targ = {0,0,0};
    double fov = pi/4;
    
    //scene
    Scene * s = new Scene(400,400,400,{200,200,255});
    s->objects = anim(n,tot);
    s->source = Lamp({-50,0,-200});
    
    //camera
    Camera c;
    Vec cam({75,0,-200});
    c = Camera(cam,targ,fov,fov,s);

    //displays
    if(tot<=1){
        Table t(cout,"Camera",4);
        t.add({"","X","Y","Z"});
        t.add(toTableEntry("Camera",c.pos));
        t.add(toTableEntry("Target",c.target));
        t.add(toTableEntry("Scr TL",c.screen(-10,10)));
        t.add(toTableEntry("Scr BR",c.screen(10,-10)));
        t.show();t.clear();cout<<"\n";

        t.title = "Distances";
        t.add("Top Left",c.screen(-10,10).dist(c.pos));
        t.add("Bot Right",c.screen(10,-10).dist(c.pos));
        t.show();t.clear();cout<<"\n";
    }
    
    Image img;
    
    if(tot<=1){
        auto start = chrono::high_resolution_clock::now(); 
        img = c.render(width,height);
        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); 
        cout << "Time taken by function: " << niceDeci(duration.count()/1000.0) << " seconds\n";     
    }else{
        img = c.render(width,height);
    }
    img.savePPM(fname);
    delete s;
}

vector<Body*> anim(uint n, uint tot){
    return {
        new Cutout({
            new Sphere({compress(n,0,tot-1,-150,150),0,0},50),
            new Cylinder({0,-25,-200},{0,-25,200},50)
        })
    };
}

int gif(string fname,uint tot){
    cout << "|";
    for(int i = 0; i < tot; i++){cout << "-";}
    cout << "|\n ";
    for(int i = 0; i < tot; i++){
        run(rendLoc+fname+to_string(i)+".ppm",200,200,i,tot);
        cout << "-";
    }
    return 0;
}

int main(){
    return gif("cutoutAnim/",12);
    
    //run(rendLoc+"compoundGif/test"+".ppm",200,200);
    return 0;
}
