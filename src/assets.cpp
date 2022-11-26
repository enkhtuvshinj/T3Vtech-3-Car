#include "crg.hpp"

crg::assets::assets()
{
	//meshes
	car_mesh = tt_3d_custom_model_load_file("assets/car_enj_no_mirror.obj");
	npc_car_mesh = tt_3d_custom_model_load_file("assets/car_mat.obj");
	fence_mesh = tt_3d_custom_model_load_file("assets/fence.obj");
	tree_mesh = tt_3d_custom_model_load_file("assets/tree.obj");

	//textures
	car_tex = tt_3d_texture_new("assets/car_enj_no_mirror.png", false);
	track_tex = tt_3d_texture_new("assets/track.png", false);
	npc_car_tex = tt_3d_texture_new("assets/car_mat.png", false);
	fence_tex = tt_3d_texture_new("assets/fence.png", false);
	tree_tex = tt_3d_texture_new("assets/tree_tex.png", false);
}
