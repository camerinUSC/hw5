#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

		size_t k = avail[0].size(); // k possible workers
		size_t n = avail.size();   // n day period

		//initalizing schedule
		sched = DailySchedule(n, vector<Worker_T>(dailyNeed));

		//shift counter while in recursion
		vector<size_t> numOfShifts(k,0);

		//backtrack here

		return scheduleHelper(avail, dailyNeed, maxShifts, sched, numOfShifts, 0, 0);

}


bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		vector<size_t> &numOfShifts,
		size_t day,
		size_t position

)

{

		size_t k = avail[0].size(); // k possible workers
		size_t n = avail.size();    // n day period


		//base case (all days filled)

		if(day == n){
			return true;
		}


		// new parameters for recursion
		size_t nextDay = day;		
		size_t nextPosition = position+1;

		//day is filled

		if(nextPosition == dailyNeed){
			nextDay = day+1;
			nextPosition = 0;
		}

		//trying k possible workers

		for(Worker_T index = 0; index < k; index++){

			if(avail[day][index] == 0){
				continue;
			}

			if(numOfShifts[index] >= maxShifts){
				continue;
			}

			//checking if worker is scheduled already

			bool scheduleFlag = false;

			for(size_t x = 0; x < position; x++){
				if(sched[day][x] == index){
					scheduleFlag = true;
					break;
				}
			}

			if(scheduleFlag == 1){
				continue;
			}

			//assign worker

			sched[day][position] = index;
			numOfShifts[index]++;

			//check validity
			if(scheduleHelper(avail, dailyNeed, maxShifts, sched, numOfShifts, nextDay, nextPosition)){
				return true;
			}


			//backtrack here

			sched[day][position] = INVALID_ID;
			numOfShifts[index]--;
		}

		
return false;

}
