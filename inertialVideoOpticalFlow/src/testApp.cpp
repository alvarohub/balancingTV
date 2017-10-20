#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    recordedMode=true;
     sense=-1;
    showFlow=false;
    showMeanFlow=false;
    
    int w=640, h=480;
    
    int screenW = ofGetScreenWidth();
	int screenH = ofGetScreenHeight();
    
    centerDisplay.setInitialCondition(screenW/2-w/2, screenH/2-h/2,0,0);
    centerDisplay.setIntegrationStep(0.7);
    centerDisplay.mass=1000; // ideally infinite here (anyway, we won't integrate the motion of the centerDisplay mass)
    centerDisplay.setWallLimits(screenW, screenH, 0,0);
    
    centerWindow.setInitialCondition(screenW/2-w/2, screenH/2-h/2 ,0,0);
    centerWindow.setIntegrationStep(0.2);
    centerWindow.mass=0.5; // mass could change depending on WHAT is moving on the screen...
    centerWindow.setWallLimits(screenW-w, screenH-h, 0,0);
    // set initial window position:
	ofSetWindowPosition(centerWindow.pos.x,centerWindow.pos.y);
    
    // the spring from the moving window to the center of the display:
    centerSpring.distance		= 0;
    centerSpring.springiness	= 0.6f;
    centerSpring.massA = & (centerDisplay);
    centerSpring.massB = & (centerWindow);
   
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(w,h);
    
    // Also, load the video:
    sumoVideo.loadMovie("movies/sumo6.mov");
	sumoVideo.play();

	colorImg.allocate(w,h);
	grayImage.allocate(w,h);
	prevGrayImage.allocate(w,h);
	
	flow.setup(w,h);

   
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

    if (recordedMode) {
        sumoVideo.idleMovie();
        if (sumoVideo.isFrameNew()) {
        colorImg.setFromPixels(sumoVideo.getPixels(), sumoVideo.getWidth(), sumoVideo.getHeight());
		grayImage = colorImg;
		//grayImage.mirror(false, true);
		flow.update(grayImage);
        }
    } 
    else { // this means live video mode
        vidGrabber.grabFrame();
        if(vidGrabber.isFrameNew()) {
            colorImg.setFromPixels(vidGrabber.getPixels(), vidGrabber.getWidth(), vidGrabber.getHeight());
            grayImage = colorImg;
            grayImage.mirror(false, true);
            flow.update(grayImage);
        }
    }

    
    // Update mean flow:
    meanFlow=flow.getMeanFlow(ofGetWidth(), ofGetHeight(), 6)*100;
    
    // Set new screen position:
    
    centerWindow.resetForce();
    // We add a force from the optical flow:
    centerWindow.addForce( sense*meanFlow.x, -sense*meanFlow.y );
    // And from the spring:
    centerSpring.update();// this add forces to the particles (from the spring), but we will update the position ONLY for the centerWindow mass:

#ifndef VERLET_METHOD
    centerWindow.addDampingForce(); // only in case of Euler method
#endif
    centerWindow.update(); // unconstrained
    centerWindow.bounceOffWalls(); // constrain position

    // Now we can set the position of the window:
    //int posx = ofGetWindowPositionX();
	//int posy = ofGetWindowPositionY();
    ofSetWindowPosition(centerWindow.pos.x,centerWindow.pos.y);
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xffffff);
    colorImg.draw(0,0, ofGetWidth(), ofGetHeight());
	//grayImage.draw(0,0, ofGetWidth(), ofGetHeight());
    if (showFlow) flow.draw(ofGetWidth(), ofGetHeight(), 3);
    
    // Show mean flow:
    if (showMeanFlow) {
    ofSetColor(255,0,0); ofSetLineWidth(2);
    ofLine( ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2+meanFlow.x, ofGetHeight()/2+meanFlow.y );

    }
}
//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if(key==' ') sense*=-1;
    if (key=='m') recordedMode=!recordedMode;
    if (key=='f') showFlow=!showFlow;
    if (key=='a') showMeanFlow=!showMeanFlow;
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

