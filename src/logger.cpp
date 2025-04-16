#include "logger.h"

LOG logLvl;


/**
 * @brief Logs a message if the message level is equal to or higher than the output level.
 * @param outLvl The level of the output
 * @param messageLvl The level of the message.
 * @param message The message to log.
 */
void LOGGER(LOG outLvl, LOG messageLvl, std::string message) {

    switch (messageLvl){
        case LOG::ERROR:
            LOG_ERROR(outLvl, message);
            break;
        case LOG::WARN:
            LOG_WARN(outLvl, message);
            break;
        case LOG::INFO:
            LOG_INFO(outLvl, message);
            break;
        case LOG::DEBUG:
            // LOG_DEBUG(outLvl, message);
            break;
        default:
            break;
    }
}

/**
 * @brief Logs an error message.
 * @param outLvl The level of the output
 * @param message The message to log.
 */
void LOG_ERROR(LOG outLvl, std::string message) {
    if (LOG::ERROR <= outLvl) {
        std::cout << "E: " << message << std::endl;
    }
}

/**
 * @brief Logs a warning message.
 * @param outLvl The level of the output
 * @param message The message to log.
 */
void LOG_WARN(LOG outLvl, std::string message) {
    if (LOG::WARN <= outLvl) {
        std::cout << "W: " << message << std::endl;
    }
}

/**
 * @brief Logs an informational message.
 * @param outLvl The level of the output
 * @param message The message to log.
 */
void LOG_INFO(LOG outLvl, std::string message) {
    if (LOG::INFO <= outLvl) {
        std::cout << "I: " << message << std::endl;
    }
}

/**
 * @brief Logs a debug message.
 * @param outLvl The level of the output
 * @param message The message to log.
 */
void LOG_DEBUG(LOG outLvl, std::string message) {
    if (LOG::DEBUG <= outLvl) {
        std::cout << "D: " << message << std::endl;
    }
}
