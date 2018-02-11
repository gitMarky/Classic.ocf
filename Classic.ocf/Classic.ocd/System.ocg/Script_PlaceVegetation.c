
/**
Better Vegetation Placement. Besides many new parameters it also does the following:
- Makes a definition call in the object to GetVegetationRootDepth() to determine how deep the plant shall be rooted (default 5)
- Checks that 80% vertical space is free for the plant, ignores horizontal space
- Leaves at least 10 pixels distance between each placed object
- Can be used for any objects, e.g. chests in tunnels ;-)
Parameters:

@par definition Object to be planted.
@par amount Quantity to be planted.
@par rectangle [optional] Target rectangle as array [x, y, width, height]. Always in absolute coordinates.
@par material_soil [optional] The soil material in which the plant grows, use {@c nil} (default) for placement in materials with Soil=1.
@par material_liquid [optional] Use 0 for non-submerged plants, or the material number for placement in that liquid (e.g. Material("Lava") for lava plants).
@par underground [optional] If {@c true} the object will be placed only in tunnels.
@par hanging [optional] Set to {@c true} for hanging plants, such as stalactices hanging from caves.
@par con_range [optional] Defines the min and max growth rate the vegetation can vary in e.g. [0, 100] for random growth
@par rot_range [optional] Defines the min and max rotation adjustment to the landscape in e.g. [-30, 30] for -30 to +30 degrees.
@return array An array with the placed vegetation.

@version 0.3
@credits Tyron, GZE (http://www.clonkforge.net/pr.pid?=1525)
 */
global func PlaceVegetationEx(id definition, int amount, proplist rectangle, int material_soil, int material_liquid, bool underground, bool hanging, array con_range, array rot_range)
{
	if (definition == nil)
	{
		FatalError("This function needs a definition");
	}

	if (amount == nil)
	{
		amount = 1;
	}
	else if (amount < 0)
	{
		FatalError("Cannot place a negative amount!");
	}
	
	var y_direction;
	if (hanging)
	{
		y_direction = 1;
	}
	else
	{
	 	y_direction = -1;
	}
	
	var x, y, width, height;
	
	if (rectangle == nil)
	{
		x = 0;
		y = 0;
		width = LandscapeWidth();
		height = LandscapeHeight();
	}
	else
	{
	 	x = rectangle.x;
	 	y = rectangle.y;
	 	width = rectangle.w;
	 	height = rectangle.h;
	}
	
	// adjust offsets
	if (this)
	{
		x -= GetX();
		y -= GetY();
	}

	if (con_range == nil)
	{
		con_range = [100, 100];
	}
	
	if (rot_range == nil)
	{
		rot_range = [0, 0];
	}
	
	var root_depth = definition->~GetVegetationRootDepth();
	if (!root_depth) root_depth = 5;
	
	// Failsafe
	var attempts = 0;
	
	// At least 80% of the objects height must be free vertically
	var minverticalspace = (definition->GetDefHeight() * 4) / 5;
	
	// The Material the object will be placed in
	var freemat = -1;
	if (underground) freemat = Material("Tunnel");
	if (material_liquid != nil) freemat = material_liquid;

	// Create a dozen random places and try there
	var rndx, rndy, valid, plant, con;
	
	// to make the loop a bit more efficient we do this calculation outside the loop - these are adjustments for root depth etc.
	var rndy_diff, realy_diff;
	if (hanging)
	{
		rndy_diff = definition->GetDefHeight() - root_depth;
		realy_diff = definition->GetDefHeight();
	}
	else
	{
		rndy_diff = root_depth;
		realy_diff = definition->GetDefHeight() / 2;
	}
	
	var vegetation=[];
	
	for (var i = 0; i < amount && attempts < 50000; attempts++)
	{
		rndx = x + Random(width);
		rndy = y + Random(height);
		

		// Okay, we found the correct material, lets try place it somewhere below that material if free
		if (isMaterialSoil(rndx, rndy, material_soil))
		{
			// Search upwards/downwards for free area
			valid = 0;
			
			while (isMaterialSoil(rndx, rndy, material_soil) && rndy < y + height && rndy > y)
			{
				rndy += y_direction;
				
				if (GetMaterial(rndx, rndy) == freemat)
				{
					valid = true;
					break;
				}
			}
			
			// Has to be either in liquid or free of liquid
			valid = valid && ((material_liquid && GBackLiquid(rndx, rndy)) || (!material_liquid && !GBackLiquid(rndx, rndy)));
			
			if (valid)
			{
				// Search upwards/downwards again to see how much free vertical space we have
				var rndy_spacecheck = rndy, testverticalspace = minverticalspace;
				
				while (GetMaterial(rndx, rndy_spacecheck) == freemat && testverticalspace > 0)
				{
					rndy_spacecheck += y_direction;
					testverticalspace--;
				}
				
				// Ok, enough vertical space
				if (testverticalspace == 0)
				{
					con = BoundBy(RandomX(con_range[0], con_range[1]), 1, 100);
					
					if (hanging)
					{
						rndy -= y_direction * (realy_diff * (100 - con)) / 100;
					}
					
					rndy += rndy_diff; // Adjust for root depth etc.
					
					
					if (!FindObject(Find_ID(definition), Find_Distance(Max(10, definition->GetDefWidth()/2), rndx, rndy)))
					{
						plant = CreateObjectAbove(definition, rndx, rndy);

						plant->SetCon(con);
						
						if (Random(2)) // do not always autorotate
						{
							
							var bot_dy = (plant->GetCon() * definition->GetDefHeight()) / 200;
							
							var lefty = plant->GetYBorder(Max(0, plant->GetX()-2), plant->GetY() + bot_dy, -2 * y_direction, 30);
							var righty = plant->GetYBorder(Min(LandscapeWidth(), plant->GetX()+2), plant->GetY() + bot_dy, -2 * y_direction, 30);
							if (lefty != -1 && righty != -1)
							{
								plant->RelSetR
								(
									BoundBy((Angle(-2, lefty, 2, righty) - 90) / 4, rot_range[0], rot_range[1]),
									0,
									bot_dy - root_depth
								);
							}
						}
						
						vegetation[i] = plant;
						i++;
					}
				}
			}
		}
	}
	return vegetation;
}

global func isMaterialSoil(x, y, materialsoil)
{
	if (materialsoil != nil)
	{
		return GetMaterial(x, y) == materialsoil;
	}
	else
	{
		return GetMaterialVal("Soil", "Material", GetMaterial(x, y));
	}
}

/**
 Automatically places vegetation in the landscape.
 @par definition This type of vegetation will be placed.
 @par quantity This many objects will be placed, depends on {@c quantity_relative}.
 @par quantity_relative [optional]  See {@link TODO}. This is {@c PLACEMENT_Amount_Relative} by default.
                        {@c PLACEMENT_Amount_Relative} generates at least one object. At
                        {@c quantity == 100} the area covered by the tree shape should cover
                        10% of the area of the specified rectangle.
 @par rectangle [optional] Objects will be placed in this rectangle in the landscape, coordinates are always global.
                By default the rectangle covers the whole landscape. 
 @return array An array containing the created objects.                        
 @author Marky
 @version 0.3
 */
global func AutoPlaceVegetation(id definition, int quantity, bool quantity_relative, proplist rectangle)
{
	if (definition == nil)
	{
		FatalError("This function needs a definition");
	}

	var width, height;
	
	if (rectangle == nil)
	{

		width = LandscapeWidth();
		height = LandscapeHeight();
	}
	else
	{
		width = rectangle.w;
		height = rectangle.h;
	}

	var number = quantity;
	
	var material_soil = definition->~GetVegetationSoil();
	var material_liquid = definition->~GetVegetationLiquid();
	var underground = definition->~GetVegetationUnderground();
	var hanging = definition->~GetVegetationHanging();
	var con_range = definition->~GetVegetationConRange();
	var rot_range = definition->~GetVegetationRotation();
	
	return PlaceVegetationEx(definition, number, rectangle, material_soil, material_liquid, underground, hanging, con_range, rot_range);
}