#include "crg.hpp"

crg::assets::assets()
{
	//meshes
	car_mesh = tt_3d_custom_model_load_file("assets/car_enj_no_mirror.obj");
	npc_car_mesh = tt_3d_custom_model_load_file("assets/car_mat.obj");
	fence_mesh = tt_3d_custom_model_load_file("assets/fence.obj");
	finish_mesh = tt_3d_custom_model_load_file("assets/finish.obj");

	tree1_mesh = tt_3d_custom_model_load_file("assets/tree.obj");

	//textures
	car_tex = tt_3d_texture_new("assets/car_enj_no_mirror.png", false);
	track_tex = tt_3d_texture_new("assets/track_high_res.png", false);
	npc_car_tex = tt_3d_texture_new("assets/car_mat.png", false);
	fence_tex = tt_3d_texture_new("assets/fence.png", false);
	finish_tex = tt_3d_texture_new("assets/finish.png", false);

	tree1_tex1 = tt_3d_texture_new("assets/tree1_tex1.png", false);
	tree1_tex2 = tt_3d_texture_new("assets/tree1_tex2.png", false);
	tree1_tex3 = tt_3d_texture_new("assets/tree1_tex3.png", false);
	tree1_tex4 = tt_3d_texture_new("assets/tree1_tex4.png", false);
}
