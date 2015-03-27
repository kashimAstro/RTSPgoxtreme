#include "ofMain.h"
#include "ofAppGlutWindow.h"

class xApp : public ofBaseApp {
	public:
		ofEasyCam cam;
		int w,h;
		ofVideoPlayer p;

		string getCameraMediaPath( int width=640, int height=360, int quality=50, int bitrate=0x2dc6c0 ) { 
		        string buffer;
		        buffer = "rtsp://192.168.1.1/MJPG?W=";
		        buffer += ofToString(width);
		        buffer += ofToString("&H=");
		        buffer += ofToString(height);                              
		        buffer += ofToString("&Q=");
		        buffer += ofToString(quality);
		        buffer += ofToString("&BR=");
		        buffer += ofToString(bitrate);
		        return buffer;                  
		}

		void setup(){
			ofSetFrameRate(150);

			w=ofGetScreenWidth();
			h=ofGetScreenHeight();
			string path = getCameraMediaPath();
			p.loadMovie(path);
			p.play();
		}

		void update(){
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
			p.update();
		}

		void draw(){
			ofBackgroundGradient(255,0);
			p.draw(0,0);
		}

		void keyPressed(int key){

		}
};

int main( ){
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280, 720, OF_WINDOW);
	ofRunApp(new xApp());

}
