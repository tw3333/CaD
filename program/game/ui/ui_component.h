#pragma once

//UI作成のためのCompositeデザインパターンクラス

class UIComponent {
public:
	
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Add(UIComponent* component) {}
	virtual void Remove(UIComponent* component) {}
	virtual UIComponent* getChild(int index) { return nullptr;  }

};