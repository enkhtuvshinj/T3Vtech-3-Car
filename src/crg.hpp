#pragma once

#include <tt.h>
#include <vector>
#include <fstream>
#include <string>

#define MAX_LAP 5

namespace crg
{
	void init();

	class assets
	{
		private:
		public:
			//meshes
			tt_3d_custom_model *car_mesh = NULL;
			tt_3d_custom_model *npc_car_mesh = NULL;
			tt_3d_custom_model *fence_mesh = NULL;
			tt_3d_custom_model *finish_mesh = NULL;
			tt_3d_custom_model *tree1_mesh = NULL;

			//textures
			tt_3d_texture *track_tex = NULL;
			tt_3d_texture *car_tex = NULL;
			tt_3d_texture *npc_car_tex = NULL;
			tt_3d_texture *fence_tex = NULL;
			tt_3d_texture *finish_tex = NULL;

			tt_3d_texture *tree1_tex1 = NULL;
			tt_3d_texture *tree1_tex2 = NULL;
			tt_3d_texture *tree1_tex3 = NULL;
			tt_3d_texture *tree1_tex4 = NULL;

			assets();
			~assets() {};
	};

	class track
	{
		private:
			tt_3d_object *m_obj = NULL;
			tt_3d_object *m_finish = NULL;
			std::vector<tt_3d_object*> m_trees;
			tt_vec3 m_finish_pos = {-143.0f, 0.0f, 0.0f};

		public:
			std::vector<tt_3d_object*> m_fence;
			track(crg::assets& assets);
			~track() {};
			tt_vec3 get_finish_pos() {return m_finish_pos;};

	};

	class car
	{
		private:
			tt_3d_object *m_obj = NULL;
			tt_3d_custom_model *m_mesh = NULL;
			tt_vec3 m_pos = {0.0f, 0.0f, 0.0f};
			tt_vec3 m_vel = {0.0f, 0.0f, 0.0f};
			tt_vec3 m_acc = {0.0f, 0.0f, 0.0f};
			tt_vec3 m_rot = {0.0f, 0.0f, 0.0f};
			tt_vec3 m_dir = {0.0f, 0.0f, -1.0f}; //initial orientation
			float m_current_lap_time = 0.0f;
			void _update_player();
			void _update_npc();

		public:
			bool m_is_player;
			car(unsigned int place, bool is_player, crg::assets& assets);
			~car();
			void update();

			void get_position(tt_vec3* pos_out);
			unsigned int get_place() {return m_place; };
			tt_3d_object* get_3d_object() {return m_obj;};
			tt_vec3 get_vel() {return m_vel;};
			void set_vel(tt_vec3& vel) {m_vel=vel;};
			tt_vec3 get_acc() {return m_acc;};
			unsigned int get_current_lap() {return m_current_lap;};
			float get_current_lap_time() {return m_current_lap_time;};

			void set_at_starting_position(crg::track& track);
			void colliding_with_car(crg::car& car);
			void colliding_with_track(crg::track& track);
			uint32_t m_next_checkpoint{0};
			uint32_t m_total_checkpoints{0};
			unsigned int m_current_lap = 0;
			unsigned int m_place;
	};

    // Guide cube for the NPC to reach in a straight line.
	class guide_cube
	{
		private:
			tt_vec3 m_pos = {0.0f, 0.0f, 0.0f};
			tt_vec3 m_vel = {0.0f, 0.0f, 0.0f};
			tt_vec3 m_acc = {0.0f, 0.0f, 0.0f};
			tt_vec3 m_rot = {0.0f, 0.0f, 0.0f};

		public:
			guide_cube(tt_vec3& pos);
			~guide_cube();
	};

	class ui_panel
	{
		private:
			tt_font *m_font_big = NULL;
			tt_font *m_font_mid = NULL;
			tt_font *m_font_small = NULL;

			tt_2d_object *m_place = NULL;
			tt_2d_object *m_speed = NULL;
			tt_2d_object *m_lap = NULL;
			tt_2d_object *m_lap_time = NULL;


			tt_2d_texture *m_place_tex = NULL;
			tt_2d_texture *m_speed_tex = NULL;
			tt_2d_texture *m_lap_tex = NULL;
			tt_2d_texture *m_lap_time_tex = NULL;

		public:
			ui_panel();
			~ui_panel();
			void update(std::vector<crg::car>& car);
	};

	class race
	{
		private:
			bool m_has_started{false};
			std::vector<tt_3d_object*> m_checkpoints;
			std::vector<car*> m_participants;

			void build_checkpoint_cubes();
		public:
			race();
			~race();

			void add_participant(car* car_entity);
			void update();
	};
}

