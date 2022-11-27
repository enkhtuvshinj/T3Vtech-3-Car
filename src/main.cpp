#include<chrono>
#include<thread>
#include "crg.hpp"

static int G_num_npcs;


int main(int argc, char *argv[])
{
	uint32_t _game_state = INTRO_STATE;
	crg::init();

	crg::assets assets;
	crg::track track(assets);
	crg::race game_race(&_game_state);

	tt_vec3 p_pos{-161.091, 0, 8.52551};
	std::vector<tt_vec3> npc_start_positions{
		{p_pos.x + 4.0f * 1, 0, p_pos.z},
		{p_pos.x + 4.0f * 2 + 1.0f, 0, p_pos.z},
		{p_pos.x + 4.0f * 3 + 2.0f, 0, p_pos.z},
	};
	G_num_npcs = npc_start_positions.size();

	//create NPC cars
	std::vector<crg::car> car;
	for(int i = 0; i<G_num_npcs; i++)
	{
		crg::car tmp_car(i+1, false, assets);
		tmp_car.set_at_starting_position(&npc_start_positions[i]);
		car.emplace_back(tmp_car);
	}

	//and the player car
	crg::car tmp_car(G_num_npcs+1, true, assets);
	tmp_car.set_at_starting_position(&p_pos);
	car.emplace_back(tmp_car);

	for (int i = 0; i < car.size(); ++i) {
		game_race.add_participant(&car[i]);
	}

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

	crg::ui_panel ui(&_game_state);
	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		if (_game_state == PLAY_STATE || _game_state == OUTRO_STATE) {
			for(int i = 0; i<car.size(); i++)
			{
				car[i].update();
				for(int j = 0; j<car.size(); j++)
				{
					car[i].colliding_with_car(car[j]);
					car[i].colliding_with_track(track);
				}
			}
			game_race.update();
		} else if (_game_state == INTRO_STATE) {
			//positioning the camera
			tt_vec3 cam_pos_delta;
			car[G_num_npcs].get_direction(&cam_pos_delta);
			cam_pos_delta = tt_math_vec3_mul_float(&cam_pos_delta, -7.5f);

			tt_vec3 cam_pos;
			car[G_num_npcs].get_position(&cam_pos);
			cam_pos = tt_math_vec3_add(&cam_pos, &cam_pos_delta);
			cam_pos.y += 2.0f;
			tt_camera_set_position(&cam_pos);

			if(tt_input_keyboard_key_press(TT_KEY_SPACE)) {
				_game_state = PLAY_STATE;
			}
		}

		car[G_num_npcs].get_position(&pos); //player car
		pos.y = 280.0f;
		tt_3d_object_set_position(sky, &pos);

		ui.update(car);
		tt_new_frame();
	}

	return 0;
}
