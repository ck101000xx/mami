#ifndef RESOURCE_MAP_HPP
#define RESOURCE_MAP_HPP
#include <utility>
#include <boost/core/noncopyable.hpp>
#include <boost/intrusive_ptr.hpp>
#include <tbb/concurrent_hash_map.h>
#include "resource.hpp"
extern "C" {
  #include <ppapi/c/pp_resource.h>
}

class resource_map : private boost::noncopyable {
public:
    static resource_map& get_instance();
    PP_Resource insert(resource *ptr);
    boost::intrusive_ptr<resource> find(PP_Resource key);
    void add_ref(PP_Resource key);
    void release(PP_Resource key);
    void erase(PP_Resource key);
private:
    resource_map() = default;
    typedef tbb::concurrent_hash_map<PP_Resource, boost::intrusive_ptr<resource> > hash_map_t;
    hash_map_t hash_map;
    std::atomic<PP_Resource> last_resource_key = 0;
}
#endif