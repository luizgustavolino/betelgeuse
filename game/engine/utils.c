//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <math.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int roundFloatToInt(float x){
    int y;

    y = (int)(x + 0.5);

    return y;
}

float deg2rad(float deg) {
  return (deg * PI / 180);
}

float rad2deg(float rad) {
  return (rad * 180 / PI);
}

// Code by David Heffernan
// from: https://bit.ly/2zVGJZS (oct 6, 2018)

	char* allocStringJoining(const char *s1, const char *s2){

		// +1 for the null-terminator
	    char *result = malloc(strlen(s1) + strlen(s2) + 1); 
	    strcpy(result, s1);
	    strcat(result, s2);
	    
	    return result;
	}


// Based on code by Warren Moore
// from: https://github.com/warrenm/AHEasing (oct 20, 2018)

	// -- cubicEaseInOut
	// Modeled after the piecewise cubic
	// y = (1/2)((2x)^3)       ; [0, 0.5)
	// y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
	float cubicEaseInOut(float p){
		if(p < 0.5){
			return 4.0 * p * p * p;
		} else {
			float f = ((2.0 * p) - 2.0);
			return 0.5 * f * f * f + 1.0;
		}
	}

	// -- cubicEaseOut
	// Modeled after the cubic y = (x - 1)^3 + 1
	float cubicEaseOut(float p){
		float f = (p - 1);
		return f * f * f + 1;
	}

	// -- bounceEaseOut
	// proportional quad functions
	float bounceEaseOut(float p){
		if(p < 4/11.0) return (121 * p * p)/16.0;
		else if(p < 8/11.0) return (363/40.0 * p * p) - (99/10.0 * p) + 17/5.0;
		else if(p < 9/10.0) return (4356/361.0 * p * p) - (35442/1805.0 * p) + 16061/1805.0;
		else return (54/5.0 * p * p) - (513/25.0 * p) + 268/25.0;
	}

	// -- backEaseOut
	// Modeled after overshooting cubic
	// y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
	float backEaseOut(float p){
		float f = (1 - p);
		return 1 - (f * f * f - f * sin(f * PI));
	}

	float applyCubicEaseInOut(int fromFrame, int toFrame, int current, float delta){

		if (current >= toFrame) return delta;
		if (current <= fromFrame) return 0.0;

		float percent = ((float) current - (float) fromFrame) / ((float) toFrame - (float)fromFrame);
		float easeTransformed = cubicEaseInOut(percent);
		return delta * easeTransformed;
	}

	float applyCubicEaseOut(int fromFrame, int toFrame, int current, float delta){

		if (current >= toFrame) return delta;
		if (current <= fromFrame) return 0.0;

		float percent = ((float) current - (float) fromFrame) / ((float) toFrame - (float)fromFrame);
		float easeTransformed = cubicEaseOut(percent);
		return delta * easeTransformed;
	}

	float applyBounceEaseOut(int fromFrame, int toFrame, int current, float delta){

		if (current >= toFrame) return delta;
		if (current <= fromFrame) return 0.0;

		float percent = ((float) current - (float) fromFrame) / ((float) toFrame - (float)fromFrame);
		float easeTransformed = bounceEaseOut(percent);
		return delta * easeTransformed;
	}

	float applyBackEaseOut(int fromFrame, int toFrame, int current, float delta){

		if (current >= toFrame) return delta;
		if (current <= fromFrame) return 0.0;

		float percent = ((float) current - (float) fromFrame) / ((float) toFrame - (float)fromFrame);
		float easeTransformed = backEaseOut(percent);
		return delta * easeTransformed;
	}

//Capture the thief before FRIDAY
//Can work from 9:00 to 18:00, so after 18:00 PM change day

//Function that calculates the travel time between cities and returns time in hour and minutes.
//Input should be (City A Latitude, City A Longitude, City B Latitude, City B Longitude)
//Max travel time based on: Max distance 4.394km (North to South), JET average speed 2.000 km/h. -> MAX TIME: 130 minutes
//I added up the airport times to it to make it more believable. So each flight is equal to 3 hours + Jet travel time.
//We can tweak these numbers for balance purposes.
int travelTime(float lat1, float lon1, float lat2, float lon2){

    //***CODE FROM GEODATASOURCE -> https://www.geodatasource.com/developers/c***
    float theta, dist;

    theta = lon1 - lon2;
    dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;
    //Distance in km
    dist = dist * 1.609344;
    //***End of code from source***

    const int airportTime = 180; //Airport time in minutes. Same for every flight
    int minutes = roundFloatToInt(airportTime + dist * 60/2000); //1 hour (in minutes) divided by the speed of the JET times the travel distance
	return minutes;
}