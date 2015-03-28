#include "ofMain.h"
#include "ftp.h"

class RTSPXtreme {
	private:
	string host;
	string user;
	string pass;
	vector<string> remote_path;

        public:
        FTP client;
	
	RTSPXtreme() {
		host="192.168.1.1";
		user="1234567890";
		pass="1234567890";

		client.setup(host,user,pass);
		client.setVerbose(true);

		remote_path.push_back("/");             //0
		remote_path.push_back("/DCIM/");	//1
		remote_path.push_back("/DCIM/100CARDV/");//2
		remote_path.push_back("/DCIM/100EVENT/");//3
		remote_path.push_back("/DCIM/100IMAGE/");   //4
		remote_path.push_back("/DCIM/100VIDEO/");   //5
		cout<<"init"<<endl;
	}

	~RTSPXtreme(){

	}

	vector<string> list(int path){
		cout<<"path:"<<remote_path[path]<<endl;
		return client.list(remote_path[path]);
	}

	string getCameraTrack1() {
		string buffer;
		buffer = "rtsp://192.168.1.1/MJPG/track1";
		//rtsp://192.168.1.1/MJPG/track1;seq=25838;rtptime=100001581
		return buffer;
	}

        string getCameraMediaPath( int width=640, int height=360, int quality=80, int bitrate=0x2dc6c0 ) {
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

        void takePhoto(){

        }

        void recordingVideo(){

        }

        void off(){

        }

	bool sendFile(string _path, string remotepath) {
		ofFile file(_path);
		string path = file.path().substr(0,file.path().length()-file.getFileName().length());
		if(client.send(file.getFileName(),path,"/")>0){
			return true;
		}
		return false;
	}

	bool getFile(string name, string path, int remotepath){	
		if(client.get(name,path,remote_path[remotepath])>0){
		       return true;
		}
		return false;
	}

	string getHost(){
		return host;
	}

	string getUser(){
		return user;
	}

	string getPass(){
		return pass;
	}

};
