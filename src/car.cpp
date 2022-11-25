#include "crg.hpp"

crg::car::car(bool is_player, tt_vec3& pos, crg::assets& assets)
{
	m_is_player = is_player;
	m_pos = pos;

	m_obj = tt_3d_object_new();
	tt_3d_object_use_custom_model(m_obj, assets.car_mesh);
	tt_3d_object_set_position(m_obj, &m_pos);

	if(m_is_player)
	{
		tt_vec3 m_pos_cam = m_pos;
		m_pos_cam.y += 2.0f;
		m_pos_cam.z += 7.5f;
		tt_camera_set_position(&m_pos_cam);
	}
}

crg::car::~car()
{

}