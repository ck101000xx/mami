#include "resource_map.hpp"

static resource_map& resource_map::get_instance() {
    static resource_map instance;
    return instance;
}
PP_Resource resource_map::insert(resource *ptr) {
    int key = ++last_resource_key;
    hash_map.insert({key, {0, new boost::intrusive_ptr(ptr, false)}});
    return key;
}
boost::intrusive_ptr<resource> resource_map::find(PP_Resource key) {
    hash_map_t::const_accessor result;
    hash_map.find(result, key);
    return result->second.second;
}
void resource_map::add_ref(PP_Resource key) {
    hash_map_t::const_accessor result;
    if (!hash_map.find(result, key)) return;
    ++result->second.first;
}
void resource_map::release(PP_Resource key) {
    hash_map_t::const_accessor result;
    if (!hash_map.find(result, key)) return;
    if (--result->second.first == 0) {
        hash_map.erase(result);
    }
}