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

		string img;
		void keyPressed(int key){
			if(key == 'g'){
				cout<<"width:"<<p.getWidth()<<",height:"<<p.getHeight()<<endl;
				cout<<"path:"<<p.getMoviePath()<<endl;
			        cout<<"position:"<<p.getPosition()<<endl;
				cout<<"speed:"<<p.getSpeed()<<endl;
               			cout<<"duration:"<<p.getDuration()<<endl;
             			cout<<"movieDone"<<p.getIsMovieDone()<<endl;
			}
			if(key == 'l'){
				vector<string> s = rtsp.list(4);
				for(int i = 0; i < s.size(); i++) {
					cout << s[i] <<endl;
				}
				if(s.size()>0){
					img=s[3];
					cout<<"select img:"<<img<<endl;
				}
			}
			if(key == 'd'){
				vector<string> fileName = ofSplitString(img," ");
				string localFolder = "/var/tmp/";
				string remoteFolder= rtsp.getPath(4);
				cout<<"file-name:"<<fileName[fileName.size()-1]<<",local-folder:"<<localFolder<<",remote-folder:"<<remoteFolder<<endl;
				if(rtsp.getFile( fileName[fileName.size()-1], localFolder, remoteFolder )){
					cout<<"download: " <<fileName[fileName.size()-1]<<localFolder<<endl;
				}
			}
			
		}
};

int main( ){
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 640, 360, OF_WINDOW);
	ofRunApp(new xApp());

}
