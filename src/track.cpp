#include "crg.hpp"

crg::track::track(crg::assets& assets)
{
	m_obj = tt_3d_object_new();
	tt_3d_object_make_cube(m_obj);

	tt_vec3 scale = {500.0f, 0.1f, 500.0f};
	tt_vec3 pos = {0.0f, -2.0f, 0.0f};
	tt_3d_object_scale(m_obj, &scale);
	tt_3d_object_set_position(m_obj, &pos);

	tt_3d_object_use_texture(m_obj, assets.track_tex);
	tt_3d_object_back_face_culling(m_obj, false);
}
