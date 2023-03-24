#ifndef _SIGNALS_H
#define _SIGNALS_H

enum Signal {
    SIG_IGNORE,
    SIG_HANDLER,
    SIG_MASK,
    SIG_PENDING
};

enum Signal parse_signal(const char *);

#endif // _SIGNALS_H