#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxOpticalFlowLK.h"

#include "classPointMass.h"
#include "classSpring.h"

class testApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	ofVideoGrabber 		vidGrabber;
    ofVideoPlayer 		sumoVideo;

	ofxCvColorImage			colorImg;
	ofxCvGrayscaleImage 	grayImage,prevGrayImage;
	ofxOpticalFlowLK		flow;
    
    ofPoint meanFlow;
    
    pointMass centerDisplay, centerWindow;
    Spring centerSpring;
	float sense;
    
    bool showFlow;
    bool recordedMode;
    bool showMeanFlow;
	
};

#endif
