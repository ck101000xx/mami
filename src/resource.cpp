#include "resource.hpp"

#include "resource_map.hpp"
resource::resource() {
    key = resource_map::get_instance().insert(this);
}
void intrusive_ptr_add_ref(const resource* res) {
    resource_map::get_instance().add_ref(res->key);
}
void intrusive_ptr_release(const resource* res) {
    resource_map::get_instance().release(res->key);
}
