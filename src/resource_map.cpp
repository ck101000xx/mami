#include "resource_map.hpp"

static resource_map& resource_map::get_instance() {
    static resource_map instance;
    return instance;
}
PP_Resource resource_map::insert(resource *ptr) {
    int key = ++last_resource_key;
    hash_map.insert({key, ptr});
    return key;
}
boost::intrusive_ptr<resource>& resource_map::find(PP_Resource key) {
    hash_map_t::const_accessor result;
    hash_map.find(result, key);
    return *new boost::intrusive_ptr(result->second);
}
void resource_map::erase(PP_Resource key) {
    hash_map.erase(key);
}