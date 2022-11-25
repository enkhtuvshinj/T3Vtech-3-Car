#pragma once

#include <tt.h>

namespace crg
{
	void init();

	class assets
	{
		private:
		public:
			//meshes
			tt_3d_custom_model *car_mesh = NULL;

			//textures
			tt_3d_texture *track_tex = NULL;

			assets();
			~assets() {};
	};

	class track
	{
		private:
			tt_3d_object *m_obj = NULL;

		public:
			track(crg::assets& assets);
			~track() {};
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

		public:
			bool m_is_player;
			car(bool is_player, tt_vec3& pos, crg::assets& assets);
			~car();
	};
}