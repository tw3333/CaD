#pragma once

//UI�쐬�̂��߂�Composite�f�U�C���p�^�[���N���X

class UIComponent {
public:
	
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Add(UIComponent* component) {}
	virtual void Remove(UIComponent* component) {}
	virtual UIComponent* getChild(int index) { return nullptr;  }

};