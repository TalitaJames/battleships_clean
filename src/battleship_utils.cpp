#include "battleship_utils.h"

/**
 * @brief Returns the date-time as a string
 * @return the date-time as a std::string
 */
std::string return_current_time_and_date()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}
