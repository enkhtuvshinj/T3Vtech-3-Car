#include<chrono>
#include<thread>
#include "crg.hpp"

#define NUM_NPC 7

int main(int argc, char *argv[])
{
	crg::init();

	crg::assets assets;
	crg::track track(assets);
	crg::race race(2);

	//create NPC cars
	std::vector<crg::car> car;
	for(int i = 0; i<NUM_NPC; i++)
	{
		crg::car tmp_car(i+1, false, assets);
		tmp_car.set_at_starting_position(track);
		car.emplace_back(tmp_car);
	}

	//and the player car
	crg::car tmp_car(NUM_NPC+1, true, assets);
	tmp_car.set_at_starting_position(track);
	race.add_participant(&tmp_car);
	car.emplace_back(tmp_car);

	//skybox
	tt_3d_object *sky = NULL;
	sky=tt_3d_object_new();
	tt_3d_custom_model *sky_model = NULL;
	sky_model=tt_3d_custom_model_load_file("assets/sky.obj");
	tt_3d_texture *sky_texture = NULL;
	sky_texture=tt_3d_texture_new("assets/car_game_sky_high_res_no_alpha.png", false);

	tt_3d_object_use_custom_model(sky, sky_model);
	tt_3d_object_use_texture(sky, sky_texture);
	tt_vec3 scale={300, 300, 300};
	tt_3d_object_scale(sky, &scale);
	tt_vec3 pos = {0.0f, 290.0f, 0.0f};
	tt_3d_object_set_position(sky, &pos);
	tt_3d_object_light_affected(sky, false);
	tt_3d_object_back_face_culling(sky, false);

	crg::ui_panel ui;
	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		for(int i = 0; i<car.size(); i++)
		{
			car[i].update();
			for(int j = 0; j<car.size(); j++)
			{
				car[i].colliding_with_car(car[j]);
				car[i].colliding_with_track(track);
			}
		}

		car[NUM_NPC].get_position(&pos); //player car
		pos.y = 280.0f;
		tt_3d_object_set_position(sky, &pos);

		ui.update(car);
		race.update();
		tt_new_frame();
	}

	return 0;
}
