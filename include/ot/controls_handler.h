#pragma once

#ifndef _INTERGEN_GENERATED__controls_handler_H_
#define _INTERGEN_GENERATED__controls_handler_H_

//@file Interface file for controls_handler interface generated by intergen
//See LICENSE file for copyright and license information

//host class: ::controls_handler

#include <comm/commexception.h>
#include <comm/intergen/ifc.h>

#include <ot/action_cfg.h>
#include <ot/glm/glm_meta.h>

namespace ot {
typedef coid::function<void(int flags, uint code, uint channel, int handler_id)> fn_event_handler;
typedef coid::function<void(float val, uint code, uint channel, int handler_id)> fn_axis_handler;
}

class controls_handler;


namespace ot {

////////////////////////////////////////////////////////////////////////////////
class controls_handler
    : public intergen_interface
{
public:

    // --- interface methods ---

    ///Register input action sending events on button press (value > 0)
    //@param name hierarchic action name
    //@param handler optional handler for changed value
    //@param handler_id optinal extra data for the handler
    //@param channels number of extra channels that are handled (multiple engines etc)
    //@param group activation group where the action is assigned (can be enabled/disabled together)
    //@return slot id or -1 on fail
    int register_event( const coid::token& name, const ot::fn_event_handler& handler, int handler_id, uint channels, uint group );

    ///Register input action sending events on value change (full state button and axis)
    //@param name hierarchic action name
    //@param slot custom id to pass back
    //@param group activation group where the action is assigned (can be enabled/disabled together)
    //@param ramp value limiter parameters
    //@param handler optional handler for changed value
    //@param handler_id optinal extra data for the handler
    //@return slot id or -1 on fail
    //@note value range -1..1
    int register_axis( const coid::token& name, const ot::fn_axis_handler& handler, int handler_id, float defval, const ot::ramp_params& ramp, uint group );

    //@return action slot or -1
    int find_action( const coid::token& name ) const;

    ///Activate event groups
    void activate();

    ///De/activate given action group
    void activate_group( uint group, bool activate );

    ///Discard action bindings from given group
    void clear_group( uint group );

    ///Clear all groups and their action bindings
    void clear_all_groups();

    ///Inject registered action
    //@param slot action slot returned from register_axis or register_event
    //@param value target action value
    void inject_axis( uint slot, float value, uint channel = 0 );

    ///Inject registered event
    //@param slot action slot returned from register_axis or register_event
    //@param value optional event value
    void inject_event( uint slot, int16 value, uint channel = 0 );

    ///Programmatically invoke axis value toggle
    float toggle_axis( uint slot, uint channel = 0 );

    //@return true if given registered slot is an event
    bool is_event( uint slot ) const;

    ///Invoke event processing
    //@param dt elapsed frame time
    //@param ext_coef 0..1 modulator for ramp_params vel and center velocity
    void update( float dt, const float2& ext_coef = float2(1) );

    // --- creators ---

    static iref<controls_handler> get() {
        return get<controls_handler>(0);
    }

    template<class T>
    static iref<T> get( T* _subclass_ );

    // --- internal helpers ---

    ///Interface revision hash
    static const int HASHID = 1577691947u;

    ///Interface name (full ns::class string)
    static const coid::tokenhash& IFCNAME() {
        static const coid::tokenhash _name = "ot::controls_handler"_T;
        return _name;
    }

    int intergen_hash_id() const override final { return HASHID; }

    bool iface_is_derived( int hash ) const override final {
        return hash == HASHID;
    }

    const coid::tokenhash& intergen_interface_name() const override final {
        return IFCNAME();
    }

    static const coid::token& intergen_default_creator_static( backend bck ) {
        static constexpr coid::token _dc("ot::controls_handler.get@1577691947"_T);
        static constexpr coid::token _djs("ot::controls_handler@wrapper.js"_T);
        static constexpr coid::token _djsc("ot::controls_handler@wrapper.jsc"_T);
        static constexpr coid::token _dlua("ot::controls_handler@wrapper.lua"_T);
        static constexpr coid::token _dnone;

        switch(bck) {
        case backend::cxx: return _dc;
        case backend::js:  return _djs;
        case backend::jsc: return _djsc;
        case backend::lua: return _dlua;
        default: return _dnone;
        }
    }

    template<enum class backend B>
    static void* intergen_wrapper_cache() {
        static void* _cached_wrapper=0;
        if (!_cached_wrapper) {
            const coid::token& tok = intergen_default_creator_static(B);
            _cached_wrapper = coid::interface_register::get_interface_creator(tok);
        }
        return _cached_wrapper;
    }

    void* intergen_wrapper( backend bck ) const override final {
        switch(bck) {
        case backend::js:  return intergen_wrapper_cache<backend::js>();
        case backend::jsc: return intergen_wrapper_cache<backend::jsc>();
        case backend::lua: return intergen_wrapper_cache<backend::lua>();
        default: return 0;
        }
    }

    backend intergen_backend() const override { return backend::cxx; }

    const coid::token& intergen_default_creator( backend bck ) const override final {
        return intergen_default_creator_static(bck);
    }

    ///Client registrator
    template<class C>
    static int register_client()
    {
        static_assert(std::is_base_of<controls_handler, C>::value, "not a base class");

        typedef intergen_interface* (*fn_client)();
        fn_client cc = []() -> intergen_interface* { return new C; };

        coid::token type = typeid(C).name();
        type.consume("class ");
        type.consume("struct ");

        coid::charstr tmp = "ot::controls_handler"_T;
        tmp << "@client-1577691947"_T << '.' << type;

        coid::interface_register::register_interface_creator(tmp, cc);
        return 0;
    }

protected:

    bool set_host(policy_intrusive_base*, intergen_interface*, iref<controls_handler>* pout);
};

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline iref<T> controls_handler::get( T* _subclass_ )
{
    typedef iref<T> (*fn_creator)(controls_handler*);

    static fn_creator create = 0;
    static constexpr coid::token ifckey = "ot::controls_handler.get@1577691947"_T;

    if (!create)
        create = reinterpret_cast<fn_creator>(
            coid::interface_register::get_interface_creator(ifckey));

    if (!create) {
        log_mismatch("get"_T, "ot::controls_handler.get"_T, "@1577691947"_T);
        return 0;
    }

    return create(_subclass_);
}

#pragma warning(push)
#pragma warning(disable : 4191)

inline int controls_handler::register_event( const coid::token& name, const ot::fn_event_handler& handler, int handler_id, uint channels, uint group )
{ return VT_CALL(int,(const coid::token&,const ot::fn_event_handler&,int,uint,uint),0)(name,handler,handler_id,channels,group); }

inline int controls_handler::register_axis( const coid::token& name, const ot::fn_axis_handler& handler, int handler_id, float defval, const ot::ramp_params& ramp, uint group )
{ return VT_CALL(int,(const coid::token&,const ot::fn_axis_handler&,int,float,const ot::ramp_params&,uint),1)(name,handler,handler_id,defval,ramp,group); }

inline int controls_handler::find_action( const coid::token& name ) const
{ return VT_CALL(int,(const coid::token&) const,2)(name); }

inline void controls_handler::activate()
{ return VT_CALL(void,(),3)(); }

inline void controls_handler::activate_group( uint group, bool activate )
{ return VT_CALL(void,(uint,bool),4)(group,activate); }

inline void controls_handler::clear_group( uint group )
{ return VT_CALL(void,(uint),5)(group); }

inline void controls_handler::clear_all_groups()
{ return VT_CALL(void,(),6)(); }

inline void controls_handler::inject_axis( uint slot, float value, uint channel )
{ return VT_CALL(void,(uint,float,uint),7)(slot,value,channel); }

inline void controls_handler::inject_event( uint slot, int16 value, uint channel )
{ return VT_CALL(void,(uint,int16,uint),8)(slot,value,channel); }

inline float controls_handler::toggle_axis( uint slot, uint channel )
{ return VT_CALL(float,(uint,uint),9)(slot,channel); }

inline bool controls_handler::is_event( uint slot ) const
{ return VT_CALL(bool,(uint) const,10)(slot); }

inline void controls_handler::update( float dt, const float2& ext_coef )
{ return VT_CALL(void,(float,const float2&),11)(dt,ext_coef); }

#pragma warning(pop)

} //namespace

#endif //_INTERGEN_GENERATED__controls_handler_H_
