/*
 * Classic clonk controls, similar to Clonk Rage, but with improvements.
 *
 * Author: Marky, original by Sven2
 */



#appendto ClassicClonk

// clear old controls
static const //CON_Aim=-1,
//             CON_GUICursor=-1,
             CON_AimUp=-1,
             CON_AimDown=-1,
             CON_AimLeft=-1,
             CON_AimRight=-1,
             CON_AimAxisUp=-1,
             CON_AimAxisDown=-1,
             CON_AimAxisLeft=-1,
             CON_AimAxisRight=-1,
             CON_Jump=-1,
//             CON_ForcedThrow=-1,
             CON_ThrowDelayed=-1,
             CON_Drop=-1,
             CON_Collect=-1,
             CON_ThrowAlt=-1,
             CON_ForcedThrowAlt=-1,
             CON_ThrowAltDelayed=-1,
             CON_DropAlt=-1,
//             CON_Hotkey1=-1,
//             CON_Hotkey2=-1,
//             CON_Hotkey3=-1,
//             CON_Hotkey4=-1,
//             CON_Hotkey5=-1,
             CON_Hotkey6=-1,
             CON_Hotkey7=-1,
             CON_Hotkey8=-1,
             CON_Hotkey9=-1,
             CON_Hotkey0=-1,
             CON_DropHotkey1=-1,
             CON_DropHotkey2=-1,
             CON_DropHotkey3=-1,
             CON_DropHotkey4=-1,
             CON_DropHotkey5=-1,
             CON_DropHotkey6=-1,
             CON_DropHotkey7=-1,
             CON_DropHotkey8=-1,
             CON_DropHotkey9=-1,
             CON_DropHotkey0=-1,
             CON_Hotkey1Select=-1,
             CON_Hotkey1SelectAlt=-1,
             CON_Hotkey2Select=-1,
             CON_Hotkey2SelectAlt=-1,
             CON_Hotkey3Select=-1,
             CON_Hotkey3SelectAlt=-1,
             CON_Hotkey4Select=-1,
             CON_Hotkey4SelectAlt=-1,
             CON_Hotkey5Select=-1,
             CON_Hotkey5SelectAlt=-1,
             CON_Hotkey6Select=-1,
             CON_Hotkey6SelectAlt=-1,
             CON_Hotkey7Select=-1,
             CON_Hotkey7SelectAlt=-1,
             CON_Hotkey8Select=-1,
             CON_Hotkey8SelectAlt=-1,
             CON_Hotkey9Select=-1,
             CON_Hotkey9SelectAlt=-1,
             CON_Hotkey0Select=-1,
             CON_Hotkey0SelectAlt=-1,
//             CON_Use=-1,
             CON_UseDelayed=-1,
             CON_CancelUse=-1,
             CON_CancelMenu=-1,
//             CON_UseAlt=-1,
             CON_UseAltDelayed=-1,
//             CON_Contents=-1,
//             CON_Grab=-1,
//             CON_Ungrab=-1,
//             CON_GrabPrevious=-1,
//             CON_GrabNext=-1,
//             CON_PushEnter=-1,
             CON_Interact=-1,
//             CON_Enter=-1,
//             CON_Exit=-1,
             CON_InteractionHotkey1=-1,
             CON_InteractionHotkey2=-1,
             CON_InteractionHotkey3=-1,
             CON_InteractionHotkey4=-1,
             CON_InteractionHotkey5=-1,
             CON_InteractionHotkey6=-1,
             CON_InteractionHotkey7=-1,
             CON_InteractionHotkey8=-1,
             CON_InteractionHotkey9=-1,
             CON_InteractionHotkey0=-1,
//             CON_NextCrew=-1,
//             CON_PreviousCrew=-1,
             CON_PlayerHotkey1=-1,
             CON_PlayerHotkey2=-1,
             CON_PlayerHotkey3=-1,
             CON_PlayerHotkey4=-1,
             CON_PlayerHotkey5=-1,
             CON_PlayerHotkey6=-1,
             CON_PlayerHotkey7=-1,
             CON_PlayerHotkey8=-1,
             CON_PlayerHotkey9=-1,
             CON_PlayerHotkey0=-1,
//             CON_GUIClick1=-1,
//             CON_GUIClick2=-1,
             CON_MenuOK=-1,
             CON_MenuCancel=-1,
//             CON_MenuLeft=-1,
             CON_MenuRight=-1,
             CON_MenuUp=-1,
             CON_MenuDown=-1,
             CON_ObjectMenuOK=-1,
             CON_ObjectMenuOKAll=-1,
             CON_ObjectMenuSelect=-1;
//             CON_ObjectMenuCancel=-1,
//             CON_ObjectMenuLeft=-1,
//             CON_ObjectMenuRight=-1,
//             CON_ObjectMenuUp=-1,
//             CON_ObjectMenuDown=-1,
//             CON_CursorPos=-1;
//             CON_PlayerMenu=-1;
//             CON_ZoomIn=-1,
//             CON_ZoomOut=-1,
//             CON_WheelZoomIn=-1,
//             CON_WheelZoomOut=-1;


static const C4DoubleClick = 10;

static const CON_None = 0;

local last_com, last_com_delay, last_com_down_double;
static g_cr_cons;

static CON_LeftSingle, CON_RightSingle, CON_UpSingle, CON_DownSingle, CON_ThrowSingle, CON_DigSingle, CON_SpecialSingle, CON_Special2Single,
       CON_LeftDouble, CON_RightDouble, CON_UpDouble, CON_DownDouble, CON_ThrowDouble, CON_DigDouble, CON_SpecialDouble, CON_Special2Double;
       
static const CON_Single = 0x1000, CON_Double = 0x2000;

func Definition()
{
	_inherited(...);
	g_cr_cons = [CON_Left, CON_Right, CON_Up, CON_Down, CON_Dig, CON_Special, CON_Special2];
	CON_LeftSingle = CON_Left | CON_Single;
	CON_RightSingle = CON_Right | CON_Single;
	CON_UpSingle = CON_Up | CON_Single;
	CON_DownSingle = CON_Down | CON_Single;
	CON_ThrowSingle = CON_Throw | CON_Single;
	CON_DigSingle = CON_Dig | CON_Single;
	CON_SpecialSingle = CON_Special | CON_Single;
	CON_Special2Single = CON_Special2 | CON_Single;
	CON_LeftDouble = CON_Left | CON_Double;
	CON_RightDouble = CON_Right | CON_Double;
	CON_UpDouble = CON_Up | CON_Double;
	CON_DownDouble = CON_Down | CON_Double;
	CON_ThrowDouble = CON_Throw | CON_Double;
	CON_DigDouble = CON_Dig | CON_Double;
	CON_SpecialDouble = CON_Special | CON_Double;
	CON_Special2Double = CON_Special2 | CON_Double;
	return true;
}

func Initialize()
{
	last_com = CON_None;
	AddTimer(this.SingleConTimer, 1);
	return _inherited(...);
}

func SingleConTimer()
{
	if (last_com != CON_None)
	{
		++last_com_delay;
		if (last_com_delay > C4DoubleClick)
		{
			// Pass additional CON_Single
			if (!(last_com & CON_Double)) ObjectControlClassic(CON_Single | last_com);
			last_com = CON_None;
			last_com_delay = 0;
		}
	}
	if (last_com_down_double) --last_com_down_double;
	return true;
}

public func ObjectControl(int plr, int ctrl, int cursorX, int cursorY, int strength, bool repeat, bool release, bool callInherited)
{
	if (!callInherited)
	{
		  // If regular com, update cursor & selection status
			//if (!(byCom & COM_Single) && !(byCom & COM_Double) && (byCom < COM_ReleaseFirst || byCom > COM_ReleaseLast))
		  //  UpdateSelectionToggleStatus();

		  if (last_com != CON_None)
		  {
				if (last_com != ctrl)
				{
					ObjectControlClassic(CON_Single | last_com, 0, plr, cursorX, cursorY, strength, repeat, release);
					// AutoStopControl uses a single COM_Down instead of DOM_Down_D for drop
					// So a COM_Down_S does what a COM_Down_D normally does, if generated by another key
					// instead of a timeout
					//if (ControlStyle && LastCom == COM_Down) LastComDownDouble = C4DoubleClick;
				}
				else
				{
					ctrl |= CON_Double;
				}
		  }

		  // LastCom/Del process
		  // this is set before issuing the ObjectControlClassic, so ObjectControlClassic-scripts may delete it
		  last_com = ctrl;
		  last_com_delay = 0;
		  // Pass regular/COM_Double byCom to player
		  var rval = ObjectControlClassic(ctrl, 0, plr, cursorX, cursorY, strength, repeat, release);
		  // LastComDownDouble process
		  if (ctrl == CON_DownDouble) last_com_down_double = C4DoubleClick;
		  return rval;
	}
	else
		return _inherited(plr, ctrl, cursorX, cursorY, strength, repeat, release);
}

func ObjectControlClassic(int ctrl, data, int plr, cursorX, cursorY, strength, repeat, release)
{
	if (ObjectControlObjectMenu(plr, ctrl, cursorX, cursorY, strength, repeat, release))
	{
		return true;
	}

	// Switch cursor... a nice hack to bypass the original OC implementation :D
	if (ObjectControlSelection(plr, ctrl, cursorX, cursorY, strength, repeat, release))
	{
		return true;
	}

	var proc = GetProcedure();
	var comdir = GetComDir();

	// building, vehicle, mount, contents, menu control
	var house = Contained();
	var vehicle = GetActionTarget();
	// the clonk can have an action target even though he lost his action.
	// That's why the clonk may only interact with a vehicle if in an
	// appropiate procedure:
	if (proc != "ATTACH" && proc != "PUSH")
		vehicle = nil;

	// forward to script...
	if (house)
	{
		if (Control2Script(ctrl, cursorX, cursorY, strength, repeat, release, house)) return true;
	}
	else if (vehicle)
	{
		if (Control2Script(ctrl, cursorX, cursorY, strength, repeat, release, vehicle)) return true;
	}


	if (ctrl == CON_Special)
	{
		//ObjectControl(plr, CON_Contents, cursorX, cursorY, strength, repeat, release, true);
		if (!release) ObjectControlShiftInventory(CON_InventoryNext);
		return true;
	}
	else if (ctrl == CON_Special2)
	{
		if (!release) OpenContextMenu(this);
	}
	else if (ctrl == CON_SpecialDouble)
	{
		ObjectControl(plr, CON_Contents, cursorX, cursorY, strength, repeat, release, true); 
	}
	else if (ctrl == CON_Left && !release)
	{
		if (proc == DFA_WALK
		 || proc == DFA_FLIGHT
		 || proc == DFA_KNEEL
		 || proc == DFA_THROW
		 || proc == DFA_HANGLE
		 || proc == DFA_PUSH
		 || proc == DFA_SWIM) ObjectComMovement(COMD_Left);
		// scaling is different
		else if (proc == DFA_SCALE)
		{
			if (GetDir() == DIR_Left)
				ObjectComMovement(COMD_Stop);
			else
			{
				ObjectComMovement(COMD_Left);
				ObjectComLetGo(-1);
			}
		}
		// digging also
		else if (proc == DFA_DIG) { if (Inside(comdir,COMD_UpRight,COMD_Left)) SetDigDir(comdir + 1); }
	}
	else if (ctrl == CON_Right && !release)
	{
		if (proc == DFA_WALK
		 || proc == DFA_FLIGHT
		 || proc == DFA_KNEEL
	     || proc == DFA_THROW
		 || proc == DFA_HANGLE
		 || proc == DFA_PUSH
		 || proc == DFA_SWIM) ObjectComMovement(COMD_Right);
		// scaling is a little special
		else if (proc == DFA_SCALE)
		{
			if (GetDir() == DIR_Right)
				ObjectComMovement(COMD_Stop);
			else
			{
				ObjectComMovement(COMD_Right);
				ObjectComLetGo(+1);
			}
		}
		// digging also
		else if (proc == DFA_DIG) { if (Inside(comdir,COMD_Right,COMD_UpLeft)) SetDigDir(comdir - 1); }
	}
	else if (ctrl == CON_Up && !release)
	{
		if (proc == DFA_WALK) PlayerObjectCommand(plr, "Jump");
		else if (proc == DFA_SCALE) ObjectComMovement(COMD_Up);
		else if (proc == DFA_HANGLE) ObjectComMovement(COMD_Stop);
		else if (proc == DFA_PUSH)
		{
			if (!ObjectControlPush(plr, CON_PushEnter))
				 ObjectControlPushErect();
		}
		else if (proc == DFA_SWIM)
		{
			ObjectComMovement(COMD_Up);
			PlayerObjectCommand(plr, "Jump");
		}
	}
	else if (ctrl == CON_Down && !release)
	{
		if (Contained())
		{
			// TODO: vehicle controls
			ObjectControlEntrance(plr, CON_Exit);
		}
		// stop
		else if (proc == DFA_WALK
		 || proc == DFA_FLIGHT
		 || proc == DFA_KNEEL
		 || proc == DFA_THROW) ObjectComMovement(COMD_Stop);
		else if (proc == DFA_PUSH) ObjectComMovement(COMD_Stop);
		// maneuver down
		else if (proc == DFA_SCALE
              || proc == DFA_SWIM) ObjectComMovement(COMD_Down);
		// cancel current action
		else if (proc == DFA_BRIDGE
			  || proc == "BUILD"
			  || proc == "CHOP"
		      || proc == DFA_DIG) ObjectComStop();
		// cancel hangling
		else if (proc == DFA_HANGLE) ObjectComLetGo(0);
	}
	else if (ctrl == CON_DownDouble && !release)
	{
		if (proc == DFA_WALK)
		{
			if(!Contained() && ObjectControlPush(plr, CON_Grab)) return true;
		}
		else if (proc == DFA_PUSH)
		{
			if(!Contained() && ObjectControlPush(plr, CON_Ungrab)) return true;
		}
	}
	else if (ctrl == CON_DigSingle)
	{
		InventoryUseTool(false, true, release);
	}
	else if (ctrl == CON_DigDouble)
	{
		InventoryUseTool(true, true, release);
	}
	else if (ctrl == CON_Throw || ctrl == CON_ForcedThrow)
	{
		var doThrow = (ctrl == CON_ForcedThrow);

		if (!release)
		{
			// open inventory menu for container
			if (proc == DFA_PUSH && GetActionTarget()->~IsContainer() && !GetMenu())
			{
				return ObjectControlPutGet(GetActionTarget(), plr, ctrl, cursorX, cursorY, strength, repeat, release);
			}
			else if (Contained() && Contained()->~IsContainer(this) && !GetMenu())
			{
				return ObjectControlPutGet(Contained(), plr, ctrl, cursorX, cursorY, strength, repeat, release);
			}
		}

		if (!doThrow)
		{
			if (last_com_down_double)
				doThrow = true; // converts to drop in the PlayerObjectCommand method
			else
			{
				var contents = Contents();
				
				if (contents)
				{
					if (Contents()->~IsAttachableTool())
					{
						doThrow = !InventoryUseTool(false, false, release);
					}
					else
					{
						doThrow = !ControlUse2Script(CON_Use, cursorX, cursorY, strength, repeat, release, contents);
					}
				}
			}
		}

		if (doThrow && !release)
		{
			if (proc == DFA_WALK
			 || proc == DFA_FLIGHT
			 || proc == DFA_KNEEL
			 || proc == DFA_THROW) PlayerObjectCommand(plr,"Throw");
			else if (proc == DFA_SCALE
				  || proc == DFA_HANGLE
				  || proc == DFA_SWIM) PlayerObjectCommand(GetOwner(),"Drop");
		}
	}
	else if (ctrl == CON_Enter && !release)
	{
		if (proc == DFA_WALK
	     || proc == DFA_SWIM) ObjectControlEntrance(plr, ctrl);
		else if (proc == DFA_PUSH) ObjectControlPush(plr, CON_PushEnter);
	}
	else if (ctrl == CON_Exit && !release)
	{
		if (proc == DFA_WALK
		 || proc == DFA_SWIM) ObjectControlEntrance(plr, ctrl);
	}
	else if ((ctrl == CON_InventoryNext || ctrl == CON_InventoryPrevious) && !release)
	{
		ObjectControlShiftInventory(ctrl);
	}

	// everything handled.
	return true;
}


func ObjectControlSelection( int plr, int ctrl, int cursorX, int cursorY, int strength, bool repeat, bool release)
{
	if (release) return false;

	var proc = GetProcedure();

	if (ctrl != CON_SelectNext
	 && ctrl != CON_SelectPrevious
	 && ctrl != CON_SelectButton
	 && ctrl != CON_ForcedNextCrew
	 && ctrl != CON_ForcedPreviousCrew)
		return false;

	var forcedSelection = (ctrl == CON_ForcedNextCrew || ctrl == CON_ForcedPreviousCrew);

	if (proc == DFA_PUSH && !forcedSelection)
	{
		var shift, shiftBack;
		if (ctrl == CON_SelectNext)
		{
			shift = true;
			shiftBack = false;
		}
		else if (ctrl == CON_SelectPrevious)
		{
			shift = true;
			shiftBack = true;
		}

		if (shift && ShiftVehicle(plr, shiftBack)) return true;
	}
	else
	{
		var convertCommand = true;

		if (ctrl == CON_SelectNext || ctrl == CON_ForcedNextCrew)
			ctrl = CON_NextCrew;
		else if (ctrl == CON_SelectPrevious || ctrl == CON_ForcedPreviousCrew)
			ctrl = CON_PreviousCrew;
		else
			convertCommand = false;

		if (convertCommand && Control2Player(plr, ctrl, cursorX, cursorY, strength, repeat,release))
			return true;
	}

	return false;
}

func ObjectControlObjectMenu( int plr, int ctrl, int cursorX, int cursorY, int strength, bool repeat, bool release)
{
	if (!GetMenu()) return false;
	if (release) return false;
	

	if(GetMenu()->~IsContentMenu())
	{
		if (ctrl == CON_SelectNext)
		{
			GetMenu()->~KeyboardSelectNextMenu(true);
			return true;
		}
		else if (ctrl == CON_SelectPrevious)
		{
			GetMenu()->~KeyboardSelectNextMenu(false);
			return true;
		}
		// left and right get handled by the menu itself...
		// special is better handled in ObjectControlClassic
		else if (ctrl == CON_Special)
		{
			return false;
		}
		// close menu
		else if (ctrl == CON_DigSingle || ctrl == CON_SpecialDouble)
		{
			// Uncloseable menu?
			if (GetMenu()->~Uncloseable()) return true;
			CancelMenu();
			return true;
		}
	}

	return false;
}

func ObjectControlShiftInventory(ctrl)
{
	// shift contents
	if (GetItems() == nil) return false;

	var amount = GetLength(GetItems());
	if (amount <= 1 && ctrl != nil) return false;

	var index_selection = GetItemPos(GetHandItem()); // we only have one hand item anyway
	var index_target = index_selection;

	// scroll direction
	for(var i = 0; i < MaxContentsCount(); i++)
	{
		if (ctrl == CON_SelectNext || ctrl == CON_InventoryNext)
			index_target++;
		else
			index_target--;

		if (index_target < 0) index_target += MaxContentsCount(); // % does not work as intended with negative numbers
		index_target = index_target % MaxContentsCount();

		if (GetItem(index_target) != nil) break;
	}

	// ok, now we have the new index. Scroll contents accordingly
	var target = GetItem(index_target);
	for(var i = 0; i < amount; i++)
	{
		if (Contents() == target) break;

		ScrollContents(); // ShiftContents() unfortunately does not work...
	}

	SetHandItemPos(0, index_target);
	return true;
}

func ObjectComMovement(int comdir)
{
	SetComDir(comdir);
	//PlayerObjectCommand(cObj->Owner,C4CMD_Follow,cObj);
	// direkt turnaround if standing still
	var proc = GetProcedure();
	if (!GetXDir() && (proc == DFA_WALK || proc == DFA_HANGLE))
	{
		if (comdir == COMD_Left || comdir == COMD_UpLeft || comdir == COMD_DownLeft)
			SetDir(DIR_Left);
		else if (comdir == COMD_Right || comdir == COMD_UpRight || comdir == COMD_DownRight)
			SetDir(DIR_Right);
	}
	return true;
}

func ObjectComStop()
{
	SetAction("Idle");
	return ObjectActionStand();
}

func ObjectActionStand()
{
	SetComDir(COMD_Stop);
	return ObjectActionWalk();
}

func ObjectActionWalk()
{
	if (!SetAction("Walk")) return false;
	SetXDir(); SetYDir();
	return true;
}

func ObjectComLetGo(int xdir)
{
	return ObjectActionJump(xdir,0,true);
}

func ObjectActionJump(int xdir, int ydir, bool by_com)
{
	// scripted jump?
	if (this->~OnActionJump(xdir, ydir, by_com)) return true;
	// hardcoded jump by action
	if (!SetAction("Jump")) return false;
	Fling(xdir, ydir, 1, false); // fixes internal attachment/mobility
	SetAction("Jump");
	return true;
}

func ObjectComUp(int plr) // by DFA_WALK or DFA_SWIM
{
  // Check object entrance, try command enter
  //C4Object *pTarget;
  //DWORD ocf=OCF_Entrance; 
  //if ((pTarget=Game.Objects.AtObject(cObj->x,cObj->y,ocf,cObj)))
  //  if (ocf & OCF_Entrance)
  //    return PlayerObjectCommand(cObj->Owner,C4CMD_Enter,pTarget);
  // Try jump
	var proc = GetProcedure();
	if (proc == DFA_WALK)
	{
		return PlayerObjectCommand(GetOwner(),"Jump");
	}
	return false;
}

func ObjectComDig() // by DFA_WALK
{
	if (!SetAction("Dig")) return false;
	return true;
}

func ObjectComDigRequest() // dig out material chunks
{
	var effect = GetEffect("IntDig", this);

	if (effect) effect.digMaterialRequest = true;
}

func ObjectControlPutGet(object container, int plr, int ctrl, cursorX, cursorY, strength, repeat, release)
{
	// force put object into container
	if ((ctrl == CON_ForcedThrow || (ctrl == CON_Throw && GetProcedure() == DFA_PUSH)) && Contents())
	{
		Contents()->Enter(container);
		return true;
	}

	return ObjectControl(plr, CON_Contents, cursorX, cursorY, strength, repeat, release, true);
}


func SetDigDir(int comd)
{
	SetComDir(comd);
	var lLimit = this.Action.Speed, xdir, ydir;
	if (comd == COMD_Up) { if (GetDir()) xdir=lLimit; else xdir=-lLimit; ydir = -lLimit/2; }
	else if (comd == COMD_UpLeft) { xdir=-lLimit; ydir=-lLimit/2; }
	else if (comd == COMD_Left) { xdir=-lLimit; ydir=0; }
	else if (comd == COMD_DownLeft) { xdir=-lLimit; ydir=+lLimit; }
	else if (comd == COMD_Down) { xdir=0; ydir=+lLimit; }
	else if (comd == COMD_DownRight) { xdir=+lLimit; ydir=+lLimit; }
	else if (comd == COMD_Right) { xdir=+lLimit; ydir=0; }
	else if (comd == COMD_UpRight) { xdir=+lLimit; ydir=-lLimit/2; }
	else if (comd == COMD_Stop) { xdir=0; ydir=0; }
	this.dig_xdir = xdir; this.dig_ydir = ydir;
	SetXDir(xdir,100); SetYDir(ydir,100);
	return true;
}

func ObjectControlDig()
{
	var proc = GetProcedure();
	if (proc == DFA_WALK)
	{
		if (ObjectComDig())
		{
			if (GetDir())
				SetDigDir(COMD_DownRight);
			else
				SetDigDir(COMD_DownLeft);
		}
	}
	else if (proc == DFA_DIG) ObjectComDigRequest();
}

public func ObjectControlPushErect()
{
	if (!GetActionTarget()) return false;

	if (!GetEffect("IntPushErect", GetActionTarget()))
         AddEffect("IntPushErect", GetActionTarget(), 1, 1, this);
	return true;
}

protected func FxIntPushErectTimer( object target, proplist effect, int timer)
{
	if (Inside(target->GetR(), -5, 5)) return -1;
	if (GetProcedure() != DFA_PUSH) return -1;

	target->~SetRDir(-Sin(BoundBy(target->GetR(), -90, 90), 3));
}

static const C4P_Command_Append = 1,
             C4P_Command_Add    = 2,
             C4P_Command_Set    = 4,
             C4P_Command_Range  = 16;

func PlayerObjectCommand(int plr, string cmd, object target, int tx, int ty, object target2, data)
{
	var mode = C4P_Command_Set;
	// Adjust for old-style keyboard throw/drop control: add & in range 
	if (cmd=="Throw" || cmd=="Drop") mode |= (C4P_Command_Add | C4P_Command_Range);
	if (cmd=="Throw")
	{
		var fConvertToDrop = false;
		// Drop on down-down-throw (classic)
		if (last_com_down_double)
		{
			fConvertToDrop = true;
			// Dropping one object automatically reenables LastComDownDouble to
			// allow easy dropping of multiple objects. Also set LastCom for
			// script compatibility (custom scripted dropping) and to prevent
			// unwanted ThrowDouble for mass dropping
			last_com = CON_DownDouble;
			last_com_delay = 0;
			last_com_down_double = C4DoubleClick;
		}
		// Jump'n'Run: Drop on combined Down/Left/Right+Throw
	//	if (pPlr->ControlStyle && (pPlr->PressedComs & (1 << COM_Down))) fConvertToDrop = true;
		if (fConvertToDrop) return PlayerObjectCommand(plr, "Drop", target, tx, ty, target2, data);
	}
	// Update selection & toggle status
  //UpdateSelectionToggleStatus();
  // Apply to all selected crew members (in cursor range) except pTarget.
	// Set, Add, Append mode flags may be combined and have a priority order.

	var i, crew, cursor=GetCursor(plr), cursor_processed;
// FIXME: whole crew movement is bad
//	while (crew = GetCrew(plr, i++))
//	{
//		if (crew==cursor) cursor_processed = true;
//		//if (crew->GetObjectVal("Select"))
//		{
//			if ((mode & C4P_Command_Range) && (!cursor || !Inside(crew->GetX()-cursor->GetX(),-15,+15) || !Inside(crew->GetY()-cursor->GetY(),-15,+15))) continue;
//			if (crew != target)
//			{
//				// Put command with unspecified put object
//				if (cmd == "Put" && !target)
//				{
//					// Special: the put command is only applied by this function if the clonk actually
//					// has something to put. Also, the put count is adjusted to that the clonk will not try to put
//					// more items than he actually has. This workaround is needed so the put command can be used
//					// to tell all selected clonks to put when in a container, simulating the old all-throw behavior.
//					if (crew->ContentsCount(data))
//						ObjectCommand2Obj(crew, cmd, target, Min(tx, crew->ContentsCount(data)), ty, target2, data, mode);
//				}
//				// Other command
//				else
//					ObjectCommand2Obj(crew, cmd, target, tx,ty, target2, data, mode);
//				// don't issue multiple Construct-commands - store previous Clonk as target for next command object
//				// note that if three Clonks get the command, and the middle one gets deleted (the Clonk, not the command), the third will start to build anyway
//				// that is very unlikely, though...could be catched in ClearPointers, if need be?
//				// also, if one Clonk of the chain aborts his command (controlled elsewhere, for instance), the following ones will fail their commands
//				// It's not a perfect solution, after all. But certainly better than placing tons of construction sites in the first place
//				if (cmd == "Construct") target = crew;
//			}
//		}
//	}
	// Always apply to cursor, even if it's not in the crew
	if (cursor && !cursor_processed && cursor != target)
		ObjectCommand2Obj(cursor, cmd, target, tx, ty, target2, data, mode);

	// Success
	return true;
}

func ObjectCommand2Obj(object obj, string cmd, object target, int tx, int ty, object target2, data, int mode)
{

	if (cmd == "Throw" && Contents() != nil) // standard throw!!
	{
		if(!Contained())
		{
			  // Erstes Inhaltsobjekt werfen
			  var throwTarget = Contents();
			  // Wurfparameter berechnen
			  var iXDir, iYDir;

			  iXDir = 50000 / 25000; if(!GetDir()) iXDir = -iXDir;
			  iYDir = -50000 / 25000;

			  // Reitet? Eigengeschwindigkeit addieren
			  if (GetActionTarget())
			  {
				iXDir += GetActionTarget()->GetXDir() / 10;
				iYDir += GetActionTarget()->GetYDir() / 10;
			  }

			return ControlThrow(throwTarget, iXDir, iYDir);
		}
	}

	// forward to object
	if (mode & C4P_Command_Append) return obj->AppendCommand(cmd,target,tx,ty,target2,0,data,0,C4CMD_Base); // append: by Shift-click and for dragging of multiple objects (all independant; thus C4CMD_Mode_Base)
	else if (mode & C4P_Command_Add) return obj->AddCommand(cmd,target,tx,ty,target2,0,data,0,C4CMD_Base); // append: by context menu and keyboard throw command (all independant; thus C4CMD_Mode_Base)
	else if (mode & C4P_Command_Set) return obj->SetCommand(cmd,target,tx,ty,target2,data);
	return false;
}

func CON2Name(int ctrl)
{

	return Format("CON_%s", CON2NameNoCon(ctrl));
//	if (ctrl & CON_Single)
//		return Format("CON_%sSingle", GetConstantNameByValue(ctrl & ~CON_Single, "CON_"));
//	else if (ctrl & CON_Double)
//		return Format("CON_%sDouble", GetConstantNameByValue(ctrl & ~CON_Double, "CON_"));
//	else
//		return Format("CON_%s", GetConstantNameByValue(ctrl, "CON_"));
}

func CON2NameNoCon(int ctrl)
{
	if (ctrl & CON_Single)
		return Format("%sSingle", GetConstantNameByValue(ctrl & ~CON_Single, "CON_"));
	else if (ctrl & CON_Double)
		return Format("%sDouble", GetConstantNameByValue(ctrl & ~CON_Double, "CON_"));
	else
		return Format("%s", GetConstantNameByValue(ctrl, "CON_"));
}

// Controls redirected to script
private func Control2Script(int ctrl, int x, int y, int strength, bool repeat, bool release, object obj)
{
		var control = "Control";
		if (Contained() == obj) control = "Contained";

		if (release)
		{
			// if any key has been released, ControlStop is called
			if (obj->Call(Format("~%sStop",control),this,ctrl))  return true;
		}
		else
		{
			// what about deadzone?
			if (strength != nil && strength < CON_Gamepad_Deadzone)
				return true;

			// Control*
			if (obj->Call(Format("~%s%s",control, CON2NameNoCon(ctrl)),this))  return true;
		}
}

// Handles push controls
private func ObjectControlPush(int plr, int ctrl)
{
	if (!this) return false;
	
	var proc = GetProcedure();
	
	// grabbing
	if (ctrl == CON_Grab)
	{
		// grab only if he walks
		if (proc != "WALK") return false;
		
		// only if there is someting to grab
		var obj = FindObject(Find_OCF(OCF_Grab), Find_AtPoint(0,0), Find_Exclude(this), Find_Layer(GetObjectLayer()));
		if (!obj) return false;
		
		// grab
		ObjectCommand("Grab", obj);
		return true;
	}
	
	// grab next/previous
	if (ctrl == CON_GrabNext)
		return ShiftVehicle(plr, false);
	if (ctrl == CON_GrabPrevious)
		return ShiftVehicle(plr, true);
	
	// ungrabbing
	if (ctrl == CON_Ungrab)
	{
		// ungrab only if he pushes
		if (proc != "PUSH") return false;
		
		// vehicles might have set their own view and it's not reset on release controls
		// So reset cursor view immediately when ungrabbing
		ResetCursorView(GetController());

		ObjectCommand("UnGrab");
		return true;
	}
	
	// push into building
	if (ctrl == CON_PushEnter)
	{
		if (proc != "PUSH") return false;
		
		// respect no push enter
		if (GetActionTarget()->GetDefCoreVal("NoPushEnter","DefCore")) return false;
		
		// a building with an entrance at right position is there?
		var obj = GetActionTarget()->GetEntranceObject();
		if (!obj) return false;

		ObjectCommand("PushTo", GetActionTarget(), 0, 0, obj);
		return true;
	}
	
}

// grabs the next/previous vehicle (if there is any)
private func ShiftVehicle(int plr, bool back)
{
	if (!this) return false;
	
	if (GetProcedure() != "PUSH") return false;

	var lorry = GetActionTarget();
	// get all grabbable objects
	var objs = FindObjects(Find_OCF(OCF_Grab), Find_AtPoint(0,0), Find_Exclude(this), Find_Layer(GetObjectLayer()));
		
	// nothing to switch to (there is no other grabbable object)
	if (GetLength(objs) <= 1) return false;
		
	// find out at what index of the array objs the vehicle is located
	var index = 0;
	for(var obj in objs)
	{
		if (obj == lorry) break;
		index++;
	}
		
	// get the next/previous vehicle
	if (back)
	{
		--index;
		if (index < 0) index = GetLength(objs)-1;
	}
	else
	{
		++index;
		if (index >= GetLength(objs)) index = 0;
	}
	
	ObjectCommand("Grab", objs[index]);
	
	return true;
}

// Handles enter and exit
private func ObjectControlEntrance(int plr, int ctrl)
{
	// enter
	if (ctrl == CON_Enter)
	{
		// contained
		if (Contained()) return false;
		// enter only if... one can
		if (!CanEnter()) return false;

		// a building with an entrance at right position is there?
		var obj = GetEntranceObject();
		if (!obj) return false;
		
		ObjectCommand("Enter", obj);
		return true;
	}
	
	// exit
	if (ctrl == CON_Exit)
	{
		if (!Contained()) return false;
		
		ObjectCommand("Exit");
		return true;
	}
	
	return false;
}
