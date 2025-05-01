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
bool assignShifts( const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, 
  DailySchedule& sched, vector<size_t>& shiftCount, size_t dayIndex, size_t workerSlot);


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

    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();

    sched.resize(numDays, vector<Worker_T>(dailyNeed, INVALID_ID));

    vector<size_t> shiftCount(numWorkers, 0);

    return assignShifts(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0);
}

bool assignShifts( const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, 
  DailySchedule& sched, vector<size_t>& shiftCount, size_t dayIndex, size_t workerSlot){

    //base case
    //schedule is fully build
    if (dayIndex == sched.size()){
      return true;
    }

    size_t numWorkers = avail[0].size();

    //check each worker
    for (Worker_T w = 0; w < numWorkers; w++){
      if (avail[dayIndex][w] && shiftCount[w] < maxShifts && find(sched[dayIndex].begin(), sched[dayIndex].end(), w) == sched[dayIndex].end()){
        sched[dayIndex][workerSlot] = w;
        shiftCount[w]++;

        //move to next day or slot ig
        bool success;

        if (workerSlot+1 == dailyNeed){
          success = assignShifts(avail, dailyNeed, maxShifts, sched, shiftCount, dayIndex+1, 0);
        }
        else {
          success = assignShifts(avail, dailyNeed, maxShifts, sched, shiftCount, dayIndex, workerSlot + 1);
        }

        if (success) return true;
        
        //backtrack
        sched[dayIndex][workerSlot] = INVALID_ID;
        shiftCount[w]--;

      }
      
      
    }

    //no valid assignment found
    return false; 
}
  

