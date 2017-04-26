
#pragma once

#include <SDKDDKVer.h>
#include <future>
#include <thread>
#include <vector>
#include <cstdint>
#include <windows.h>
#include "SList.h"
#include "Vector.h"
#include "Hashmap.h"
#include "HashFunction.h"
#include "RTTI.h"
#include "XMLParseHelper.h"
#include "XMLParseMaster.h"
#include "XMLTableParser.h"
#include "ScopeSharedData.h"

#include "GameTime.h"
#include "WorldState.h"
#include "Factory.h"
#include "Action.h"
#include "ActionList.h"
#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionListIf.h"

#include "EventSubscriber.h"
#include "EventPublisher.h"
#include "Event.h"
#include "EventQueue.h"

#include "Reaction.h"
#include "EventMessage.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"

//#include "Attributed.h"
#include <assert.h>
