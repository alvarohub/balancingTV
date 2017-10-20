#ifndef SPRING2_H
#define SPRING2_H

// Springs between particles of the active contour:

#include "classPointMass.h"

class Spring {

	public:

		Spring();
		
		pointMass * massA;
		pointMass * massB;
		
		float distance;
		float springiness;	 // this is the k, springiness constant
	
		void update();
	
};


#endif
