/**
 * @file
 * @author Talita
 * @brief Functions to log things at different levels
 * @date 2025-04-14
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

/// @brief the levels of logging information
enum LOG{
    QUIET,
    ERROR,
    WARN,
    INFO,
    DEBUG,
};

extern LOG logLvl;

void LOGGER(LOG outLvl, LOG messageLvl, std::string);

void LOG_ERROR(LOG outLvl, std::string);
void LOG_WARN(LOG outLvl, std::string);
void LOG_INFO(LOG outLvl, std::string);
void LOG_DEBUG(LOG outLvl, std::string);


#endif //LOGGER_H