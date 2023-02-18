#include "../gm_manager.h"
#include "gm_scene_base.h"
#include "../gm_card_manager.h"


class Test : public SceneBase {
public:


	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	CardManager* cmgr = CardManager::GetInstance();

private:




};