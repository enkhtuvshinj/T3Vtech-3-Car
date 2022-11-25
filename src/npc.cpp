#include "crg.hpp"

crg::npc::npc(tt_vec3& pos, crg::assets& assets)
{
	m_pos = pos;

	m_obj = tt_3d_object_new();
	tt_3d_object_use_custom_model(m_obj, assets.npc_car_mesh);
	tt_3d_object_set_position(m_obj, &m_pos);
    tt_3d_object_use_texture(m_obj, assets.npc_car_tex);

}

crg::npc::~npc()
{

}
