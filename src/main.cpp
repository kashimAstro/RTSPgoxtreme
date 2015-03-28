#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "rtsp.h"

class xApp : public ofBaseApp {
	public:
		ofEasyCam cam;
		ofVideoPlayer p;
		RTSPXtreme rtsp;
		int w,h;

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
			if(key == 'l'){
				vector<string> s = rtsp.list(4);
				for(int i = 0; i < s.size(); i++) {
					cout << s[i] <<endl;
				}
			}
		}
};

int main( ){
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280, 720, OF_WINDOW);
	ofRunApp(new xApp());

}
