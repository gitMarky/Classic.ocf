/*
 *	Chemical factory
 *
 *	Author: Marky, Mesh: constantin
 */

#include Library_Structure
#include Library_Ownable
#include Library_DoorControl
#include Library_Producer

#include Basement48

local hold_production;

func Definition(def)
{
	def.MeshTransformation = Trans_Translate(1500);
	def.PictureTransformation = Trans_Mul(Trans_Translate(0, 0, -1000),
	                                      Trans_Rotate(-25, 1, 0, 0),
	                                      Trans_Rotate(-20,0,1,0));
}



/*-- Production --*/

public func IsProduct(id product_id)
{
	return product_id->~IsChemicalProduct();
}

private func ProductionTime(id toProduce) { return 100; }
public func PowerNeed() { return 40; }

public func OnProductionStart(id product)
{
	AddEffect("Working", this, 100, 1, this);
	hold_production = false;
	Sound("Gear", false, nil, nil, 1);
}

public func OnProductionHold(id product)
{
	hold_production = true;
	Sound("Gear", false, nil, nil, -1);
	Sound("Fire::Blowout");
}

public func OnProductionContinued(id product)
{
	hold_production = false;
	Sound("Gear", false, nil, nil, 1);
}

public func OnProductionFinish(id product)
{
	RemoveEffect("Working", this);
	Sound("Gear", false, nil, nil, -1);
}

protected func FxWorkingTimer()
{
	if(!hold_production)
		Smoking();
}

private func Smoking()
{
	if (Random(2)) Smoke(+9, -29, 12);
	Smoke(-3, -27, 7 + Random(5));
}


/* Door control */

private func SoundOpenDoor()
{
  Sound("SteelGate2");
}
  
private func SoundCloseDoor()
{
  Sound("SteelGate2");
}

/* Properties */

local Name = "$Name$";
local Description ="$Description$";
local BlastIncinerate = 100;
local ContainBlast = true;
local HitPoints = 70;


local ActMap = {
OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Delay = 1,
	NextAction = "DoorOpen",
	StartCall = "SoundOpenDoor",
	Animation = "OpenDoor",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Procedure = DFA_NONE,
	Length = 20,
	Delay = 1,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
	Animation = "DoorOpen",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Delay = 1,
	NextAction = "Idle",
	StartCall = "SoundCloseDoor",
	Animation = "CloseDoor",
},
};

local Name = "$Name$";
local Description = "$Description$";
