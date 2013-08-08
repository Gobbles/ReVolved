#include "Character.h"

Script::Script(std::shared_ptr<Character> _character)
{
	character = _character;
}

Script::~Script()
{
}

//void Script::DoScript(int animIdx, int KeyFrameIdx)
//{
//	std::shared_ptr<Animations> animations = character->charDef->animations[animIdx];
//	std::shared_ptr<KeyFrame> keyFrame = animations->keyFrames[KeyFrameIdx];
//
//	bool done = false;
//
//	for(int i = 0; i < keyFrame->scripts.size(); i++)
//	{
//		if(done)
//			break;
//		else
//		{
//			std::shared_ptr<ScriptLine> line = keyFrame->scripts[i];
//			if(line != NULL)
//			{
//				switch(line->command)
//				{
//					case SetAnim:
//						character->SetAnim(line->sParam);
//						break;
//					case Goto:
//						character->AnimFrame = line->iParam;
//						done = true;
//						break;
//					case IfUpGoto:
//						if(character->keyUp)
//						{
//							character->AnimFrame = line->iParam;
//							done = true;
//						}
//						break;
//					case IfDownGoto:
//						if(character->keyDown)
//						{
//							character->AnimFrame = line->iParam;
//							done = true;
//						}
//						break;
//					case Float:
//						character->floating = true;
//						break;
//					case UnFloat:
//						character->floating = false;
//						break;
//					case Slide:
//						character->Slide(line->iParam);
//						break;
//					case Backup:
//						character->Slide(-line->iParam);
//						break;
//					case SetJump:
//						character->SetJump(line->iParam);
//						break;
//					case JoyMove:
//						if(character->keyLeft)
//							character->Trajectory->x = -character->speed;
//						else if(character->keyRight)
//							character->Trajectory->x = character->speed;
//						break;
//					case ClearKeys:
//						character->PressedKey = Nokey;
//						break;
//					case SetUpperGoto:
//						character->GoToGoal[Upper] = line->iParam;
//						break;
//					case SetLowerGoto:
//						character->GoToGoal[Upper] = line->iParam;
//						break;
//					case SetAtkGoto:
//						character->GoToGoal[Upper] = line->iParam;
//						break;
//					case SetAnyGoto:
//                        character->GoToGoal[Upper] = line->iParam;
//                        character->GoToGoal[Lower] = line->iParam;
//                        character->GoToGoal[Attack] = line->iParam;
//                        break;
//                    case SetSecondaryGoto:
//                        character->GoToGoal[Secondary] = line->iParam;
//                        character->GoToGoal[SecUp] = line->iParam;
//                        character->GoToGoal[SecDown] = line->iParam;
//						break;
//					case SetSecUpGoto:
//                        character->GoToGoal[SecUp] = line->iParam;
//                        break;
//                    case SetSecDownGoto:
//						character->GoToGoal[SecDown] = line->iParam;
//						break;
//				}
//			}
//		}
//	}
//}