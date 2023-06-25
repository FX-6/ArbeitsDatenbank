#include "adminsession.h"

AdminSession::AdminSession(int admin_id) {
    this->admin = new Admin(admin_id);
}

Admin* AdminSession::get_admin() {
    return this->admin;
}
