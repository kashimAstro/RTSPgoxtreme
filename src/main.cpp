#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "rtsp.h"

class xApp : public ofBaseApp {
	public:
		ofEasyCam cam;
		ofVideoPlayer p;
		int w,h;
		RTSPXtreme rtsp;

		void setup(){
			ofSetFrameRate(25);

			w=ofGetScreenWidth();
			h=ofGetScreenHeight();

			string path = rtsp.getCameraMediaPath();
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
