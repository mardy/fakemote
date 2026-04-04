#ifndef LOGGING_H
#define LOGGING_H

#define LOG_INFO(...) printf(__VA_ARGS__)
#if DEBUG
#define LOG_DEBUG(...) printf(__VA_ARGS__)
#else
#define LOG_DEBUG(...) (void)0
#endif

#endif
