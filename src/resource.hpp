#ifndef MAMI_RESOURCE_HPP
#define MAMI_RESOURCE_HPP
#include <atomic>
#include <utility>
extern "C" {
  #include <ppapi/c/pp_resource.h>
}
#include "resource_map.hpp"
namespace mami {
template<class T>
class resource {
public:
    virtual ~resource() = default;
    friend class resource_ptr<T>;
protected:
    resource() = default;
private:
    std::atomic<int> ref_count = 0;
};
template<class T>
class resource_ptr {
private:
    typedef resource_ptr<T> this_type;
public:
    template<typename ...Args>
    static resource_ptr<T> & create(Args... args) {
        return *new resource_ptr(new T(args...));
    }
    static void add_ref(PP_Resource key) {
        this_type(key).add_ref();
    }
    static void release(PP_Resource key) {
        this_type(key).release();
    }
    resource_ptr() : key(0), px(nullptr) {}
    resource_ptr(PP_Resource key) : key(key) {
        px = internal::resource_map::find<T>(key);
        add_ref();
    }
    resource_ptr(this_type const & rhs) : key(rhs.key), px(rhs.px) {
        add_ref();
    }
    resource_ptr(this_type && rhs) : key(rhs.key), px(rhs.px) {
        rhs.px = nullptr;
    }
    this_type & operator=(this_tpye const & rhs) {
        resource_ptr(rhs).swap(*this);
        return *this;
    }
    this_type & operator=(this_type && rhs) {
        resource_ptr(std::move(rhs)).swap(*this);
        return *this;
    }
    ~resource_ptr() {
        release();
    }
    T & operator*() const {
        return *px;
    }
    T * operator->() const {
        return px;
    }
private:
    resourcr_ptr(resource * px) : px(px) {
        key = internal::resource_map::insert<T>(res);
        add_ref();
    }
    void add_ref() {
        if (px != nullptr) ++px->ref_count;
    }
    void release() {
        if (px != nullptr && --px->ref_count == 0) {
            internal::resource_map::erase<T>(key);
            delete px;
        }
    }
    void swap(this_type & rhs) {
        std::swap(key, rhs.key);
        std::swap(px, rhs.px);
    }
};
}
#endif