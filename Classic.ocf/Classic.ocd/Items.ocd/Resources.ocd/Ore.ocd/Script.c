/*-- Ore --*/

protected func Construction()
{
	var graphic = Random(5);
	if (graphic)
		SetGraphics(Format("%d", graphic));
}

protected func Hit(x, y)
{
	StonyObjectHit(x, y);
	return true;
}

public func IsFoundryIngredient() { return true; }

local Collectible = true;
local Name = "$Name$";
local Description = "$Description$";
local Rebuy = true;
local Plane = 460;