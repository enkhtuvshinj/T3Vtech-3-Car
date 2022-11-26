#pragma once

#include <tt.h>
#include <vector>

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
			tt_3d_custom_model *tree_mesh = NULL;

			//textures
			tt_3d_texture *track_tex = NULL;
			tt_3d_texture *car_tex = NULL;
			tt_3d_texture *npc_car_tex = NULL;
			tt_3d_texture *fence_tex = NULL;
			tt_3d_texture *finish_tex = NULL;
			tt_3d_texture *tree_tex = NULL;

			assets();
			~assets() {};
	};

	class track
	{
		private:
			tt_3d_object *m_obj = NULL;
			tt_3d_object *m_finish = NULL;
			std::vector<tt_3d_object*> m_fence;
			std::vector<tt_3d_object*> m_trees;
			tt_vec3 m_finish_pos = {-143.0f, 0.0f, 0.0f};

		public:
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

		public:
			bool m_is_player;
			car(bool is_player, tt_vec3& pos, crg::assets& assets);
			~car();
			void update();
			void get_position(tt_vec3* pos_out);
			void set_at_starting_position(unsigned int place, crg::track& track);
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
}

