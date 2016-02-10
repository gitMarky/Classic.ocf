/*
 *	The Home Base
 *
 *	Author: Marky
 */

#include Library_Base
#include Library_Vendor

private func Collection2(object item)
{
	if(!IsBase() && item->~IsBaseFlag() && item->GetOwner() != NO_OWNER)
	{
		item->~SetBase(this);
		MakeBase(false); // this actually makes it a base...
		ScheduleCall(this, this.UpdateInteractionMenus, 2);
	}

	_inherited(item);
}

private func OnFlagLost()
{
	UpdateInteractionMenus();
	MakeBase(true);
}

/* --- Buy materials at base --- */

// Provides an interaction menu for buying things.
public func HasInteractionMenu() { return true; }

public func AllowBuyMenuEntries() { return GetFlag() != nil;}
public func AllowSellMenuEntries() { return GetFlag() != nil;}

public func GetInteractionMenus(object clonk)
{
	var menus = _inherited(clonk) ?? [];

	// only open the menus if ready
	var base_menu =
	{
		title = "$MsgBaseControl$",
		entries_callback = this.GetBaseControlMenuEntries,
		callback = "OnBaseControlSelection",
		callback_hover = "OnBaseControlHover",
		callback_target = this,
		BackgroundColor = GetPlayerColor(GetOwner()),
		Priority = 60
	};
	PushBack(menus, base_menu);
	
	return menus;
}


public func GetBaseControlMenuEntries(object clonk)
{
	var menu_entries = [];
	
	if (GetFlag())
	{
		PushBack(menu_entries,
			{symbol = this, extra_data = clonk,
				custom =
				{
					Right = "100%", Bottom = "2em",
					BackgroundColor = {Std = 0, OnHover = 0x50ff0000},
					image = {Right = "2em", Symbol = GetFlag()},
					text = {Left = "2em", Text = "$MsgRemoveFlag$"},
					Bottom = "1.2em",
					Priority = -1,
					BackgroundColor = RGB(25, 100, 100),
				}});
	}
	
	return menu_entries;
}

public func OnBaseControlSelection(id symbol, object clonk)
{
	RemoveFlag(clonk);
	UpdateInteractionMenus(this.GetBaseControlMenuEntries);	
}

public func OnBaseControlHover(id symbol, object clonk, desc_menu_target, menu_id)
{
	var text = "$DescRemoveFlag$";
	GuiUpdateText(text, menu_id, 1, desc_menu_target);
}

public func RemoveFlag(object clonk)
{
	var flag = GetFlag();
	
	if (flag == nil) return false;
	
	flag->LostBase();
	
	var x = flag->GetX();
	var y = flag->GetY();
	
	if (!clonk->Collect(flag))
	{
		flag->SetPosition(x, y);
	}
	
	return true;
}

public func GetFlag()
{
	return FindObject(Find_Func("IsBaseFlag"), Find_Owner(GetOwner()), Find_ActionTarget(this));
}

protected func OnStructureDestroyed()
{
	var flag = GetFlag();
	if (flag != nil)
	{
		flag->~LostBase();
	}
	
	_inherited(...);
}
