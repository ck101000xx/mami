#include "resource.hpp"

#include "resource_map.hpp"
resource::resource() : key(resource_map::get_instance().insert(this)) {
}
void resource::add_ref() {
    ++ref_count;
}
void resource::release() {
    if (--ref_count == 0) {
        resource_map::get_instance().erase(key);
        delete this;
    }
}
PP_Resource pp_resource() {
    return key;
}
void intrusive_ptr_add_ref(const resource* res) {
    res->add_ref();
}
void intrusive_ptr_release(const resource* res) {
    res->release();
}
