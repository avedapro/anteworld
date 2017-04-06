#pragma once

#ifndef __INTERGEN_GENERATED__aircraft_physics_H__
#define __INTERGEN_GENERATED__aircraft_physics_H__

//@file Interface file for aircraft_physics interface generated by intergen
//See LICENSE file for copyright and license information

#include <comm/commexception.h>
#include <comm/intergen/ifc.h>

#include <ot/object.h>
#include <ot/geomob.h>
#include <ot/jsb.h>
#include <ot/sndgrp.h>
#include <ot/vehicle_cfg.h>
#include <ot/explosion_params.h>

class jsbsim_plane;


namespace ot {

////////////////////////////////////////////////////////////////////////////////

///Interface for aircraft with JSBSim and geomob access methods
class aircraft_physics
    : public intergen_interface
{
public:

    // --- interface methods ---

    ///Titan hack
    //@return custom data value
    uint64 get_custom_data_value() const;

    //@param id 0 the main body
    iref<ot::geomob> get_geomob( int id );

    //@return ot::jsb interface to JSBSim instance
    iref<ot::jsb> jsb();

    //@return of::snd_group interface
    iref<ot::sndgrp> sound();

    //@return fb interface for IR/NVG settings
    
    ///Register event action handler
    //@param name hierarchic action name, file/group/action
    //@param group activation group where the action is assigned (can be enabled/disabled together)
    //@param channels number of extra channels that the handler supports
    //@return slot id or -1 on fail
    int register_event__( const coid::token& name, uint group = 0, uint channels = 0 );

    ///Register axis action handler
    //@param name hierarchic action name, file/group/action
    //@param ramp value limiter parameters (ignored for buttons)
    //@param defval initial value for the axis
    //@param group activation group where the action is assigned (can be enabled/disabled together)
    //@return slot id or -1 on fail
    int register_axis__( const coid::token& name, const ot::ramp_params& ramp, float defval = 0, uint group = 0 );

    ///Activate or deactivate given action group
    //@params group group id
    //@param activate activate/deactivate the group
    void action_group( uint group, bool activate );

    ///Clear existing action groups
    void clear_action_groups();

    ///Define circular spotlight source
    //@param offset model-space offset relative to the bone or model pivot
    //@param dir light direction
    //@param lp light parameters
    //@param joint joint name to attach the light to
    //@return light emitter id
    //@note can be called only from within init_chassis
    uint add_spot_light( const float3& offset, const float3& dir, const ot::light_params& lp, const coid::token& joint = coid::token() );

    ///Define point light source
    //@param offset model-space offset relative to the bone or model pivot
    //@param lp light parameters
    //@param joint joint name to attach the light to
    //@return light emitter id
    //@note can be called only from within init_chassis
    uint add_point_light( const float3& offset, const ot::light_params& lp, const coid::token& joint = coid::token() );

    ///Turn light on/off
    void light( uint id, bool on );

    ///Turn light on/off
    void light_mask( uint mask, bool on, uint offset = 0 );

    ///Toggle light
    void light_toggle( uint id );

    ///Toggle lights by bit mask
    void light_toggle_mask( uint mask, uint offset = 0 );

    ///Set light color/intensity
    void light_color( uint id, const float4& color, float range = 0 );

    ///All lights off
    void lights_off( bool instant = false );

    ///Return current solar time and cosine of sun-zenith angle
    //@param time [out] solar time at vehicle location, in miliseconds
    //@param sun_coef sun position relative to horizon: 0 sun at horizon, 1 sun at zenith, -1 sun at anti-zenith
    void solar_time( ifc_out double& time, ifc_out float& sun_coef ) const;

    ///Set model space position for FPS camera
    void set_fps_camera_pos( const float3& pos, uint joint_id = UMAX32 );

    ///Set model space rotation frame
    //@param rot model space rotation
    //@param mouse rotation mode: 0 freeze, 1 reset&disable, 2 enable, 3 reset & enable
    void set_fps_camera_rot( const quat& rot, ot::ERotationMode mouse_rotation );

    ///Set temporary camera FOV in FPS mode
    //@param hfov horizontal fov in degrees, 0 to reset to the default one
    //@param vfov optional vertical fov in degrees, otherwise computed from aspect ratio
    void set_fps_camera_fov( float hfov, float vfov = 0 );

    ///Set model space orientation for FPS camera
    //@param yaw yaw angle in radians, positive values to the right
    //@param pitch pitch angle in radians, positive up
    //@param roll roll angle in radians, positive clockwise
    //@param mouse rotation mode: 0 freeze, 1 reset&disable, 2 enable, 3 reset & enable
    void set_fps_camera_ypr( float yaw, float pitch, float roll, ot::ERotationMode mouse_rotation );

    
    //@param target ECEF coordinates of the point
    //@param level_horizon keep horizon level (roll the camera)
    //@return true if tracking was enabled, false if center wasn't on terrain or the current camera mode is not FPS
    bool set_fps_camera_tracking_point( const double3& target, bool level_horizon );

    
    //@param level_horizon keep horizon level (roll the camera)
    //@return true if tracking was enabled, false if center wasn't on terrain or the current camera mode is not FPS
    bool set_fps_camera_tracking( bool level_horizon );

    ///Disable tracking
    bool set_fps_camera_tracking_off();

    ///Set FPS camera model-space offset and initial rotation
    //@param pos offset position, relative to the object or bone
    //@param rot rotation from default camera orientation (model -z forward, +y up)
    //@param head_sim true if head movement should be simulated
    //@param cam_enabled true if camera rotation controls are enabled
    //@param joint_id bone id to attach to
    void set_fps_camera( const float3& pos, const quat& rot, bool head_sim = true, bool cam_enabled = true, uint joint_id = UMAX32 );

    //@return current FPS camera position
    float3 get_fps_camera_pos() const;

    //@return current FPS camera rotation in model space
    //@param base true for the base orientation frame, false for current camera orientation as altered by mouse
    quat get_fps_camera_rot( bool base = false ) const;

    //@return current yaw/pitch/roll angles of the camera in model space in radians
    //@param base true for the base orientation frame, false for current camera orientation as altered by mouse
    float3 get_fps_camera_ypr( bool base = false ) const;

    ///Get heading/pitch/roll angles of the object in radians
    float3 heading_pitch_roll() const;

    ///Set initial pitch/roll angles
    //@param pitch pitch angle in degrees
    //@param roll roll angle in degrees
    void set_pitch_roll( float pitch, float roll );

    /// reset simulation
    /// user is responsible to initialize all params through jsbsim properties
    /// _jsbic->InitializeIC();
    /// _jsbic->SetPsiRadIC(angles(3));
    /// _jsbic->SetThetaRadIC(angles(2));
    /// _jsbic->SetPhiRadIC(angles(1));
    /// _jsbic->SetVcalibratedKtsIC(speed_kts);
    /// _jsbic->SetLatitudeRadIC(glm::radians(lat_lon.x));
    /// _jsbic->SetLongitudeRadIC(glm::radians(lat_lon.y));
    /// _jsbic->SetAltitudeASLFtIC(altitude * M2F());
    /// _jsbic->SetVcalibratedKtsIC(speed_kts);
    void reset_ic();

    /// initialize simulation from initial conditions
    /// _jsbexec->ResetToInitialConditions(0);
    /// _jsbexec->RunIC();
    void initialize_ic();

    bool engine_running() const;

    //@return current camera mode or seat (negative values), or ot::CamFree if camera isn't bound to this object
    ot::ECameraMode get_camera_mode() const;

    ///
    void activate_event_group( const coid::token& name );

    ///Post message to the fading log
    void fade( const coid::token& text ) const;

    ///Post log message with recognized prefixes: error,warning,info,dbg,debug,perf
    void log( const coid::token& text ) const;

    ///Obsolete
    void log_err( const coid::token& text );

    void log_dbg( const coid::token& text );

    void log_inf( const coid::token& text );

    ///Fire a colored plasma thing
    //@param pos model-space launch position
    //@param dir model-space launch direction
    //@param speed firing velocity in m/s
    //@param color plasma color
    void fire( const float3& pos, const float3& dir, float speed, float caliber, const float3& color, uint joint = pkg::InvalidBoneId );

    ///Explode ground at model position
    //@param ge explosion parameters
    void explode_ground( const ot::ground_explosion& ge );

    //@return height of model-space point above terrain or maxheight if terrain is lower
    //@param pos model-space launch position
    //@param maxheight max height to check
    //@param joint bone id to be relative to
    float elevation_above_terrain( const float3& pos, float maxheight, uint joint = pkg::InvalidBoneId ) const;

    ///Test if ray from model intersects with terrain
    //@param pos model-space position
    //@param dir model-space ray direction
    //@param maxdist max ray distance to check (keep short if possible)
    //@param joint bone id to be relative to
    //@return intersection distance or >= maxdist if no hit
    float ray_test( const float3& pos, const float3& dir, float maxdist, ifc_out float3* norm = 0, ifc_out double3* hitpoint = 0, uint joint = pkg::InvalidBoneId ) const;

    ///Test if ray from model hits an object
    //@param pos model-space position
    //@param dir model-space ray direction
    //@param maxdist max ray distance to check (keep short if possible)
    //@param exclude_self true if ray should not hit origin body
    //@param joint bone id to be relative to
    //@return object hit
    iref<ot::object> object_test( const float3& pos, const float3& dir, float maxdist, bool exclude_self, ifc_out float3* norm = 0, ifc_out double3* hitpoint = 0, uint joint = pkg::InvalidBoneId ) const;


protected:
    // --- interface events (callbacks from host to client) ---
    // ---       overload these to handle host events       ---

    friend class ::jsbsim_plane;

    ///Interface event for initialization and script reload
    //@param params parameter object with properties from objdef file
    //@return aircraft configuration object
    virtual ot::aircraft_config initialize__( const coid::charstr& params ){ throw coid::exception("handler not implemented"); }

    ///Interface event for handling aircraft state before rendering (inputs, animating joints etc)
    virtual void update_actions( float dt, const coid::range<int32>& actbuf ) {}

    ///Interface event for handling aircraft state before rendering (inputs, animating joints etc)
    virtual void update_frame( float dt ) {}

    ///Invoked on FPS camera switch event (switching between vehicle seats and cameras)
    //@param camera camera id to switch to
    //@return true if camera exists and switching was handled
    virtual bool switch_seat( int camera ) { return false; }

    virtual void ext_param( const coid::token& name, float value ) {}

    virtual void force_bind_script_events() {}

public:
    // --- host helpers to check presence of handlers in scripts ---

    virtual bool is_bound_initialize__() { return true; }
    virtual bool is_bound_update_actions() { return true; }
    virtual bool is_bound_update_frame() { return true; }
    virtual bool is_bound_switch_seat() { return true; }
    virtual bool is_bound_ext_param() { return true; }

public:
    // --- creators ---

    ///Internal constructor
    static iref<aircraft_physics> get( jsbsim_plane* p ) {
        return get<aircraft_physics>(0, p);
    }

    template<class T>
    static iref<T> get( T* _subclass_, jsbsim_plane* p );

    // --- internal helpers ---

    virtual ~aircraft_physics() {
        if (_cleaner) _cleaner(this,0);
    }

    static const int HASHID = 1783448745;

    int intergen_hash_id() const override final { return HASHID; }

    bool iface_is_derived( int hash ) const override final {
        return hash == HASHID;
    }

    const coid::tokenhash& intergen_interface_name() const override final {
        static const coid::tokenhash _name = "ot::aircraft_physics";
        return _name;
    }

    static const coid::token& intergen_default_creator_static( EBackend bck ) {
        static const coid::token _dc("");
        static const coid::token _djs("ot::aircraft_physics@wrapper.js");
        static const coid::token _dlua("ot::aircraft_physics@wrapper.lua");
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

    typedef void (*cleanup_fn)(aircraft_physics*, intergen_interface*);
    cleanup_fn _cleaner;

    aircraft_physics() : _cleaner(0)
    {}
};

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline iref<T> aircraft_physics::get( T* _subclass_, jsbsim_plane* p )
{
    typedef iref<T> (*fn_creator)(aircraft_physics*, jsbsim_plane*);

    static fn_creator create = 0;
    static const coid::token ifckey = "ot::aircraft_physics.get@1783448745";

    if (!create)
        create = reinterpret_cast<fn_creator>(
            coid::interface_register::get_interface_creator(ifckey));

    if (!create)
        throw coid::exception("interface creator inaccessible: ") << ifckey;

    return create(_subclass_, p);
}

#pragma warning(push)
#pragma warning(disable : 4191)

inline uint64 aircraft_physics::get_custom_data_value() const
{ return VT_CALL(uint64,() const,0)(); }

inline iref<ot::geomob> aircraft_physics::get_geomob( int id )
{ return VT_CALL(iref<ot::geomob>,(int),1)(id); }

inline iref<ot::jsb> aircraft_physics::jsb()
{ return VT_CALL(iref<ot::jsb>,(),2)(); }

inline iref<ot::sndgrp> aircraft_physics::sound()
{ return VT_CALL(iref<ot::sndgrp>,(),3)(); }

inline int aircraft_physics::register_event__( const coid::token& name, uint group, uint channels )
{ return VT_CALL(int,(const coid::token&,uint,uint),4)(name,group,channels); }

inline int aircraft_physics::register_axis__( const coid::token& name, const ot::ramp_params& ramp, float defval, uint group )
{ return VT_CALL(int,(const coid::token&,const ot::ramp_params&,float,uint),5)(name,ramp,defval,group); }

inline void aircraft_physics::action_group( uint group, bool activate )
{ return VT_CALL(void,(uint,bool),6)(group,activate); }

inline void aircraft_physics::clear_action_groups()
{ return VT_CALL(void,(),7)(); }

inline uint aircraft_physics::add_spot_light( const float3& offset, const float3& dir, const ot::light_params& lp, const coid::token& joint )
{ return VT_CALL(uint,(const float3&,const float3&,const ot::light_params&,const coid::token&),8)(offset,dir,lp,joint); }

inline uint aircraft_physics::add_point_light( const float3& offset, const ot::light_params& lp, const coid::token& joint )
{ return VT_CALL(uint,(const float3&,const ot::light_params&,const coid::token&),9)(offset,lp,joint); }

inline void aircraft_physics::light( uint id, bool on )
{ return VT_CALL(void,(uint,bool),10)(id,on); }

inline void aircraft_physics::light_mask( uint mask, bool on, uint offset )
{ return VT_CALL(void,(uint,bool,uint),11)(mask,on,offset); }

inline void aircraft_physics::light_toggle( uint id )
{ return VT_CALL(void,(uint),12)(id); }

inline void aircraft_physics::light_toggle_mask( uint mask, uint offset )
{ return VT_CALL(void,(uint,uint),13)(mask,offset); }

inline void aircraft_physics::light_color( uint id, const float4& color, float range )
{ return VT_CALL(void,(uint,const float4&,float),14)(id,color,range); }

inline void aircraft_physics::lights_off( bool instant )
{ return VT_CALL(void,(bool),15)(instant); }

inline void aircraft_physics::solar_time( double& time, float& sun_coef ) const
{ return VT_CALL(void,(double&,float&) const,16)(time,sun_coef); }

inline void aircraft_physics::set_fps_camera_pos( const float3& pos, uint joint_id )
{ return VT_CALL(void,(const float3&,uint),17)(pos,joint_id); }

inline void aircraft_physics::set_fps_camera_rot( const quat& rot, ot::ERotationMode mouse_rotation )
{ return VT_CALL(void,(const quat&,ot::ERotationMode),18)(rot,mouse_rotation); }

inline void aircraft_physics::set_fps_camera_fov( float hfov, float vfov )
{ return VT_CALL(void,(float,float),19)(hfov,vfov); }

inline void aircraft_physics::set_fps_camera_ypr( float yaw, float pitch, float roll, ot::ERotationMode mouse_rotation )
{ return VT_CALL(void,(float,float,float,ot::ERotationMode),20)(yaw,pitch,roll,mouse_rotation); }

inline bool aircraft_physics::set_fps_camera_tracking_point( const double3& target, bool level_horizon )
{ return VT_CALL(bool,(const double3&,bool),21)(target,level_horizon); }

inline bool aircraft_physics::set_fps_camera_tracking( bool level_horizon )
{ return VT_CALL(bool,(bool),22)(level_horizon); }

inline bool aircraft_physics::set_fps_camera_tracking_off()
{ return VT_CALL(bool,(),23)(); }

inline void aircraft_physics::set_fps_camera( const float3& pos, const quat& rot, bool head_sim, bool cam_enabled, uint joint_id )
{ return VT_CALL(void,(const float3&,const quat&,bool,bool,uint),24)(pos,rot,head_sim,cam_enabled,joint_id); }

inline float3 aircraft_physics::get_fps_camera_pos() const
{ return VT_CALL(float3,() const,25)(); }

inline quat aircraft_physics::get_fps_camera_rot( bool base ) const
{ return VT_CALL(quat,(bool) const,26)(base); }

inline float3 aircraft_physics::get_fps_camera_ypr( bool base ) const
{ return VT_CALL(float3,(bool) const,27)(base); }

inline float3 aircraft_physics::heading_pitch_roll() const
{ return VT_CALL(float3,() const,28)(); }

inline void aircraft_physics::set_pitch_roll( float pitch, float roll )
{ return VT_CALL(void,(float,float),29)(pitch,roll); }

inline void aircraft_physics::reset_ic()
{ return VT_CALL(void,(),30)(); }

inline void aircraft_physics::initialize_ic()
{ return VT_CALL(void,(),31)(); }

inline bool aircraft_physics::engine_running() const
{ return VT_CALL(bool,() const,32)(); }

inline ot::ECameraMode aircraft_physics::get_camera_mode() const
{ return VT_CALL(ot::ECameraMode,() const,33)(); }

inline void aircraft_physics::activate_event_group( const coid::token& name )
{ return VT_CALL(void,(const coid::token&),34)(name); }

inline void aircraft_physics::fade( const coid::token& text ) const
{ return VT_CALL(void,(const coid::token&) const,35)(text); }

inline void aircraft_physics::log( const coid::token& text ) const
{ return VT_CALL(void,(const coid::token&) const,36)(text); }

inline void aircraft_physics::log_err( const coid::token& text )
{ return VT_CALL(void,(const coid::token&),37)(text); }

inline void aircraft_physics::log_dbg( const coid::token& text )
{ return VT_CALL(void,(const coid::token&),38)(text); }

inline void aircraft_physics::log_inf( const coid::token& text )
{ return VT_CALL(void,(const coid::token&),39)(text); }

inline void aircraft_physics::fire( const float3& pos, const float3& dir, float speed, float caliber, const float3& color, uint joint )
{ return VT_CALL(void,(const float3&,const float3&,float,float,const float3&,uint),40)(pos,dir,speed,caliber,color,joint); }

inline void aircraft_physics::explode_ground( const ot::ground_explosion& ge )
{ return VT_CALL(void,(const ot::ground_explosion&),41)(ge); }

inline float aircraft_physics::elevation_above_terrain( const float3& pos, float maxheight, uint joint ) const
{ return VT_CALL(float,(const float3&,float,uint) const,42)(pos,maxheight,joint); }

inline float aircraft_physics::ray_test( const float3& pos, const float3& dir, float maxdist, float3* norm, double3* hitpoint, uint joint ) const
{ return VT_CALL(float,(const float3&,const float3&,float,float3*,double3*,uint) const,43)(pos,dir,maxdist,norm,hitpoint,joint); }

inline iref<ot::object> aircraft_physics::object_test( const float3& pos, const float3& dir, float maxdist, bool exclude_self, float3* norm, double3* hitpoint, uint joint ) const
{ return VT_CALL(iref<ot::object>,(const float3&,const float3&,float,bool,float3*,double3*,uint) const,44)(pos,dir,maxdist,exclude_self,norm,hitpoint,joint); }

#pragma warning(pop)

} //namespace

#endif //__INTERGEN_GENERATED__aircraft_physics_H__
