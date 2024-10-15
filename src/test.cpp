#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>



int getMaximumTasks(int limit, vector<int> primary, vector<int> secondary)
{
    int ret;  // number of secondary tasks we can comeplete
    
    // sort the secondary
    sort(secondary.begin(), secondary.end());
    
    // loop across each #hrs 
    for (auto h : primary) {
       int rem = limit - h; 
       // check if there is a secondary we can hit
       int secondary_task
       for (auto task : secondary)
       
    }
    
    

    return ret;

