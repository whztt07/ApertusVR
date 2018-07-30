#include "ApeSelectionImpl.h"

Ape::SelectionImpl::SelectionImpl(std::string name, bool isHostCreated) : Ape::Replica("Node", isHostCreated)
{
	mpEventManagerImpl = ((Ape::EventManagerImpl*)Ape::IEventManager::getSingletonPtr());
	mpScene = Ape::IScene::getSingletonPtr();
}

std::string Ape::SelectionImpl::getName()
{
	return mName;
}

std::vector<Ape::NodeWeakPtr> Ape::SelectionImpl::getNodes()
{
	std::vector<Ape::NodeWeakPtr> nodes;

	auto nodeIt = mSelectedNodes.begin();
	while (nodeIt != mSelectedNodes.end())
	{
		nodes.push_back(nodeIt->second);
	}

	return nodes;
}

std::map<std::string, Ape::NodeWeakPtr> Ape::SelectionImpl::getNodesMap()
{
	return mSelectedNodes;
}

void Ape::SelectionImpl::addNode(std::string nodeName)
{
	if (auto nodeSharedPtr = mpScene->getNode(nodeName).lock())
	{
		Ape::NodeWeakPtrVector childNodes = nodeSharedPtr->getChildNodes();
		LOG_DEBUG("childNodes size: " << childNodes.size());
		for (auto childNode : childNodes)
			if (auto childNodeSP = childNode.lock())
				LOG_DEBUG("childNode: " << childNodeSP->getName());
		mSelectedNodes.insert(std::pair<std::string, Ape::NodeWeakPtr>(nodeSharedPtr->getName(), nodeSharedPtr));
		nodeSharedPtr->showBoundingBox(true);
	}
}

bool Ape::SelectionImpl::removeNode(std::string nodeName)
{
	LOG_TRACE("nodeName: " << nodeName);
	std::map<std::string, Ape::NodeWeakPtr>::iterator findIt;
	findIt = mSelectedNodes.find(nodeName);
	if (findIt != mSelectedNodes.end())
	{
		if (auto findNode = findIt->second.lock())
		{
			findNode->showBoundingBox(false);
			mSelectedNodes.erase(findIt);
			return true;
		}
	}
	return false;
}

void Ape::SelectionImpl::clear()
{
	LOG_TRACE("");
	auto nodeIt = mSelectedNodes.begin();
	while (nodeIt != mSelectedNodes.end())
	{
		if (auto selectedNodeInMap = nodeIt->second.lock())
		{
			selectedNodeInMap->showBoundingBox(false);
			nodeIt = mSelectedNodes.erase(nodeIt);
		}
		else
		{
			++nodeIt;
		}
	}
}
