#include "crg.hpp"


int main(int argc, char *argv[])
{
	crg::init();

	crg::assets assets;
	crg::track track(assets);

	//creating player car
	tt_vec3 player_pos = {0.0f, 0.0f, 0.0f};
	crg::car car(true, player_pos, assets);
	car.set_at_starting_position(2, track);

	tt_vec3 npc_pos = {-1.5f, 0.0f, 6.0f};
	crg::car npc(false, npc_pos, assets);
	npc.set_at_starting_position(1, track);

	tt_vec3 light_col={0.5f, 0.3f, 0.03f};
	tt_vec3 light_pos={-20.0f, 10.0f, -50.0f};
	tt_point_light light=tt_point_light_new();
	tt_point_light_set_color(light, &light_col);
	tt_point_light_set_position(light, &light_pos);
	tt_point_light_set_strength(light, 2500.0f);

	//skybox
	tt_3d_object *sky = NULL;
	sky=tt_3d_object_new();
	tt_3d_custom_model *sky_model = NULL;
	sky_model=tt_3d_custom_model_load_file("assets/sky.obj");
	tt_3d_texture *sky_texture = NULL;
	sky_texture=tt_3d_texture_new("assets/car_game_sky3.png", false);

	tt_3d_object_use_custom_model(sky, sky_model);
	tt_3d_object_use_texture(sky, sky_texture);
	tt_vec3 scale={300, 300, 300};
	tt_3d_object_scale(sky, &scale);
	tt_vec3 pos = {0.0f, 290.0f, 0.0f};
	tt_3d_object_set_position(sky, &pos);
	tt_3d_object_light_affected(sky, false);
	tt_3d_object_back_face_culling(sky, false);

	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		car.update();
		npc.update();

		car.get_position(&pos);
		pos.y = 280.0f;
		tt_3d_object_set_position(sky, &pos);

		tt_new_frame();
	}

	return 0;
}
