#ifndef RESOURCE_MAP_HPP
#define RESOURCE_MAP_HPP
#include <atomic>
#include <utility>
#include <tbb/concurrent_hash_map.h>
extern "C" {
  #include <ppapi/c/pp_resource.h>
}

namespace mami {
namespace internal {
class resource_map {
private:
    template<class T>
    typedef tbb::concurrent_hash_map<PP_Resource, T *> hash_map_t;
public:
    template<class T>
    static PP_Resource insert(T * p) {
        PP_Resource key = next_key();
        hash_map<T>.insert({key, p});
        return key;
    }
    template<class T>
    static T* find(PP_Resource key) {
        hash_map_t<T>::const_accessor result;
        return hash_map<T>.find(result, key) ? result->second : nullptr ;
    }
    template<class T>
    static void erase(PP_Resourcre key) {
        hash_map<T>.erase(key);
    }
private:
    static PP_Resource next_key() {
        static std::atomic<PP_Resource> last_key(0);
        return ++last_key;
    }
    template<class T>
    static const hash_map_t<T> hash_map;
};
template<class T>
const resource_map::hash_map_t<T> resource_map::hash_map;
}
}
#endif