/*
    YEAR-2038 Problem
    2147483647 -> unix time stamp will end at this time, on January 19, 2038 at 3 hours 14 minutes 7 seconds
    Because 2147483647  is the maximum positive value for a 32-bit signed binary integer in computing.
*/

#include<bits/stdc++.h>

using namespace std;

bool isLeapYear(int currYear)
{
    if(currYear % 400 == 0 || (currYear % 4 == 0 && currYear % 100 != 0))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

// seconds -> DD:MM:YYYY:HH:MM:SS, Start of unix time - 01 Jan 1970, 00:00:00

string unixTimeStampToHumanReadable(long int unixTime) 
{
    string ans = "";
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long int currYear,
    daysTillNow,
    extraTime,
    extraDays,
    index,
    date,
    month,
    hours,
    minutes,
    seconds,
    flag = 0;

    // adding 1 because daysTillNow will give days till previous day and we have to include current day for DATE and MONTH
    daysTillNow = (unixTime / (24 * 60 * 60)) + 1;

    extraTime = unixTime  % (24 * 60 * 60);

    currYear = 1970;     // year calculation will start from Epoch's year (1970)


// calculating currrent year
    while((daysTillNow > 365 && !isLeapYear(currYear)) || ((daysTillNow > 366 && isLeapYear(currYear))))
    {
        if(isLeapYear(currYear)) // checking if an year is a leap year
        {
            daysTillNow -= 366;
        }
        else                    // otherwise
        {
            daysTillNow -= 365;
        }
        currYear += 1; 
    }

// updating extradays    
    extraDays = daysTillNow; // because daysTillNow is reduced till remaining days
    
    if(isLeapYear(currYear)) 
        flag = 1;
    
// calculating MONTH and DATE
    month = 0, index = 0; 
    if(flag == 1) // if it is a leap year
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
                if(extraDays <= 0)
                    break;
            }
            index += 1;
        }
    }

    else          // if this is not a leap year
    {
        while(true)
        { 
            if(extraDays - daysOfMonth[index] < 0)
                break;
            month += 1;
            extraDays -= daysOfMonth[index];
            if(extraDays <= 0)
                break;
            index += 1; 
        }
    }

    if(extraDays > 0) // we are in (month + 1)th month.
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

// calculating Hours:Minutes:Seconds    
    
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    seconds = (extraTime % 3600) % 60;
    
    ans += to_string(date);
    ans += " : ";
    ans += to_string(month);
    ans += " : ";
    ans += to_string(currYear);
    ans += " : ";
    ans += to_string(hours);
    ans += " : ";
    ans += to_string(minutes);
    ans += " : ";
    ans += to_string(seconds);
    

    return ans;
}

int main()
{
    long int seconds = 2147483647  ;

    string ans = unixTimeStampToHumanReadable(seconds);
    
    cout<<ans<<"\n";

    return 0;
}
