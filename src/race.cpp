
#include <vector>
#include <crg.hpp>

static std::vector<tt_vec3> race_checkpoints;
static void _init_checkpoints();


crg::race::race(uint32_t* game_state)
{
	m_game_state = game_state;
	build_checkpoint_cubes();
}

crg::race::~race()
{}

void crg::race::update()
{
	// Check collision between participants and next checkpoint.
	for (auto& participant: m_participants) {
		auto next_checkpoint{
			m_checkpoints[participant->m_next_checkpoint]};
		auto pobj{participant->get_3d_object()};
		if(tt_3d_object_colliding_aabb(pobj, next_checkpoint)) {
			if (participant->m_next_checkpoint == 0) {
				// Just completed a lap.
				participant->m_current_lap++;
			}

			if (participant->m_next_checkpoint == m_checkpoints.size() - 1) {
				participant->m_next_checkpoint = 0;
			} else {
				participant->m_next_checkpoint++;
			}
			participant->m_total_checkpoints++;
		}
		if (participant->m_is_player && participant->m_current_lap == MAX_LAP + 1) {
			*m_game_state = OUTRO_STATE;
		}
	}

	for (int i = 0; i < m_participants.size(); ++i) {
		m_participants[i]->m_place = 1;
		uint32_t total_i = m_participants[i]->m_total_checkpoints;
		for (int j = 0; j < m_participants.size(); ++j) {
			uint32_t total_j = m_participants[j]->m_total_checkpoints;
			if (total_j > total_i) {
				m_participants[i]->m_place++;
			}
		}
	}
}

void crg::race::add_participant(crg::car* car)
{
	m_participants.push_back(car);
}

void crg::race::build_checkpoint_cubes()
{
	_init_checkpoints();

	/* One before the last element. */
	for (int i = 0; i < race_checkpoints.size() - 1; i += 2) {
		tt_vec3* curr_point = &race_checkpoints[i];
		tt_vec3* next_point = &race_checkpoints[i + 1];

		// Get middle point.
		tt_vec3 middle_point = tt_math_vec3_add(curr_point, next_point);
		middle_point = tt_math_vec3_mul_float(&middle_point, 0.5f);

		// Get length of checkpoint.
		tt_vec3 line_vec = tt_math_vec3_sub(next_point, curr_point);
		float total_length = tt_math_vec3_length(&line_vec);

		// Get angle of checkpoint.
		line_vec = tt_math_vec3_normalize(&line_vec);
		tt_vec3 ref_frame = {0, 0, -1};
		float angle = std::acos(
			tt_math_vec3_dot(&line_vec, &ref_frame) / 1.0 // Vectors are normalized.
		);
		if(line_vec.x > 0)
		{
			angle *= -1.0f;
		}
		angle += 0.5f * tt_PI;

		// Create collision cube.
		tt_3d_object *cube_obj = tt_3d_object_new();
		tt_vec3 scale = {5.0f, 1.0f, 100.0f};
		tt_vec3 rot_axis = {0.0f, 1.0f, 0.0f};
		tt_3d_object_make_cube(cube_obj);
		tt_3d_object_scale(cube_obj, &scale);
		tt_3d_object_set_position(cube_obj, &middle_point);
		tt_3d_object_rotate(cube_obj, &rot_axis, angle);
		tt_3d_object_back_face_culling(cube_obj, false);
		tt_3d_object_make_invisible(cube_obj, true);
		m_checkpoints.emplace_back(cube_obj);
	}
}

static void _init_checkpoints()
{
	race_checkpoints = {
		{{-148.748, 0, 1.54457}},
		{{-148.658, 0, -5.59604}},
		{{-148.579, 0, -12.2524}},
		{{-148.498, 0, -19.019}},
		{{-148.538, 0, -26.9941}},
		{{-149, 0, -35.1331}},
		{{-149.538, 0, -43.9082}},
		{{-150.089, 0, -52.8304}},
		{{-150.727, 0, -63.1224}},
		{{-151.641, 0, -72.24}},
		{{-152.927, 0, -81.2856}},
		{{-154.241, 0, -90.189}},
		{{-155.673, 0, -99.8069}},
		{{-157.019, 0, -108.818}},
		{{-158.32, 0, -117.517}},
		{{-159.504, 0, -125.436}},
		{{-160.722, 0, -133.579}},
		{{-161.228, 0, -146.235}},
		{{-160.055, 0, -154.319}},
		{{-158.176, 0, -162.945}},
		{{-155.7, 0, -171.036}},
		{{-151.391, 0, -179.809}},
		{{-148.447, 0, -183.795}},
		{{-140.451, 0, -193.732}},
		{{-131.618, 0, -199.835}},
		{{-123.906, 0, -202}},
		{{-113.198, 0, -204.522}},
		{{-104.826, 0, -206.155}},
		{{-92.7627, 0, -208.46}},
		{{-83.7133, 0, -210.18}},
		{{-73.609, 0, -211.53}},
		{{-64.627, 0, -212.365}},
		{{-54.8071, 0, -213.251}},
		{{-43.1566, 0, -214.296}},
		{{-33.4339, 0, -215.167}},
		{{-24.9709, 0, -215.925}},
		{{-18.1874, 0, -216.533}},
		{{-8.64594, 0, -217.387}},
		{{-0.310077, 0, -217.767}},
		{{7.81769, 0, -217.828}},
		{{17.7647, 0, -217.862}},
		{{27.4279, 0, -217.885}},
		{{35.6831, 0, -217.902}},
		{{43.0575, 0, -217.917}},
		{{51.1565, 0, -217.932}},
		{{58.4886, 0, -217.946}},
		{{65.6138, 0, -217.96}},
		{{72.6437, 0, -217.973}},
		{{79.5069, 0, -217.986}},
		{{86.7805, 0, -218}},
		{{91.72, 0, -217.539}},
		{{98.1723, 0, -216.856}},
		{{107.934, 0, -215.482}},
		{{114.581, 0, -214.274}},
		{{123.97, 0, -212.531}},
		{{131.018, 0, -210.882}},
		{{137.411, 0, -209.156}},
		{{144.905, 0, -206.71}},
		{{151.678, 0, -204.155}},
		{{159.77, 0, -200.711}},
		{{167.26, 0, -196.45}},
		{{173.343, 0, -192.062}},
		{{180.338, 0, -186.029}},
		{{186.994, 0, -179.156}},
		{{193.492, 0, -171.586}},
		{{195.521, 0, -165.526}},
		{{195.02, 0, -158.213}},
		{{194.02, 0, -147.653}},
		{{190.606, 0, -136.244}},
		{{185.726, 0, -126.139}},
		{{180.102, 0, -118.697}},
		{{172.787, 0, -111.612}},
		{{166.863, 0, -106.097}},
		{{159.916, 0, -99.7113}},
		{{152.996, 0, -93.374}},
		{{144.128, 0, -85.9988}},
		{{137.375, 0, -81.1112}},
		{{128.601, 0, -74.8619}},
		{{121.156, 0, -68.5417}},
		{{116.375, 0, -61.9627}},
		{{113.044, 0, -55.1624}},
		{{109.639, 0, -44.0577}},
		{{109.25, 0, -35.1038}},
		{{109.143, 0, -26.1534}},
		{{110.636, 0, -15.0969}},
		{{113.329, 0, -7.02337}},
		{{117.657, 0, 2.83578}},
		{{122.004, 0, 10.7557}},
		{{126.252, 0, 19.1714}},
		{{129.855, 0, 27.8068}},
		{{134.193, 0, 38.5983}},
		{{137.408, 0, 46.6675}},
		{{139.669, 0, 52.373}},
		{{142.526, 0, 59.6001}},
		{{145.898, 0, 68.8736}},
		{{147.839, 0, 75.3049}},
		{{149.747, 0, 81.8818}},
		{{151.304, 0, 87.307}},
		{{152.612, 0, 94.4563}},
		{{153.59, 0, 101.747}},
		{{153.863, 0, 112.306}},
		{{153.427, 0, 123.188}},
		{{152.899, 0, 134.235}},
		{{150.991, 0, 143.85}},
		{{148.173, 0, 151.427}},
		{{141.558, 0, 160.48}},
		{{134.979, 0, 166.782}},
		{{126.491, 0, 173.433}},
		{{117.35, 0, 179.47}},
		{{105.518, 0, 185.904}},
		{{96.1432, 0, 189.395}},
		{{88.057, 0, 192.148}},
		{{78.6956, 0, 194.971}},
		{{71.046, 0, 196.299}},
		{{62.0666, 0, 197.652}},
		{{53.9836, 0, 198.818}},
		{{43.5691, 0, 199.953}},
		{{36.4854, 0, 200.194}},
		{{28.498, 0, 200.353}},
		{{18.6166, 0, 200.507}},
		{{5.56339, 0, 200.686}},
		{{-1.67674, 0, 200.78}},
		{{-13.7066, 0, 199.921}},
		{{-22.0079, 0, 198.467}},
		{{-32.521, 0, 196.433}},
		{{-46.6286, 0, 192.145}},
		{{-55.3894, 0, 188.982}},
		{{-63.9478, 0, 185.769}},
		{{-73.7255, 0, 182.053}},
		{{-81.7456, 0, 178.995}},
		{{-88.0058, 0, 176.157}},
		{{-95.1546, 0, 172.845}},
		{{-102.814, 0, 168.629}},
		{{-108.309, 0, 165.183}},
		{{-116.629, 0, 158.259}},
		{{-123.386, 0, 151.252}},
		{{-128.534, 0, 143.443}},
		{{-132.557, 0, 136.141}},
		{{-136.105, 0, 129.348}},
		{{-140.084, 0, 119.026}},
		{{-141.821, 0, 107.401}},
		{{-143.022, 0, 97.0406}},
		{{-146.12, 0, 87.0068}},
		{{-148.43, 0, 81.3111}},
		{{-150.129, 0, 72.547}},
		{{-150.143, 0, 72.4041}},
		{{-150.392, 0, 62.2776}},
		{{-150.181, 0, 53.4851}},
		{{-149.889, 0, 45.1902}},
		{{-149.6, 0, 37.9387}},
		{{-149.249, 0, 29.5608}},
		{{-149.24, 0, 29.3322}},
		{{-149.044, 0, 19.6941}},
		{{-149.275, 0, 11.9635}},
	};
}

