#include "crg.hpp"

#define NUM_NPC 7

int main(int argc, char *argv[])
{
	crg::init();

	crg::assets assets;
	crg::track track(assets);

	//creating player car
	crg::car car(NUM_NPC+1, true, assets);
	car.set_at_starting_position(track);

	//create NPCs
	std::vector<crg::car> npc;
	for(int i = 0; i<NUM_NPC; i++)
	{
		crg::car tmp_npc(i+1, false, assets);
		tmp_npc.set_at_starting_position(track);
		npc.emplace_back(tmp_npc);
	}

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
		for(int i = 0; i<npc.size(); i++)
		{
			npc[i].update();
		}

		car.get_position(&pos);
		pos.y = 280.0f;
		tt_3d_object_set_position(sky, &pos);

		tt_new_frame();
	}

	return 0;
}
