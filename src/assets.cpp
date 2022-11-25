#include "crg.hpp"

crg::assets::assets()
{
	//meshes
	car_mesh = tt_3d_custom_model_load_file("assets/car_enj.obj");

	//textures
	car_tex = tt_3d_texture_new("assets/car_enj.png", false);
	track_tex = tt_3d_texture_new("assets/track.png", false);
}