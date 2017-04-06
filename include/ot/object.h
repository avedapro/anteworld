#pragma once

#ifndef __INTERGEN_GENERATED__object_H__
#define __INTERGEN_GENERATED__object_H__

//@file Interface file for object interface generated by intergen
//See LICENSE file for copyright and license information

#include <comm/commexception.h>
#include <comm/intergen/ifc.h>

#include <ot/object_cfg.h>
#include <ot/geomob.h>
#include <ot/glm/glm_types.h>
#include <ot/glm/glm_meta.h>

class object;


namespace ot {

////////////////////////////////////////////////////////////////////////////////
class object
    : public intergen_interface
{
public:

    // --- interface methods ---

    //@return type of the underlying object
    virtual ot::EObjectType type() const = 0;

    //@return unique object id
    virtual uint id() const = 0;

    
    virtual void* get_custom_data() const = 0;

    virtual void set_custom_data( void* p ) = 0;

    virtual uint get_editor_id() const = 0;

    virtual void set_editor_id( uint id ) = 0;

    virtual void* get_pkg_geomob() const = 0;

    //@return object path (package url)
    virtual const coid::charstr& get_objurl() const = 0;

    
    virtual bool get_objdef_info( ifc_out ot::pkginfo::objdef& info ) const = 0;

    //@return ECEF world position
    virtual const double3& get_pos() const = 0;

    ///Set world position
    //@param commit if false, do not update internal info yet - used for mouse drag
    virtual void set_pos( const double3& pos, bool commit = true ) = 0;

    //@return object rotation from the reference frame (-z forward, +y up)
    virtual const quat& get_rot() const = 0;

    ///Set object rotation from the reference frame (-z forward, +y up)
    virtual void set_rot( const quat& rot ) = 0;

    ///Set position and rotation
    virtual void set_pos_rot( const double3& pos, const quat& rot ) = 0;

    ///Get full positional data (with velocities)
    //@return 0 if object not ready (no data returned), >0 if ready and active, <0 if sleeping
    virtual int get_positional_data( ot::dynamic_pos& data ) const = 0;

    ///Set full positional data (with velocities)
    //@return 0 if object not ready and the position could not be set, else ok
    virtual int set_positional_data( const ot::dynamic_pos& data ) = 0;

    ///Set FPS camera model-space offset and initial rotation
    //@param pos offset position, relative to the object or bone
    //@param rot rotation from default camera orientation (model -z forward, +y up)
    //@param head_sim true if head movement should be simulated
    //@param cam_enabled true if camera rotation controls are enabled
    //@param joint_id bone id to attach to
    virtual void set_fps_camera( const float3& pos, const quat& rot, bool head_sim = true, bool cam_enabled = true, uint joint_id = UMAX32 ) = 0;

    //@return FPS camera model-space offset
    virtual float3 get_fps_camera_pos() const = 0;

    ///Get heading/pitch/roll angles of the object in radians
    virtual float3 heading_pitch_roll() const = 0;

    //@param id 0 the main body
    virtual iref<ot::geomob> get_geomob( int id ) = 0;

    ///Enter the vehicle with preferred camera mode
    //@param camode camera mode to enter
    //@param bindio controls binding mode
    //@return current camera mode
    virtual ot::ECameraMode enter( ot::ECameraMode camode = ot::CamPrevious, ot::EControlsBinding bindio = ot::BindControls ) = 0;

    ///Return camera control to UFO controller
    virtual void exit() = 0;

    //@return current camera mode or seat (negative values), or ot::CamFree if camera isn't bound to this object
    virtual ot::ECameraMode get_camera_mode() const = 0;

    ///Fetch input controls data captured when vehicle was entered with ot::BindCapture
    //@param buf captured input controls data
    //@note performs a buffer swap with internal controls buffer, keep using the same buffer to avoid unnecessary allocations
    virtual void fetch_controls( ifc_out coid::dynarray<int32>& buf ) = 0;

    ///Apply input controls data
    //@param cmd input command array pointer returned from fetch_controls
    //@param ncmds number of commands in the array
    virtual void apply_controls( const int32* cmd, uint ncmds ) = 0;

    ///Pause/unpause simulation
    virtual void pause( bool p ) = 0;

    ///Remove from the scene
    virtual void remove_from_scene() = 0;

    /// show/hide whole geom object
    virtual void set_visible( bool visible ) = 0;

    //@return true if the object is visible
    virtual bool is_visible() const = 0;

    //@return true if the geom is fully loaded
    virtual bool is_ready() const = 0;

    //@return true if the object is persistent in the world
    virtual bool is_persistent() const = 0;

    //@return true if script loading failed and object can't get into the ready state
    virtual bool is_script_error() const = 0;

    ///Update object in cache, change to permanent if necessary (only effective on static objects)
    virtual void commit() = 0;

    ///Set collision group and mask
    virtual void set_collision_group( uint group, uint mask ) = 0;

    ///Get collision group and mask
    //@param mask optional mask value
    //@return collision group id
    virtual uint get_collision_group( ifc_out uint* mask ) const = 0;

    ///Apply extra force
    //@param mpos model-space postion to act on
    //@param force model or world-space force vector
    //@param worldspace true for world-space, false for model-space force vector
    virtual void extra_force( const float3& mpos, const float3& force, bool worldspace = false ) = 0;

    ///Apply extra force impulse (force * dt)
    //@param mpos model-space postion to act on
    //@param impulse model or world-space force impulse vector
    //@param worldspace true for world-space, false for model-space force vector
    virtual void extra_impulse( const float3& mpos, const float3& impulse, bool worldspace = false ) = 0;

    //@return current offset from model pivot to center of mass
    virtual float3 com_offset() const = 0;

    //@return the underlying physics rigid body object, if any (cast to btRigidBody*)
    virtual void* rigid_body() const = 0;

    // --- creators ---


    // --- internal helpers ---

    static const int HASHID = 753485362;

    int intergen_hash_id() const override { return HASHID; }

    bool iface_is_derived( int hash ) const override {
        return hash == HASHID;
    }

    const coid::tokenhash& intergen_interface_name() const override {
        static const coid::tokenhash _name = "ot::object";
        return _name;
    }

    static const coid::token& intergen_default_creator_static( EBackend bck ) {
        static const coid::token _dc("");
        static const coid::token _djs("ot::object@wrapper.js");
        static const coid::token _dlua("ot::object@wrapper.lua");
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

    void* intergen_wrapper( EBackend bck ) const override {
        switch(bck) {
        case IFC_BACKEND_JS: return intergen_wrapper_cache<IFC_BACKEND_JS>();
        case IFC_BACKEND_LUA: return intergen_wrapper_cache<IFC_BACKEND_LUA>();
        default: return 0;
        }
    }

    EBackend intergen_backend() const override { return IFC_BACKEND_CXX; }

    const coid::token& intergen_default_creator( EBackend bck ) const override {
        return intergen_default_creator_static(bck);
    }

protected:

    object()
    {}
};

} //namespace

#endif //__INTERGEN_GENERATED__object_H__
