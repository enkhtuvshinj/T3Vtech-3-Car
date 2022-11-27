#include "crg.hpp"
extern bool tt_frustum_culling_trigger;

void crg::init()
{
	tt_init("Wild Racing Game", 1000, 800, true, 0, NULL);

	//setting general lighting properties
	tt_gfx_gouraud_shading(true);
	tt_gfx_phong_shading(false);
	tt_frustum_culling_trigger=false; //some slight hack

	//set directional lighting
	tt_dir_light light = tt_directional_light_new();
	tt_vec3 light_dir = {-1.0, -10.0f, 10.0f};
	tt_vec3 light_col={0.5f, 0.3f, 0.03f};
	tt_directional_light_set_direction(light, &light_dir);
	tt_directional_light_set_color(light, &light_col);
	tt_directional_light_set_strength(light, 1.1f);
}
