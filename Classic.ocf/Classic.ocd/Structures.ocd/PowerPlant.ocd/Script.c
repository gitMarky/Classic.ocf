/*
 * Power plant
 *
 *	Burns fuels like coal, wood and oil to produce power. The steam engine
 *	produces 120 units of power independent of the fuel. However, the fuel 
 *	determines the amount of fuel and thereby the burn time.
 *
 *
 * Author: Marky (mesh, texture), Open Clonk Team (script, by Maikel)
 */

#include Library_Structure
#include Library_Ownable
#include Library_DoorControl
#include Library_PowerProducer
#include Library_Flag

#include Basement60

local DefaultFlagRadius = 1000;

static const PowerPlant_produced_power = 120;

func Definition(id def)
{
	def.MeshTransformation = Trans_Mul(Trans_Translate(-6500, -1000, 0), 
	                                   Trans_Rotate(20, 0, 1, 0),
	                                   Trans_Scale(990, 1000, 1000));
	def.PictureTransformation = Trans_Mul(Trans_Rotate( 20, 0, 1, 0), 
	                                      Trans_Rotate( -5, 0, 0, 1),
	                                      Trans_Rotate(-10, 1, 0, 0),
	                                      Trans_Translate(1000, -5000, -2000));
}


// Variable to store the fuel amount currently held in the engine.
local fuel_amount;

protected func Construction()
{
	fuel_amount = 0;
	return _inherited(...);
}

protected func Initialize()
{
	// you get one coal for free!
	fuel_amount = Coal->GetFuelAmount();

	AddTimer("ContentsCheck", 10);
	return _inherited(...);
}

public func IsContainer() { return true; }

protected func RejectCollect(id item, object obj)
{
	if (obj->~IsFuel())
		return false;
	return true;
}


private func SoundOpenDoor()
{
	Sound("GateOpen");
}

private func SoundCloseDoor()
{
	Sound("GateClose");
}

protected func Collection(object obj, bool put)
{
	Sound("Objects::Clonk");
}

public func ContentsCheck()
{
	// Ejects non fuel items immediately
	var fuel;
	if(fuel = FindObject(Find_Container(this), Find_Not(Find_Func("IsFuel")))) 
	{
		fuel->Exit(-53, 21, -20, -1, -1, -30);
		Sound("Chuff");
	}
	
	// If active don't do anything.
	if (GetAction() == "Work") 
		return;

	// If there is fuel available let the network know.
	if (fuel_amount > 0 || FindObject(Find_Container(this), Find_Func("IsFuel")))
		RegisterPowerProduction(PowerPlant_produced_power);
	return;
}

public func GetFuelAmount()
{
	return fuel_amount;
}


/*-- Power Production --*/

// Produces power on demand, so not steady.
public func IsSteadyPowerProducer() { return false; }

// Low priority so that other sources of power are drained before burning fuel.
public func GetProducerPriority() { return 0; }

// Callback from the power library for production of power request.
public func OnPowerProductionStart(int amount) 
{ 
	// Check if there is fuel.
	if (fuel_amount <= 0)
	{
		// Search for new fuel among the contents.
		var fuel = FindObject(Find_Container(this), Find_Func("IsFuel"));
		if (!fuel)
			return false;
		// Extract the fuel amount from the new piece of fuel.	
		fuel_amount += fuel->~GetFuelAmount(true) * 18;
		fuel->RemoveObject();
	}
	AddEffect("Working", this, 100, 1, this);
	return true;
}

// Callback from the power library requesting to stop power production.
public func OnPowerProductionStop(int amount)
{
	RemoveEffect("Working", this);
	return true;
}

// Start call from working action.
protected func WorkStart()
{
	Sound("PowerPlant", false, nil, nil, 1);
	return;
}

// Phase call from working action, every two frames.
protected func FxWorkingTimer(object target, proplist effect, int timer)
{
	// Reduce the fuel amount by 1 per frame.
	fuel_amount -= 1;
	// Check if there is still enough fuel available.
	if (fuel_amount <= 0)
	{
		// Search for new fuel among the contents.
		var fuel = FindObject(Find_Container(this), Find_Func("IsFuel"));
		if (!fuel)
		{
			// Set action to idle and unregister this producer as available from the network.
			UnregisterPowerProduction();
			return;
		}
		// Extract the fuel amount from the new piece of fuel.	
		fuel_amount += fuel->~GetFuelAmount(true) * 18;
		fuel->RemoveObject();
	}
	// Smoke from the exhaust shaft.
	Smoke( 16 * GetCalcDir(), -27, 14);
	Smoke(  3 * GetCalcDir(), -26, 12);
	// Fire in the furnace.
	CreateParticle("Fire", 21 * GetCalcDir() + RandomX(-2, 2), 14 + RandomX(-2, 2), PV_Random(-1, 1), PV_Random(-1, 1), PV_Random(10, 18), Particles_Fire(), 2);
	return;
}

// Stop call from working action.
protected func WorkStop()
{
	// Don't kill the sound in this call, since that would interupt the sound effect.
	return;
}

// Abort call from working action.
protected func WorkAbort()
{
	// Sound can be safely stopped here since this action will always end with an abort call.
	Sound("PowerPlant", false, nil, nil, -1);
	return;	
}


/*-- Properties --*/

//private func Burning()
//{
//  // Rauch
//  // Energieerzeugung
//  DoEnergy(+25);
//  // Weiter
//  if(GetActTime() < GetBurnTime()) return(1);
//  // Fertig
//  SetAction("Idle");
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 130;
local ContainBlast = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Length = 10,
	Delay = 1,
	NextAction = "DoorOpen",
	StartCall = "SoundOpenDoor",
	Animation = "OpenDoor",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Delay = 20,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
	Animation = "DoorOpen",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Length = 10,
	Delay = 1,
	NextAction = "Idle",
	StartCall = "SoundCloseDoor",
	Animation = "CloseDoor",
},

};
