#include "classSpring.h"
#include "myVectorClass.h"

//---------------------------------------------------------------------
Spring::Spring(){
	massA = NULL;
	massB = NULL;
}

//---------------------------------------------------------------------
void Spring::update(){
	if ((massA == NULL) || (massB == NULL)){
		return;
	}
	
	vector2D pta = massA->pos;
	vector2D ptb = massB->pos;
	
	float theirDistance = (pta - ptb).length();
	float springForce = (springiness * (distance - theirDistance));
	vector2D frcToAdd = (pta-ptb).normalize() * springForce;
	
	massA->addForce(frcToAdd);
	massB->addForce(-frcToAdd);
	//massA->totalForce.x+=frcToAdd.x;massA->totalForce.y+=frcToAdd.y;
	//massB->totalForce.x-=frcToAdd.x;massB->totalForce.y-=frcToAdd.y;
}
