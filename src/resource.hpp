#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <ppapi/c/pp_resource.h>
extern "C" {
  #include <ppapi/c/pp_resource.h>
}
class resource {
public:
    resource();
    virtual ~resource() = default;
    friend void intrusive_ptr_add_ref(const resource*);
    friend void intrusive_ptr_release(const resource*);
private:
    PP_Resource key;
}
void intrusive_ptr_add_ref(const resource*);
void intrusive_ptr_release(const resource*);
#endif