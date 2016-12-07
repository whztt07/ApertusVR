#include <iostream>
#include "ApeFobHeadTrackingPlugin.h"

ApeFobHeadTrackingPlugin::ApeFobHeadTrackingPlugin()
{
	mpSystemConfig = Ape::ISystemConfig::getSingletonPtr();
	mpEventManager = Ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(Ape::Event::Group::NODE, std::bind(&ApeFobHeadTrackingPlugin::eventCallBack, this, std::placeholders::_1));
	mpScene = Ape::IScene::getSingletonPtr();
	mCameraNode = Ape::NodeWeakPtr();
	mpFobTracker = nullptr;
}

ApeFobHeadTrackingPlugin::~ApeFobHeadTrackingPlugin()
{
	std::cout << "ApeFobHeadTrackingPlugin dtor" << std::endl;
}

void ApeFobHeadTrackingPlugin::eventCallBack(const Ape::Event& event)
{
	if (event.group == Ape::Event::Group::NODE && event.type == Ape::Event::Type::NODE_CREATE && event.subjectName == mpSystemConfig->getSceneSessionConfig().generatedUniqueUserName)
	{
		if (auto node = (mpScene->getNode(event.subjectName).lock()))
			mCameraNode = node;
	}
}

void ApeFobHeadTrackingPlugin::Init()
{
	std::cout << "ApeFobHeadTrackingPlugin::init" << std::endl;
	mpFobTracker = trackdInitTrackerReader(4126);
}

void ApeFobHeadTrackingPlugin::Run()
{
	while (mpFobTracker)
	{
		if (trackdGetPosition(mpFobTracker, 0, pos))
		{

		}
		if (auto cameraNode = mCameraNode.lock())
		{
			
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	mpEventManager->disconnectEvent(Ape::Event::Group::NODE, std::bind(&ApeFobHeadTrackingPlugin::eventCallBack, this, std::placeholders::_1));
}

void ApeFobHeadTrackingPlugin::Step()
{

}

void ApeFobHeadTrackingPlugin::Stop()
{

}

void ApeFobHeadTrackingPlugin::Suspend()
{

}

void ApeFobHeadTrackingPlugin::Restart()
{

}
