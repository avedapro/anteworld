#pragma once

#ifndef __INTERGEN_GENERATED__geomob_H__
#define __INTERGEN_GENERATED__geomob_H__

//@file Interface file for geomob interface generated by intergen
//See LICENSE file for copyright and license information

#include <comm/commexception.h>
#include <comm/intergen/ifc.h>

#include <ot/glm/glm_meta.h>
#include <ot/geom_types.h>
#include <ot/object_cfg.h>
#include <ot/animation_stack.h>
#include <ot/glm/glm_types.h>

namespace ot {
    class geomob;

    namespace pkginfo {
    struct objdef;
    }
}

namespace pkg
{
    struct lod_meshes;
    struct mesh_draw_data2;
}


namespace pkg {
    class geomob;
}

namespace ot {

////////////////////////////////////////////////////////////////////////////////
///Geometry instance interface
class geomob
    : public intergen_interface
{
public:

    // --- interface methods ---

    ///Get object's world position (ECEF)
    const double3& get_pos() const;

    ///Get object's rotation quaternion (rotation of model (+z up, +y forward) in ECEF)
    const glm::quat& get_rot() const;

    uint get_inst_id() const;

    ///Get world position of a point in model's relative offset
    double3 get_world_pos_offset( const float3& offset, uint bone = pkg::InvalidBoneId ) const;

    //@return instance scale
    const float3& get_scale() const;

    void set_scale( const float3& scale );

    ///Set object's world position (ECEF)
    void set_pos( const double3& pos );

    void move( const float3& vec );

    ///Set object's rotation quaternion (rotation of model (+z up, +y forward) in ECEF)
    void set_rot( const glm::quat& rot );

    void add_rot( const glm::quat& rot );

    void set_pos_rot( const double3& pos, const quat& rot );

    ///Remove object from the scene
    void remove_from_scene();

    ///
    uint get_children_count() const;

    uint get_child( uint idx ) const;

    const coid::charstr& get_objurl() const;

    
    bool get_objdef_info( ifc_out ot::pkginfo::objdef& info ) const;

    ushort get_lod_count() const;

    ///Get vector from the model pivot into the center of the OBB
    float3 get_obb_offset() const;

    ///Get OBB's diagonal half-vector
    float3 get_obb_hvec() const;

    
    /// return entity ID
    uint get_eid() const;

    /// set/get uint32 (used by scene editor)
    void set_custom_data( uint custom_data ) const;

    uint get_custom_data() const;

    
    //@return local joint id it's on geom only to get global ID add get_bones_base()
    uint get_joint( const coid::token& name ) const;

    uint get_mesh_id( const coid::token& name ) const;

    ///Show/hide bone hierarchy - not implemented yet
    void set_joint_visible( uint joint, bool visible, bool recursive = true );

    ///Rotate bone along an axis (incremental)
    void reset_joint( uint joint );

    ///Rotate bone along an axis (incremental)
    //@param joint 
    //@param angle rotation angle in radians
    //@param vec rotation axis vector (MUST BE normalized)
    //@param orig true if rotation should go from the bind pose, otherwise accumulate
    void rotate_joint( uint joint, float angle, const float3& vec, bool orig = false );

    ///Rotate bone along an axis (from default orientation)
    //@param joint 
    //@param angle rotation angle in radians
    //@param vec rotation axis vector (MUST BE normalized)
    void rotate_joint_orig( uint joint, float angle, const float3& vec );

    ///Move bone (incremental)
    //@param orig true if movement should go from the bind pose, otherwise accumulate
    void move_joint( uint joint, const float3& vec, bool orig = false );

    ///Move bone (from default position)
    void move_joint_orig( uint joint, const float3& vec );

    ///Mesh visibility control
    //@param name mesh name
    //@note if the last char is @ it will disable all submeshes with suffix @1-@N (submeshes appear because of multi-materials used within mesh)
    //@note if the last char * it will disable all submeshes that begin with given name
    void set_mesh_visible( coid::token name, bool show );

    ///Mesh visibility with mesh ID
    void set_mesh_visible_id( uint id, bool show );

    //@return joint position in model space
    float3 get_joint_model_pos( uint joint ) const;

    //@return joint position in model space
    double3 get_joint_ecef_pos( uint joint ) const;

    //@return joint position in model space
    float3 get_joint_ecef_rot_z( uint joint ) const;

    //@return joint position in model space (compatibility)
    float3 get_joint_local_pos( uint joint ) const;

    ///
    
    ///Deselect object previously selected via object_factory
    void deselect();

    
    //@return number of bones
    uint get_num_bones() const;

    //@return constant pointer to bones meta information (parent IDs)
    const pkg::bone_meta* get_bone_meta_ptr() const;

    //@return constant pointer to bones description (bone name, etc)
    const pkg::bone_desc* get_bone_desc_ptr() const;

    //@return constant pointer to inverse bind pose transformations
    const pkg::bone_data* get_bone_ibp_ptr() const;

    //@return constant pointer to bones bind pose local transformations
    const pkg::bone_data* get_bone_bp_local_ptr() const;

    /// return pointer to bones local transformations,
    /// these transformations are later recomputed to world space transformations and used in shader
    ///
    /// Updates to this array have no effect if raw_bones_update is enabled!
    ///
    /// BE VERY CAREFUL HOW MUCH DATA YOU ARE WRITING TO THIS MEMORY !!!
    ///
    pkg::bone_data* get_bone_local_ptr() const;

    /// loads animation and return animation handle
    iref<ot::animation> load_animation( const coid::token& filename, const coid::token& root_bone, uint frame_offset );

    /// if set to AnimExplicit (0x01) then user has to call
    /// animate() to animate geom's bones
    void set_animate_mode( pkg::EGeomAnimateMode mode );

    ///Explicitly animate geom's bones
    float3 animate();

    ///Set user skeleton modification weight (default == 0.0f)
    void set_skeleton_weight( float weight );

    //@return animation stack for geom object
    iref<ot::animation_stack> get_animation_stack();

    
    ///Show/hide whole geom object
    void set_visible( bool visible );

    ///Make object visible or invisible on the slave
    //@note all objects are visible by default 
    
    //@return true if the geom's visible flag is true
    bool is_visible() const;

    //@return true if the geom is fully loaded
    bool is_ready() const;

    ///Get current bone model space transformation from previous frame
    bool get_bone_model_dq( uint joint, ifc_out quat& rot, ifc_out quat& dual ) const;

    bool get_bone_model_tm( uint joint, ifc_out float3& pos, ifc_out quat& rot ) const;

    ///Return bone model space transformation from previous frame, with extra offset
    bool get_bone_model_tm_offset( uint joint, const float3& offset, ifc_out float3& pos, ifc_out quat& rot ) const;

    ///Get bone bind pose model space transformation (iverse of IBP)
    bool get_bone_model_bp_dq( uint joint, ifc_out quat& rot, ifc_out quat& dual ) const;

    bool get_bone_model_bp_tm( uint joint, ifc_out float3& pos, ifc_out quat& rot ) const;

    //@returns bone skin transformation previous frame
    const pkg::bone_gpu_data* get_bone_skin_dq( uint bone_id ) const;

    ///Get current bone local space transformation from parent
    bool get_bone_local_dq( uint joint, ifc_out quat& rot, ifc_out quat& dual ) const;

    bool get_bone_local_tm( uint joint, ifc_out float3& pos, ifc_out quat& rot ) const;

    const pkg::mesh_desc* get_meshes_ptr() const;

    const pkg::mesh_data* get_meshes_data_ptr() const;

    const pkg::lod_meshes* get_lods_ptr() const;

    const pkg::lod_meshes* get_collision_meshes_ptr() const;

    uchar* get_mesh_flags_ptr() const;

    const pkg::mesh_obb_data* get_meshes_obbs() const;

    coid::dynarray<pkg::mesh_desc> get_meshes() const;

    coid::dynarray<pkg::lod_meshes> get_lods() const;

    pkg::lod_meshes get_collision_meshes() const;

    coid::dynarray<uchar> get_mesh_flags() const;

    ///
    void attach_to( const iref<ot::geomob>& geom, uint joint_id = pkg::InvalidBoneId, bool update_tm = true );

    ///
    uint attach_geom( const coid::token& url, const coid::token& joint, const double3& pos, const quat& rot );

    ///
    void get_world_transform( ifc_out double3& pos, ifc_out quat& rot ) const;

    ///
    void dump_geom_info();

    ///
    uint get_mtl_count() const;

    ///
    uint get_mtl_id( uint id ) const;

    const pkg::lod_meshes* get_lod_meshes( uint lod ) const;

    const pkg::mesh_draw_data2* get_mesh_draw_data( uint mesh ) const;

    ///
    const int2* get_positions( const pkg::mesh_draw_data2* mdd ) const;

    const ushort* get_indices( const pkg::mesh_draw_data2* mdd ) const;

    const uchar4* get_skin_indices( const pkg::mesh_draw_data2* mdd ) const;

    const uchar4* get_skin_weights( const pkg::mesh_draw_data2* mdd ) const;

    ///
    void get_mesh_tm( uint mesh_id, quat& rot, quat& dual );

    ///
    bool has_hit_mask_component() const;

    /// create geom hitmask component and allocate hit mask texture 256x256
    /// prepare and cache acceleration sturctures
    /// expect second UV coordinates in model
    /// second UV space have to be one for all object meshes
    /// mesh UVs cannot overlap otherwise hit mask will not work properly
    /// unwrapped meshes 
    /// https://docs.google.com/document/d/1tWURh8NENZARN9WVn1rFjkQu4j4nQMP1YngLbA1WPVY/pub
    uint create_hit_mask_component();

    /// render blood into hit mask
    void ray_vs_hit_mask( const double3& ecef_pos, const float3& ecef_dir, uint hit_mesh_id );

    // --- creators ---

    /// create geom instance
    ///@url geom URL like "outerra/m4/m4"
    ///@parent_id parent entity ID, can be get with geom::get_eid() or use -1
    ///@parent_joint_id parent's geom joint ID or 0xffff
    static iref<geomob> create( const coid::token& url, coid::uint parent_id, coid::uint parent_joint_id ) {
        return create<geomob>(0, url, parent_id, parent_joint_id);
    }

    template<class T>
    static iref<T> create( T* _subclass_, const coid::token& url, coid::uint parent_id, coid::uint parent_joint_id );
    /// create geom instance and return new geom interface
    ///@url geom URL like "outerra/m4/m4"
    ///@parent_id parent entity ID, can be get with geom::get_eid() or use -1
    ///@parent_joint_id parent's geom joint ID or 0xffff
    ///@pos position
    ///@rot rotation
    static iref<geomob> create2( const coid::token& url, coid::uint parent_id, coid::uint parent_joint_id, double3 pos, quat rot ) {
        return create2<geomob>(0, url, parent_id, parent_joint_id, pos, rot);
    }

    template<class T>
    static iref<T> create2( T* _subclass_, const coid::token& url, coid::uint parent_id, coid::uint parent_joint_id, double3 pos, quat rot );
    /// create geom instance and return new geom interface
    ///@url geom URL like "outerra/m4/m4"
    ///@parent_id parent entity ID, can be get with geom::get_eid() or use -1
    ///@parent_joint parent's joint name or null
    ///@pos position
    ///@rot rotation
    static iref<geomob> create3( const coid::token& url, coid::uint parent_id, const coid::token& parent_joint, double3 pos, quat rot ) {
        return create3<geomob>(0, url, parent_id, parent_joint, pos, rot);
    }

    template<class T>
    static iref<T> create3( T* _subclass_, const coid::token& url, coid::uint parent_id, const coid::token& parent_joint, double3 pos, quat rot );
    /// return geomob component interface from entity
    static iref<geomob> from_entity_id( coid::uint entity_id ) {
        return from_entity_id<geomob>(0, entity_id);
    }

    template<class T>
    static iref<T> from_entity_id( T* _subclass_, coid::uint entity_id );
    ///Interface creator for internal use
    static iref<geomob> _get_instance_interface( void* so ) {
        return _get_instance_interface<geomob>(0, so);
    }

    template<class T>
    static iref<T> _get_instance_interface( T* _subclass_, void* so );

    // --- internal helpers ---

    static const int HASHID = 1654959773;

    int intergen_hash_id() const override final { return HASHID; }

    bool iface_is_derived( int hash ) const override final {
        return hash == HASHID;
    }

    const coid::tokenhash& intergen_interface_name() const override final {
        static const coid::tokenhash _name = "ot::geomob";
        return _name;
    }

    static const coid::token& intergen_default_creator_static( EBackend bck ) {
        static const coid::token _dc("");
        static const coid::token _djs("ot::geomob@wrapper.js");
        static const coid::token _dlua("ot::geomob@wrapper.lua");
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

    geomob()
    {}
};

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline iref<T> geomob::create( T* _subclass_, const coid::token& url, coid::uint parent_id, coid::uint parent_joint_id )
{
    typedef iref<T> (*fn_creator)(geomob*, const coid::token&, coid::uint, coid::uint);

    static fn_creator create = 0;
    static const coid::token ifckey = "ot::geomob.create@1654959773";

    if (!create)
        create = reinterpret_cast<fn_creator>(
            coid::interface_register::get_interface_creator(ifckey));

    if (!create)
        throw coid::exception("interface creator inaccessible: ") << ifckey;

    return create(_subclass_, url, parent_id, parent_joint_id);
}
////////////////////////////////////////////////////////////////////////////////
template<class T>
inline iref<T> geomob::create2( T* _subclass_, const coid::token& url, coid::uint parent_id, coid::uint parent_joint_id, double3 pos, quat rot )
{
    typedef iref<T> (*fn_creator)(geomob*, const coid::token&, coid::uint, coid::uint, double3, quat);

    static fn_creator create = 0;
    static const coid::token ifckey = "ot::geomob.create2@1654959773";

    if (!create)
        create = reinterpret_cast<fn_creator>(
            coid::interface_register::get_interface_creator(ifckey));

    if (!create)
        throw coid::exception("interface creator inaccessible: ") << ifckey;

    return create(_subclass_, url, parent_id, parent_joint_id, pos, rot);
}
////////////////////////////////////////////////////////////////////////////////
template<class T>
inline iref<T> geomob::create3( T* _subclass_, const coid::token& url, coid::uint parent_id, const coid::token& parent_joint, double3 pos, quat rot )
{
    typedef iref<T> (*fn_creator)(geomob*, const coid::token&, coid::uint, const coid::token&, double3, quat);

    static fn_creator create = 0;
    static const coid::token ifckey = "ot::geomob.create3@1654959773";

    if (!create)
        create = reinterpret_cast<fn_creator>(
            coid::interface_register::get_interface_creator(ifckey));

    if (!create)
        throw coid::exception("interface creator inaccessible: ") << ifckey;

    return create(_subclass_, url, parent_id, parent_joint, pos, rot);
}
////////////////////////////////////////////////////////////////////////////////
template<class T>
inline iref<T> geomob::from_entity_id( T* _subclass_, coid::uint entity_id )
{
    typedef iref<T> (*fn_creator)(geomob*, coid::uint);

    static fn_creator create = 0;
    static const coid::token ifckey = "ot::geomob.from_entity_id@1654959773";

    if (!create)
        create = reinterpret_cast<fn_creator>(
            coid::interface_register::get_interface_creator(ifckey));

    if (!create)
        throw coid::exception("interface creator inaccessible: ") << ifckey;

    return create(_subclass_, entity_id);
}
////////////////////////////////////////////////////////////////////////////////
template<class T>
inline iref<T> geomob::_get_instance_interface( T* _subclass_, void* so )
{
    typedef iref<T> (*fn_creator)(geomob*, void*);

    static fn_creator create = 0;
    static const coid::token ifckey = "ot::geomob._get_instance_interface@1654959773";

    if (!create)
        create = reinterpret_cast<fn_creator>(
            coid::interface_register::get_interface_creator(ifckey));

    if (!create)
        throw coid::exception("interface creator inaccessible: ") << ifckey;

    return create(_subclass_, so);
}

#pragma warning(push)
#pragma warning(disable : 4191)

inline const double3& geomob::get_pos() const
{ return VT_CALL(const double3&,() const,0)(); }

inline const glm::quat& geomob::get_rot() const
{ return VT_CALL(const glm::quat&,() const,1)(); }

inline uint geomob::get_inst_id() const
{ return VT_CALL(uint,() const,2)(); }

inline double3 geomob::get_world_pos_offset( const float3& offset, uint bone ) const
{ return VT_CALL(double3,(const float3&,uint) const,3)(offset,bone); }

inline const float3& geomob::get_scale() const
{ return VT_CALL(const float3&,() const,4)(); }

inline void geomob::set_scale( const float3& scale )
{ return VT_CALL(void,(const float3&),5)(scale); }

inline void geomob::set_pos( const double3& pos )
{ return VT_CALL(void,(const double3&),6)(pos); }

inline void geomob::move( const float3& vec )
{ return VT_CALL(void,(const float3&),7)(vec); }

inline void geomob::set_rot( const glm::quat& rot )
{ return VT_CALL(void,(const glm::quat&),8)(rot); }

inline void geomob::add_rot( const glm::quat& rot )
{ return VT_CALL(void,(const glm::quat&),9)(rot); }

inline void geomob::set_pos_rot( const double3& pos, const quat& rot )
{ return VT_CALL(void,(const double3&,const quat&),10)(pos,rot); }

inline void geomob::remove_from_scene()
{ return VT_CALL(void,(),11)(); }

inline uint geomob::get_children_count() const
{ return VT_CALL(uint,() const,12)(); }

inline uint geomob::get_child( uint idx ) const
{ return VT_CALL(uint,(uint) const,13)(idx); }

inline const coid::charstr& geomob::get_objurl() const
{ return VT_CALL(const coid::charstr&,() const,14)(); }

inline bool geomob::get_objdef_info( ot::pkginfo::objdef& info ) const
{ return VT_CALL(bool,(ot::pkginfo::objdef&) const,15)(info); }

inline ushort geomob::get_lod_count() const
{ return VT_CALL(ushort,() const,16)(); }

inline float3 geomob::get_obb_offset() const
{ return VT_CALL(float3,() const,17)(); }

inline float3 geomob::get_obb_hvec() const
{ return VT_CALL(float3,() const,18)(); }

inline uint geomob::get_eid() const
{ return VT_CALL(uint,() const,19)(); }

inline void geomob::set_custom_data( uint custom_data ) const
{ return VT_CALL(void,(uint) const,20)(custom_data); }

inline uint geomob::get_custom_data() const
{ return VT_CALL(uint,() const,21)(); }

inline uint geomob::get_joint( const coid::token& name ) const
{ return VT_CALL(uint,(const coid::token&) const,22)(name); }

inline uint geomob::get_mesh_id( const coid::token& name ) const
{ return VT_CALL(uint,(const coid::token&) const,23)(name); }

inline void geomob::set_joint_visible( uint joint, bool visible, bool recursive )
{ return VT_CALL(void,(uint,bool,bool),24)(joint,visible,recursive); }

inline void geomob::reset_joint( uint joint )
{ return VT_CALL(void,(uint),25)(joint); }

inline void geomob::rotate_joint( uint joint, float angle, const float3& vec, bool orig )
{ return VT_CALL(void,(uint,float,const float3&,bool),26)(joint,angle,vec,orig); }

inline void geomob::rotate_joint_orig( uint joint, float angle, const float3& vec )
{ return VT_CALL(void,(uint,float,const float3&),27)(joint,angle,vec); }

inline void geomob::move_joint( uint joint, const float3& vec, bool orig )
{ return VT_CALL(void,(uint,const float3&,bool),28)(joint,vec,orig); }

inline void geomob::move_joint_orig( uint joint, const float3& vec )
{ return VT_CALL(void,(uint,const float3&),29)(joint,vec); }

inline void geomob::set_mesh_visible( coid::token name, bool show )
{ return VT_CALL(void,(coid::token,bool),30)(name,show); }

inline void geomob::set_mesh_visible_id( uint id, bool show )
{ return VT_CALL(void,(uint,bool),31)(id,show); }

inline float3 geomob::get_joint_model_pos( uint joint ) const
{ return VT_CALL(float3,(uint) const,32)(joint); }

inline double3 geomob::get_joint_ecef_pos( uint joint ) const
{ return VT_CALL(double3,(uint) const,33)(joint); }

inline float3 geomob::get_joint_ecef_rot_z( uint joint ) const
{ return VT_CALL(float3,(uint) const,34)(joint); }

inline float3 geomob::get_joint_local_pos( uint joint ) const
{ return VT_CALL(float3,(uint) const,35)(joint); }

inline void geomob::deselect()
{ return VT_CALL(void,(),36)(); }

inline uint geomob::get_num_bones() const
{ return VT_CALL(uint,() const,37)(); }

inline const pkg::bone_meta* geomob::get_bone_meta_ptr() const
{ return VT_CALL(const pkg::bone_meta*,() const,38)(); }

inline const pkg::bone_desc* geomob::get_bone_desc_ptr() const
{ return VT_CALL(const pkg::bone_desc*,() const,39)(); }

inline const pkg::bone_data* geomob::get_bone_ibp_ptr() const
{ return VT_CALL(const pkg::bone_data*,() const,40)(); }

inline const pkg::bone_data* geomob::get_bone_bp_local_ptr() const
{ return VT_CALL(const pkg::bone_data*,() const,41)(); }

inline pkg::bone_data* geomob::get_bone_local_ptr() const
{ return VT_CALL(pkg::bone_data*,() const,42)(); }

inline iref<ot::animation> geomob::load_animation( const coid::token& filename, const coid::token& root_bone, uint frame_offset )
{ return VT_CALL(iref<ot::animation>,(const coid::token&,const coid::token&,uint),43)(filename,root_bone,frame_offset); }

inline void geomob::set_animate_mode( pkg::EGeomAnimateMode mode )
{ return VT_CALL(void,(pkg::EGeomAnimateMode),44)(mode); }

inline float3 geomob::animate()
{ return VT_CALL(float3,(),45)(); }

inline void geomob::set_skeleton_weight( float weight )
{ return VT_CALL(void,(float),46)(weight); }

inline iref<ot::animation_stack> geomob::get_animation_stack()
{ return VT_CALL(iref<ot::animation_stack>,(),47)(); }

inline void geomob::set_visible( bool visible )
{ return VT_CALL(void,(bool),48)(visible); }

inline bool geomob::is_visible() const
{ return VT_CALL(bool,() const,49)(); }

inline bool geomob::is_ready() const
{ return VT_CALL(bool,() const,50)(); }

inline bool geomob::get_bone_model_dq( uint joint, quat& rot, quat& dual ) const
{ return VT_CALL(bool,(uint,quat&,quat&) const,51)(joint,rot,dual); }

inline bool geomob::get_bone_model_tm( uint joint, float3& pos, quat& rot ) const
{ return VT_CALL(bool,(uint,float3&,quat&) const,52)(joint,pos,rot); }

inline bool geomob::get_bone_model_tm_offset( uint joint, const float3& offset, float3& pos, quat& rot ) const
{ return VT_CALL(bool,(uint,const float3&,float3&,quat&) const,53)(joint,offset,pos,rot); }

inline bool geomob::get_bone_model_bp_dq( uint joint, quat& rot, quat& dual ) const
{ return VT_CALL(bool,(uint,quat&,quat&) const,54)(joint,rot,dual); }

inline bool geomob::get_bone_model_bp_tm( uint joint, float3& pos, quat& rot ) const
{ return VT_CALL(bool,(uint,float3&,quat&) const,55)(joint,pos,rot); }

inline const pkg::bone_gpu_data* geomob::get_bone_skin_dq( uint bone_id ) const
{ return VT_CALL(const pkg::bone_gpu_data*,(uint) const,56)(bone_id); }

inline bool geomob::get_bone_local_dq( uint joint, quat& rot, quat& dual ) const
{ return VT_CALL(bool,(uint,quat&,quat&) const,57)(joint,rot,dual); }

inline bool geomob::get_bone_local_tm( uint joint, float3& pos, quat& rot ) const
{ return VT_CALL(bool,(uint,float3&,quat&) const,58)(joint,pos,rot); }

inline const pkg::mesh_desc* geomob::get_meshes_ptr() const
{ return VT_CALL(const pkg::mesh_desc*,() const,59)(); }

inline const pkg::mesh_data* geomob::get_meshes_data_ptr() const
{ return VT_CALL(const pkg::mesh_data*,() const,60)(); }

inline const pkg::lod_meshes* geomob::get_lods_ptr() const
{ return VT_CALL(const pkg::lod_meshes*,() const,61)(); }

inline const pkg::lod_meshes* geomob::get_collision_meshes_ptr() const
{ return VT_CALL(const pkg::lod_meshes*,() const,62)(); }

inline uchar* geomob::get_mesh_flags_ptr() const
{ return VT_CALL(uchar*,() const,63)(); }

inline const pkg::mesh_obb_data* geomob::get_meshes_obbs() const
{ return VT_CALL(const pkg::mesh_obb_data*,() const,64)(); }

inline coid::dynarray<pkg::mesh_desc> geomob::get_meshes() const
{ return VT_CALL(coid::dynarray<pkg::mesh_desc>,() const,65)(); }

inline coid::dynarray<pkg::lod_meshes> geomob::get_lods() const
{ return VT_CALL(coid::dynarray<pkg::lod_meshes>,() const,66)(); }

inline pkg::lod_meshes geomob::get_collision_meshes() const
{ return VT_CALL(pkg::lod_meshes,() const,67)(); }

inline coid::dynarray<uchar> geomob::get_mesh_flags() const
{ return VT_CALL(coid::dynarray<uchar>,() const,68)(); }

inline void geomob::attach_to( const iref<ot::geomob>& geom, uint joint_id, bool update_tm )
{ return VT_CALL(void,(const iref<ot::geomob>&,uint,bool),69)(geom,joint_id,update_tm); }

inline uint geomob::attach_geom( const coid::token& url, const coid::token& joint, const double3& pos, const quat& rot )
{ return VT_CALL(uint,(const coid::token&,const coid::token&,const double3&,const quat&),70)(url,joint,pos,rot); }

inline void geomob::get_world_transform( double3& pos, quat& rot ) const
{ return VT_CALL(void,(double3&,quat&) const,71)(pos,rot); }

inline void geomob::dump_geom_info()
{ return VT_CALL(void,(),72)(); }

inline uint geomob::get_mtl_count() const
{ return VT_CALL(uint,() const,73)(); }

inline uint geomob::get_mtl_id( uint id ) const
{ return VT_CALL(uint,(uint) const,74)(id); }

inline const pkg::lod_meshes* geomob::get_lod_meshes( uint lod ) const
{ return VT_CALL(const pkg::lod_meshes*,(uint) const,75)(lod); }

inline const pkg::mesh_draw_data2* geomob::get_mesh_draw_data( uint mesh ) const
{ return VT_CALL(const pkg::mesh_draw_data2*,(uint) const,76)(mesh); }

inline const int2* geomob::get_positions( const pkg::mesh_draw_data2* mdd ) const
{ return VT_CALL(const int2*,(const pkg::mesh_draw_data2*) const,77)(mdd); }

inline const ushort* geomob::get_indices( const pkg::mesh_draw_data2* mdd ) const
{ return VT_CALL(const ushort*,(const pkg::mesh_draw_data2*) const,78)(mdd); }

inline const uchar4* geomob::get_skin_indices( const pkg::mesh_draw_data2* mdd ) const
{ return VT_CALL(const uchar4*,(const pkg::mesh_draw_data2*) const,79)(mdd); }

inline const uchar4* geomob::get_skin_weights( const pkg::mesh_draw_data2* mdd ) const
{ return VT_CALL(const uchar4*,(const pkg::mesh_draw_data2*) const,80)(mdd); }

inline void geomob::get_mesh_tm( uint mesh_id, quat& rot, quat& dual )
{ return VT_CALL(void,(uint,quat&,quat&),81)(mesh_id,rot,dual); }

inline bool geomob::has_hit_mask_component() const
{ return VT_CALL(bool,() const,82)(); }

inline uint geomob::create_hit_mask_component()
{ return VT_CALL(uint,(),83)(); }

inline void geomob::ray_vs_hit_mask( const double3& ecef_pos, const float3& ecef_dir, uint hit_mesh_id )
{ return VT_CALL(void,(const double3&,const float3&,uint),84)(ecef_pos,ecef_dir,hit_mesh_id); }

#pragma warning(pop)

} //namespace

#endif //__INTERGEN_GENERATED__geomob_H__
