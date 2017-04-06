#pragma once

#ifndef __INTERGEN_GENERATED__tracker_H__
#define __INTERGEN_GENERATED__tracker_H__

//@file Interface file for tracker interface generated by intergen
//See LICENSE file for copyright and license information

#include <comm/commexception.h>
#include <comm/intergen/ifc.h>

#include <ot/glm/glm_meta.h>

class app;


namespace ot {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///OT HMD interface
class tracker
    : public intergen_interface
{
public:

    // --- interface methods ---


protected:
    // --- interface events (callbacks from host to client) ---
    // ---       overload these to handle host events       ---

    friend class ::app;

    ///Get tracker orientation and position, in the reference coord system (-z forward, +x right, +y up)
    //@param rot return rotation quaternion
    //@param pos optional, relative position
    //@return true if tracker is active
    virtual bool data( quat& rot, float3* pos ){ throw coid::exception("handler not implemented"); }

    ///Get tracker position, if available
    //@param pos return relative position
    //@return true if the tracker is active and supports positional tracking, false otherwise
    virtual bool position( float3& pos ){ throw coid::exception("handler not implemented"); }

    ///Set current position & orientation as the reference one
    virtual void set_reference() {}

    virtual void force_bind_script_events() {}

public:
    // --- host helpers to check presence of handlers in scripts ---

    virtual bool is_bound_data() { return true; }
    virtual bool is_bound_position() { return true; }
    virtual bool is_bound_set_reference() { return true; }

public:
    // --- creators ---

    //@param name plugin name
    static iref<tracker> create( const char* name ) {
        return create<tracker>(0, name);
    }

    template<class T>
    static iref<T> create( T* _subclass_, const char* name );

    // --- internal helpers ---

    virtual ~tracker() {
        if (_cleaner) _cleaner(this,0);
    }

    static const int HASHID = 4121333987;

    int intergen_hash_id() const override final { return HASHID; }

    bool iface_is_derived( int hash ) const override final {
        return hash == HASHID;
    }

    const coid::tokenhash& intergen_interface_name() const override final {
        static const coid::tokenhash _name = "ot::tracker";
        return _name;
    }

    static const coid::token& intergen_default_creator_static( EBackend bck ) {
        static const coid::token _dc("");
        static const coid::token _djs("ot::tracker@wrapper.js");
        static const coid::token _dlua("ot::tracker@wrapper.lua");
        static const coid::token _dnone;

        switch(bck) {
        case IFC_BACKEND_CXX: return _dc;
        case IFC_BACKEND_JS:  return _djs;
        case IFC_BACKEND_LUA: return _dlua;
        default: return _dnone;
        }
    }


    template<enum EBackend B>
    static void* intergen_wrapper_cache() {
        static void* _cached_wrapper=0;
        if (!_cached_wrapper) {
            const coid::token& tok = intergen_default_creator_static(B);
            _cached_wrapper = coid::interface_register::get_interface_creator(tok);
        }
        return _cached_wrapper;
    }

    void* intergen_wrapper( EBackend bck ) const override final {
        switch(bck) {
        case IFC_BACKEND_JS: return intergen_wrapper_cache<IFC_BACKEND_JS>();
        case IFC_BACKEND_LUA: return intergen_wrapper_cache<IFC_BACKEND_LUA>();
        default: return 0;
        }
    }

    EBackend intergen_backend() const override { return IFC_BACKEND_CXX; }

    const coid::token& intergen_default_creator( EBackend bck ) const override final {
        return intergen_default_creator_static(bck);
    }

protected:

    typedef void (*cleanup_fn)(tracker*, intergen_interface*);
    cleanup_fn _cleaner;

    tracker() : _cleaner(0)
    {}
};

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline iref<T> tracker::create( T* _subclass_, const char* name )
{
    typedef iref<T> (*fn_creator)(tracker*, const char*);

    static fn_creator create = 0;
    static const coid::token ifckey = "ot::tracker.create@4121333987";

    if (!create)
        create = reinterpret_cast<fn_creator>(
            coid::interface_register::get_interface_creator(ifckey));

    if (!create)
        throw coid::exception("interface creator inaccessible: ") << ifckey;

    return create(_subclass_, name);
}

#pragma warning(push)
#pragma warning(disable : 4191)

#pragma warning(pop)

} //namespace

#endif //__INTERGEN_GENERATED__tracker_H__
