#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <atomic>
extern "C" {
  #include <ppapi/c/pp_resource.h>
}
class resource {
public:
    resource();
    virtual ~resource() = default;
    void add_ref();
    void release();
    PP_Resource pp_resource();
    friend void intrusive_ptr_add_ref(const resource*);
    friend void intrusive_ptr_release(const resource*);
private:
    const PP_Resource key;
    std::atomic<int> ref_count = 0;
}
void intrusive_ptr_add_ref(const resource*);
void intrusive_ptr_release(const resource*);
#endif