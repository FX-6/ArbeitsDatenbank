#include "dozentensession.h"

DozentenSession::DozentenSession(int dozent_id) {
    this->dozent = new Dozent(dozent_id);
}

Dozent* DozentenSession::get_dozent() {
    return this->dozent;
}
