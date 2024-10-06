#pragma once
#include "UI.h"

class Sprite;

class Panel : public UI
{
	using Super = UI;
public:
	Panel();
	virtual ~Panel();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void		AddChild(unique_ptr<UI> ui);
	void		RemoveChild(UI* ui);


protected:
	//vector<UI*> _children;
	vector<unique_ptr<UI>>	_children;
	vector<UI*>				_childrenToRemove;
};

