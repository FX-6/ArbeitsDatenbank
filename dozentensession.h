#ifndef DOZENTENSESSION_H
#define DOZENTENSESSION_H

#include "dozent.h"

class DozentenSession {
public:
    DozentenSession(int dozent_id);
    Dozent* get_dozent();

private:
    Dozent *dozent;
};

#endif // DOZENTENSESSION_H
