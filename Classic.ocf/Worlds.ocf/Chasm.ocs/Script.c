#include Library_Scenario


private func Init_Goals()
{
	AddGoal_Wealth(100 + 50 * SCENPAR_Difficulty);
	AddGoal_Resource(Gold, 30 + 20 * SCENPAR_Difficulty);
}

private func Init_Environment()
{
	SetSkyParallax(0, 33, 57, 0, 0, 0, 0); 
	AddAmbience_Time();

	// Some dark clouds which rain few ashes.
	Cloud->Place(15);
	Cloud->SetPrecipitation("Ashes", 17 + 10 * SCENPAR_Difficulty);
	Cloud->SetCloudRGB(60, 35, 25);
	Cloud->SetLightning(0 + 1 * SCENPAR_Difficulty);

	// Some natural disasters.
	Disaster(Meteor, 8, 4, 2);
	Disaster(Volcano, 15, 6);
	Disaster(Earthquake, 8, 4);
	Volcano->SetMaterial("DuroLava");
}

private func Init_Vegetation()
{
	var burned_trees_1 = AutoPlaceVegetation(Tree1, 6);

	for (var tree in burned_trees_1)
		tree->~SetBurned();

	AutoPlaceVegetation(Tree1, 15);
	AutoPlaceVegetation(Tree2, 9);
	AutoPlaceVegetation(Tree3, 12);

	PlaceGrass(15);
	
	for (var grass in FindObjects(Find_ID(Grass)))
	{
		grass->SetClrModulation(RGB(225+Random(30), Random(30), Random(30)));
	}
}

private func Init_Animals()
{
	PlaceAnimals(Bird, 3, PLACEMENT_Air);
	// 2 monster eggs
	// 1 zap nest
	// 4 fire monster eggs
}

private func InitMaterial()
{
	// Some objects in the earth.	
	PlaceInEarth(Bone, 2);
	PlaceInEarth(Flint, 7);
	PlaceInEarth(Gold, 4);
	PlaceInEarth(Loam, 5);
	PlaceInEarth(Skull, 1);
}


private func Player_StartingMaterial(int player)
{
	SetWealth(player, 80);
	
	var trees = FindObjects(Find_Func("IsTree"));
	var start = trees[Random(GetLength(trees))];

	for (var crew in FindObjects(Find_Category(OCF_CrewMember), Find_Owner(player)))
	{
		crew->SetPosition(start->GetX(), start->GetY());
	}
}

private func Player_StartingEquipmentForCrewMember(int player, object crew, int crew_index)
{
	_inherited(player, crew, crew_index);

	if (0 == crew_index)
	{
		crew->CreateContents(ClassicFlag);
		crew->CreateContents(Conkit);
	}
}

private func Player_InitialKnowledge(int player)
{
	var needs_power = !FindObject(Find_ID(Rule_NoPowerNeed));

	
	GivePlayerBasicKnowledge(player);
	GivePlayerSpecificKnowledge(player, [ClassicHutWooden, ClassicHutStone]);
	if (needs_power) GivePlayerPowerKnowledge(player);
	GivePlayerCraftingKnowledge(player);
	GivePlayerMiningKnowledge(player);
	GivePlayerPumpingKnowledge(player);	
	GivePlayerChemicalKnowledge(player);
	
	var myHomeBaseMaterial =
	[
		[Conkit, 3],
		[Pipe, 5],
		[Loam, 11],
		[Wood, 12],
		[Metal, 8],
		[Concrete, 9],
		[Flint, 9],
		[TFlint, 14],
		[ClassicDynamiteBox, 1],
		[GunPowder, 1],
		[MetalBarrel, 2],
		[Torch, 4],
		[ClassicFlag, 1],
		[ClassicClonk, 6]
	];
	var myHomeBaseProduction = 
	[
		[Conkit, 3],
		[Pipe, 5],
		[Loam, 11],
		[Metal, 8],
		[Concrete, 9],
		[Flint, 10],
		[TFlint, 10],
		[ClassicDynamiteBox, 1],
		[GunPowder, 11],
		[MetalBarrel, 2],
		[ClassicFlag, 2],
		[ClassicClonk, 3]
	];
	
	for (var material in myHomeBaseMaterial)
	{
		DoBaseMaterial(player, material[0], material[1]);
	}
	for (var material in myHomeBaseProduction)
	{
		DoBaseProduction(player, material[0], material[1]);
	}

	return true;
}