#Small Reverse Engineering GOXtreme Wifi Control!

URL RTSP reversed:
rtsp://192.168.1.1/MJPG?W=WIDTH&H=HEIHGT&Q=QUALITY&BR=BITRATE

URL DEFAULT STREAM:
rtsp://192.168.1.1/MJPG?W=360&H=240&Q=50&BR=0x2dc6c0

Example function get video stream:

<pre>
string getCameraMediaPath(int width=640, int height=360, int quality=50, int bitrate=0x2dc6c0) {
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
</pre>

<br>AMAZON goXtreme Wifi Control: http://www.amazon.it/gp/product/B00IYF3T74?psc=1&redirect=true&ref_=oh_aui_detailpage_o02_s00
<br>Description protocol: http://it.wikipedia.org/wiki/Real_Time_Streaming_Protocol
<br>
<p> SPECIFICHE CAMERA GOXTREME:</p>
<ul>
<li> Format image: JPG</li>
<li> Risolution image: 8 MP (3264 x 1080px, interpolati), 5 MP (2560x1920px)</li>
<li> Format video: h.264</li>
<li> Risolution video: 1080p (1920x1080px) @30fps, 720p (1280x720px) @60fps,</li>
<li> 720p (1280x720px) @30fps</li>

![alt tag](https://github.com/kashimAstro/RTSPgoxtreme/blob/master/MY.jpg)
![alt tag](https://github.com/kashimAstro/RTSPgoxtreme/blob/master/rtsp.png)

