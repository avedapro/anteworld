#pragma once

#ifndef __INTERGEN_GENERATED__environment_H__
#define __INTERGEN_GENERATED__environment_H__

//@file Interface file for environment interface generated by intergen
//See LICENSE file for copyright and license information

#include <comm/commexception.h>
#include <comm/intergen/ifc.h>

#include <ot/env.h>
#include <v8/v8.h>

class WorldView;


namespace ot {

////////////////////////////////////////////////////////////////////////////////
///OT environment interface ////////////////////////////////////////////////
class environment
    : public intergen_interface
{
public:

    // --- interface methods ---

    ///Save environment config if it was modified
    void save_changed_config();

    void get_atmospheric_params( ifc_out ot::atmospheric_params& dst, bool def = false ) const;

    void get_water_params( ifc_out ot::water_params& dst, bool def = false ) const;

    void get_fog_params( ifc_out ot::fog_params& dst, bool def = false ) const;

    void get_forest_params( ifc_out ot::forest_params& dst, bool def = false ) const;

    void get_snow_params( ifc_out ot::snow_params& dst, bool def = false ) const;

    void get_weather_params( ifc_out ot::weather_params& dst, bool def = false ) const;

    void get_cloud_params( ifc_out ot::cloud_params& dst, bool def = false ) const;

    void set_atmospheric_params( const ot::atmospheric_params& src );

    void set_water_params( const ot::water_params& src );

    void set_fog_params( const ot::fog_params& src );

    void set_forest_params( const ot::forest_params& src );

    void set_snow_params( const ot::snow_params& src );

    void set_weather_params( const ot::weather_params& src );

    void set_cloud_params( const ot::cloud_params& src );

    //@return wind speed at given height above the ground
    float wind_speed_at_height( float h ) const;

    int64 get_day_of_year() const;

    double get_time_of_day() const;

    float get_timeflow_multiplier() const;

    //@param dyear day of year
    //@param tday UTC time [msec]
    //@param flowm time flow multiplier
    void set_time( int64 dyear, double tday, float flowm = 1.0f );

    ///Set ocean wave amplitude and surf wave amplitude
    void set_sea_params( float wave_amp, float surf_amp, float wave_len );

    ///Get ocean wave params
    void get_sea_params( ifc_out float& wave_amp, ifc_out float& surf_amp, ifc_out float& wave_len ) const;

    // --- creators ---

    static iref<environment> get() {
        return get<environment>(0);
    }

    template<class T>
    static iref<T> get( T* _subclass_ );

    // --- internal helpers ---

    static const int HASHID = 3635061359;

    int intergen_hash_id() const override final { return HASHID; }

    bool iface_is_derived( int hash ) const override final {
        return hash == HASHID;
    }

    const coid::tokenhash& intergen_interface_name() const override final {
        static const coid::tokenhash _name = "ot::environment";
        return _name;
    }

    static const coid::token& intergen_default_creator_static( EBackend bck ) {
        static const coid::token _dc("ot::environment.get@3635061359");
        static const coid::token _djs("ot::environment@wrapper.js");
        static const coid::token _dlua("ot::environment@wrapper.lua");
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

    environment()
    {}
};

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline iref<T> environment::get( T* _subclass_ )
{
    typedef iref<T> (*fn_creator)(environment*);

    static fn_creator create = 0;
    static const coid::token ifckey = "ot::environment.get@3635061359";

    if (!create)
        create = reinterpret_cast<fn_creator>(
            coid::interface_register::get_interface_creator(ifckey));

    if (!create)
        throw coid::exception("interface creator inaccessible: ") << ifckey;

    return create(_subclass_);
}

#pragma warning(push)
#pragma warning(disable : 4191)

inline void environment::save_changed_config()
{ return VT_CALL(void,(),0)(); }

inline void environment::get_atmospheric_params( ot::atmospheric_params& dst, bool def ) const
{ return VT_CALL(void,(ot::atmospheric_params&,bool) const,1)(dst,def); }

inline void environment::get_water_params( ot::water_params& dst, bool def ) const
{ return VT_CALL(void,(ot::water_params&,bool) const,2)(dst,def); }

inline void environment::get_fog_params( ot::fog_params& dst, bool def ) const
{ return VT_CALL(void,(ot::fog_params&,bool) const,3)(dst,def); }

inline void environment::get_forest_params( ot::forest_params& dst, bool def ) const
{ return VT_CALL(void,(ot::forest_params&,bool) const,4)(dst,def); }

inline void environment::get_snow_params( ot::snow_params& dst, bool def ) const
{ return VT_CALL(void,(ot::snow_params&,bool) const,5)(dst,def); }

inline void environment::get_weather_params( ot::weather_params& dst, bool def ) const
{ return VT_CALL(void,(ot::weather_params&,bool) const,6)(dst,def); }

inline void environment::get_cloud_params( ot::cloud_params& dst, bool def ) const
{ return VT_CALL(void,(ot::cloud_params&,bool) const,7)(dst,def); }

inline void environment::set_atmospheric_params( const ot::atmospheric_params& src )
{ return VT_CALL(void,(const ot::atmospheric_params&),8)(src); }

inline void environment::set_water_params( const ot::water_params& src )
{ return VT_CALL(void,(const ot::water_params&),9)(src); }

inline void environment::set_fog_params( const ot::fog_params& src )
{ return VT_CALL(void,(const ot::fog_params&),10)(src); }

inline void environment::set_forest_params( const ot::forest_params& src )
{ return VT_CALL(void,(const ot::forest_params&),11)(src); }

inline void environment::set_snow_params( const ot::snow_params& src )
{ return VT_CALL(void,(const ot::snow_params&),12)(src); }

inline void environment::set_weather_params( const ot::weather_params& src )
{ return VT_CALL(void,(const ot::weather_params&),13)(src); }

inline void environment::set_cloud_params( const ot::cloud_params& src )
{ return VT_CALL(void,(const ot::cloud_params&),14)(src); }

inline float environment::wind_speed_at_height( float h ) const
{ return VT_CALL(float,(float) const,15)(h); }

inline int64 environment::get_day_of_year() const
{ return VT_CALL(int64,() const,16)(); }

inline double environment::get_time_of_day() const
{ return VT_CALL(double,() const,17)(); }

inline float environment::get_timeflow_multiplier() const
{ return VT_CALL(float,() const,18)(); }

inline void environment::set_time( int64 dyear, double tday, float flowm )
{ return VT_CALL(void,(int64,double,float),19)(dyear,tday,flowm); }

inline void environment::set_sea_params( float wave_amp, float surf_amp, float wave_len )
{ return VT_CALL(void,(float,float,float),20)(wave_amp,surf_amp,wave_len); }

inline void environment::get_sea_params( float& wave_amp, float& surf_amp, float& wave_len ) const
{ return VT_CALL(void,(float&,float&,float&) const,21)(wave_amp,surf_amp,wave_len); }

#pragma warning(pop)

} //namespace

#endif //__INTERGEN_GENERATED__environment_H__
