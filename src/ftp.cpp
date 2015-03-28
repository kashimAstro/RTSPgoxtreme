#include "ftp.h"

FTP::FTP() {
    ftpClient   = NULL;
    bVerbose    = false;
    host        = "";
    user        = "";
    pass        = "";
    port        = 0;
    bSetup      = false;
}

void FTP::setup(string _host, string username, string password, int _port) {
    host    = _host;
    user    = username;
    pass    = password;
    port    = _port;
    bSetup  = true;
}

int FTP::send(string fileName, string localFolder, string remoteFolder) {
    if( bSetup == false ){
        if( bVerbose ) printf("error - you need to call setup first\n");
        return -1;
    }
    
    int numBytes = 0;
    
    try{
        startFtp();
        
        if( bVerbose )printf("ftp-ing %s\n", fileName.c_str());
        localFolder = ofToDataPath( localFolder );
        if(localFolder.length() > 0){
            if( localFolder[localFolder.length()-1] != '/' ){
                localFolder += "/";
            }
        }
        
        if(remoteFolder.length() > 0){
            if( remoteFolder[remoteFolder.length()-1] != '/' ){
                remoteFolder += "/";
            }
        }
        
        string localPath    = localFolder  + fileName;
        string remotePath   = remoteFolder + fileName;
        
        ostringstream remoteOSS;
        remoteOSS << remoteFolder << fileName;
        
        if( bVerbose )printf("localpath is %s\n remotepath is %s\n", localPath.c_str(), remotePath.c_str());
        
        ftpClient->login(user, pass);
        ftpClient->setFileType(Poco::Net::FTPClientSession::TYPE_BINARY);
        
        ostream& ftpOStream = ftpClient->beginUpload(remoteOSS.str().c_str());  //how to make it overwrite?
        
        ifstream localIFStream(localPath.c_str(), ifstream::in | ifstream::binary);
        numBytes = Poco::StreamCopier::copyStream(localIFStream, ftpOStream);
        ftpClient->endUpload();
        
        endFtp();
        
        if(bVerbose)printf("uploaded %i bytes\n\n", numBytes);
        
    }
    catch (Poco::Exception& exc)
    {
        cout << exc.displayText() << endl;
        return -1;
    }
    return numBytes;

}

int FTP::get(string fileName, string localFolder, string remoteFolder) {
	if( bSetup == false ){
        if( bVerbose )printf("error - you need to call setup first\n");
        return -1;
    }
    int numBytes = 0;
    
    try{
        startFtp();
        if( bVerbose )printf("ftp-ing %s\n", fileName.c_str());
        localFolder = ofToDataPath( localFolder );
        if(localFolder.length() > 0){
            if( localFolder[localFolder.length()-1] != '/' ){
                localFolder += "/";
            }
        }
        
        if(remoteFolder.length() > 0){
            if( remoteFolder[remoteFolder.length()-1] != '/' ){
                remoteFolder += "/";
            }
        }
        
        string localPath    = localFolder  + fileName;
        string remotePath   = remoteFolder + fileName;
        
        ostringstream remoteOSS;
        remoteOSS << remoteFolder << fileName;
        
        if( bVerbose )printf("localpath is %s\n remotepath is %s\n", localPath.c_str(), remotePath.c_str());
        
        ftpClient->login(user, pass);
        ftpClient->setFileType(Poco::Net::FTPClientSession::TYPE_BINARY);
        istream& ftpOStream = ftpClient->beginDownload(remoteOSS.str().c_str());

        ofstream localIFStream(localPath.c_str(), ifstream::out | ifstream::binary);
        numBytes = Poco::StreamCopier::copyStream(ftpOStream, localIFStream);
        ftpClient->endDownload();
        endFtp();
        
        if(bVerbose)printf("downloaded %i bytes\n\n", numBytes);
        
    }
    catch (Poco::Exception& exc)
    {
        cout << exc.displayText() << endl;
        return -1;
    }
}

vector<string> FTP::list(string path) {
    try{
        startFtp();
        string res;
        ftpClient->login(user, pass);
        istream &ist = ftpClient->beginList(path, true);
        Poco::StreamCopier::copyToString(ist, res);
        ftpClient->endList();
        
        return ofSplitString(res, "\n", true, true);
        endFtp();
    }
    catch (Poco::Exception& exc)
    {
        cout << exc.displayText() << endl;
//        return 0;
    }

}
void FTP::setVerbose(bool verbose) {
    bVerbose = verbose;
}
