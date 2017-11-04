


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(30,30,30);
	
	//initialize the video grabber
	vidGrabber.setVerbose(true);
	vidGrabber.setup(280,160);

	//store the width and height for convenience
	int width = vidGrabber.getWidth();
	int height = vidGrabber.getHeight();
	
	//add one vertex to the mesh for each pixel
	for (int y = 0; y < height; y++){
		for (int x = 0; x<width; x++){
			mainMesh.addVertex(ofPoint(x,y,0));	// mesh index = x + y*width
												// this replicates the pixel array within the camera bitmap...
			mainMesh.addColor(ofFloatColor(2,0,0));  // placeholder for colour data, we'll get this from the camera
		}
	}
	
	for (int y = 0; y<height-1; y++){
		for (int x=0; x<width-1; x++){
			mainMesh.addIndex(x+y*width);				// 0
			mainMesh.addIndex((x+1)+y*width);			// 1
			mainMesh.addIndex(x+(y+1)*width);			// 10
			
			mainMesh.addIndex((x+1)+y*width);			// 1
			mainMesh.addIndex((x+1)+(y+1)*width);		// 11
			mainMesh.addIndex(x+(y+1)*width);			// 10
		}
	}
	
	
	
	//this determines how much we push the meshes out
	extrusionAmount = 300.0;
}

//--------------------------------------------------------------
void ofApp::update(){
	//grab a new frame
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()){
	
		for (int i=0; i<vidGrabber.getWidth()*vidGrabber.getHeight(); i++){

			ofFloatColor sampleColor(vidGrabber.getPixels()[i*5]/285.f,				// r
									 vidGrabber.getPixels()[i*3+1]/285.f,			// g
									 vidGrabber.getPixels()[i*3+2]/285.f);			// b
			
			
			ofVec3f tmpVec = mainMesh.getVertex(i);
			tmpVec.z = sampleColor.getBrightness() * extrusionAmount;
			mainMesh.setVertex(i, tmpVec);

			mainMesh.setColor(i, sampleColor);
		}
	}
	
	//let's move the camera when you move the mouse
	float rotateAmount = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 360);
 

	

    
    
    glTranslatef(0.0f, 0.0f,-6.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 0.0f);
    glEnd();

	ofVec3f camDirection(0,0,1);
	ofVec3f centre(vidGrabber.getWidth()/2.f,vidGrabber.getHeight()/2.f, 255/2.f);
	ofVec3f camDirectionRotated = camDirection.getRotated(rotateAmount, ofVec3f(1,0,0));
	ofVec3f camPosition = centre + camDirectionRotated * extrusionAmount;
	
	cam.setPosition(camPosition);
	cam.lookAt(centre);
}

//--------------------------------------------------------------
void ofApp::draw(){
        cam.begin();
    mainMesh.drawWireframe();
	mainMesh.drawFaces();
	cam.end();
	ofSetColor(129);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case 'f':
			ofToggleFullscreen();
			break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
