#ifndef ADMINSESSION_H
#define ADMINSESSION_H

#include "admin.h"

class AdminSession {
public:
    AdminSession(int admin_id);
    Admin* get_admin();

private:
    Admin *admin;
};

#endif // ADMINSESSION_H
