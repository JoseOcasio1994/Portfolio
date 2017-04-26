
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
#include "Datum.h"
#include "XMLParseHelper.h"
#include "XMLParseMaster.h"
#include "ScopeSharedData.h"
#include "Factory.h"
#include "RTTI.h"
#include <assert.h>

#include "WorldState.h"
#include "Factory.h"
#include "Entity.h"
#include "Sector.h"
#include "World.h"

#include "EventSubscriber.h"
#include "EventPublisher.h"
#include "Event.h"
#include "EventQueue.h"

#include "Reaction.h"
#include "EventMessage.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"

#include "Foo.h"
#include "FooAction.h"
#include "FooEntity.h"
#include "FooMacro.h"
#include "FooFactory.h"
#include "FooXMLHelper.h"
#include "FooSharedData.h"
#include "FooScopeData.h"
#include "FooMessage.h"
#include "FooSubscriber.h"
#include "FooSubscriberEnqueue.h"
#include "FooSubscriberClearQ.h"
#include "FooSubscriberException.h"
#include "FooSubscriberUnsub.h"
#include "FooSubscriberSub.h"
