#include "gm_scene_base.h"
#include "../gm_manager.h"
#include "../gm_camera.h"


class GmCamera;
class SceneSelectPhase;

class ScenePlay : public SceneBase {
public:
	ScenePlay() {}
	~ScenePlay();

	GmCamera* camera_ = nullptr;
	SceneSelectPhase* dungeon_ = nullptr;

	float jump_vel_ = 0;
	dxe::Mesh* ctrl_box_ = nullptr;
	dxe::Mesh* floor_ = nullptr;

	std::list<dxe::Mesh*> field_boxs_;

	tnl::Quaternion fix_rot;

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;



private:

	float width1 = DXE_WINDOW_WIDTH / 10;
	float height1 = DXE_WINDOW_HEIGHT / 10;

	int playscreen = 0;
	int miniscreen = 0;

	float m_window_width = width1 * 3;
	float m_window_height = height1 * 3;


	float m_w = (width1 * 3) / 10;
	float m_h = (height1 * 3) / 10;

	


};

