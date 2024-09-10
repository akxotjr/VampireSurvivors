#include "pch.h"
#include "Panel.h"

Panel::Panel()
{

}

Panel::~Panel()
{

}

void Panel::Init()
{
	Super::Init();

	for (auto& child : _children)
		child->Init();
}

void Panel::Update()
{
	Super::Update();

	for (auto& child : _children)
		child->Update();

	//for (UI* child : _childrenToRemove) {
	//	auto it = std::remove(_childrenToRemove.begin(), _childrenToRemove.end(), child);
	//	_childrenToRemove.erase(it, _childrenToRemove.end());
	//}
}

void Panel::Render(HDC hdc)
{
	Super::Render(hdc);

	for (auto& child : _children)
		child->Render(hdc);
}

void Panel::AddChild(unique_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	_children.push_back(::move(ui));
}

void Panel::RemoveChild(UI* ui)
{
	if (ui == nullptr)
		return;

	_children.erase(::remove_if(_children.begin(), _children.end(),
		[&ui](const unique_ptr<UI>& ptr) {
			return ptr.get() == ui;
		}),
		_children.end());
	//_childrenToRemove.push_back(ui);
}