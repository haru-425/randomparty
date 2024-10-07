#include "all.h"

float tracking(VECTOR2 target, VECTOR2 tracking_person) {
	VECTOR2 subVector;
	float angle;
	subVector.x = target.x - tracking_person.x;
	subVector.y = target.y - tracking_person.y;

	angle = (float)atan2(subVector.y, subVector.x);
	return angle;
}
