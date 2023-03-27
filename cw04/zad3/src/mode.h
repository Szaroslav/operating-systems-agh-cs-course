#ifndef _MODE_H
#define _MODE_H

enum Mode {
    M_PNUMS     = 1,    // Print numbers
    M_STIME     = 2,    // Print current time (single)
    M_PCHANGES  = 3,    // Print number of mode changes
    M_ITIME     = 4,    // Print current time (1 second interval)
    M_EXIT      = 5     // Exit
};

enum Mode parse_mode(const char *);

#endif // _MODE_H