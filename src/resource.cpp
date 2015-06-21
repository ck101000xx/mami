#include "resource.hpp"

#include "resource_map.hpp"
resource::resource() {
    key = resource_map::get_instance().insert(this);
}
void intrusive_ptr_add_ref(const resource* res) {
    ++res->ref_count;
}
void intrusive_ptr_release(const resource* res) {
    if (--res->ref_count == 0) {
        resource_map::get_instance().erase(res->key);
    }
}
