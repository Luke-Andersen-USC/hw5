#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool scheduleHelper(int row, int col,
std::map<int,int>& original, 
AvailabilityMatrix& avail, 
DailySchedule& sched, size_t dailyNeed);
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

    std::map<int,int> workers;
		for(unsigned int i = 0; i < avail[0].size(); i++)
		{
			workers.insert(std::make_pair<int,int>(i,maxShifts));
		}

		std::vector<Worker_T> empty;
		sched.push_back(empty);
		AvailabilityMatrix availCopy = avail;

		bool works = scheduleHelper(0, 0, workers, availCopy, sched, dailyNeed);


		return works;

}

bool scheduleHelper(int row, int col, 
std::map<int,int>& original, 
AvailabilityMatrix& avail, 
DailySchedule& sched, size_t dailyNeed)
{
		//everything true!
    if((unsigned)row == avail.size())
    {
				if(!sched.empty())
				{
					sched.pop_back();
				}
        return true;
    }

		if(sched[row].size() == dailyNeed)
		{
			
			std::vector<Worker_T> empty;
			sched.push_back(empty);
			
			bool next = scheduleHelper(row + 1, 0, original, avail, sched, dailyNeed);

			if(next)
			{
				return next;
			}
			sched.pop_back();
		}
    else 
		{

			for(std::map<int,int>::iterator it = original.begin(); it != original.end(); it++)
			{		
			
				if(avail[row][col] == true && it->second > 0)
				{
					sched[row].push_back(it->first);
					original[it->first] -= 1;

					avail[row][col] = 0;

					bool next = true;
					
					next = scheduleHelper(row, 0, original, avail, sched, dailyNeed);
					
					if(next)
					{
						return next;
					}

					avail[row][col] = 1;
					original[it->first]++;
					sched[row].pop_back();

				}

				col++;
			}
			
		}

		return false;
}
