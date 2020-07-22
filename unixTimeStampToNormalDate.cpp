/*
    YEAR-2038 Problem
    2147483647 seconds -> unix time stamp will end at this time, on January 19, 2038 at 3 hours 14 minutes 7 seconds
    Because 2147483647  is the maximum positive value for a 32-bit signed binary integer in computing.
*/

#include<bits/stdc++.h>

using namespace std;

// seconds -> DD:MM:YYYY:HH:MM:SS, Start of unix time - 01 Jan 1970, 00:00:00

string unixTimeStampToHumanReadable(long int seconds) 
{
    string ans = "";
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    long int currYear,
    daysTillNow,
    extraTime,
    extraDays,
    index,
    date,
    month,
    hours,
    minutes,
    secondss,
    flag = 0;

    daysTillNow = seconds / (24 * 60 * 60),
    extraTime = seconds  % (24 * 60 * 60),
    currYear = 1970;

// calculating currrent year
    while(daysTillNow >= 365)
    {
        if(currYear % 400 == 0 || (currYear % 4 == 0 && currYear % 100 != 0))
        {
            daysTillNow -= 366;
        }
        else
        {
            daysTillNow -= 365;
        }
        currYear += 1; 
    }

// updating extradays    
    extraDays = daysTillNow + 1; // because extradays will give days till previous day and we have to include current day for DATE
    
    if(currYear % 400 == 0 || (currYear % 4 == 0 && currYear % 100 != 0))
        flag = 1;
    
// calculating MONTH and DATE
    month = 0, index = 0; 
    if(flag == 1)
    {
        while(true)
        {
            
            if(index == 1)
            {
                if(extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
                
            }
            else
            {
                if(extraDays - daysOfMonth[index] < 0)
                    break;
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else
    {
        while(true)
        {
            
            if(extraDays - daysOfMonth[index] < 0)
                break;
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
            
            
        }
    }

    if(extraDays > 0)
    {
        month += 1;
        date = extraDays;
    }
    else
    {
        if(month == 2 && flag == 1)
            date = 29;
        else
        {
            date = daysOfMonth[month - 1];
        }
        
    }

// calculating HH:MM:YYYY    
    
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;
    
    ans += to_string(date);
    ans += ":";
    ans += to_string(month);
    ans += ":";
    ans += to_string(currYear);
    ans += ":";
    ans += to_string(hours);
    ans += ":";
    ans += to_string(minutes);
    ans += ":";
    ans += to_string(secondss);
    

    return ans;
}

int main()
{
    long int seconds;
    cin>>seconds;

    string ans = unixTimeStampToHumanReadable(seconds);
    
    cout<<ans<<"\n";

    return 0;
}
