#pragma once

#include <tt.h>
#include <vector>
#include <fstream>

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
			unsigned int m_place;
			void _update_player();
			void _update_npc();

		public:
			bool m_is_player;
			car(unsigned int place, bool is_player, crg::assets& assets);
			~car();
			void update();
			void get_position(tt_vec3* pos_out);
			tt_3d_object* get_3d_object() {return m_obj;};
			tt_vec3 get_vel() {return m_vel;};
			void set_vel(tt_vec3& vel) {m_vel=vel;};
			tt_vec3 get_acc() {return m_acc;};
			void set_at_starting_position(crg::track& track);
			void colliding_with_car(crg::car& car);
			void colliding_with_track(crg::track& track);
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
		ui_panel();
		~ui_panel();
	};
}

