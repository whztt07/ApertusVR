#include "ApeRadioButtonImpl.h"

Ape::RadioButtonImpl::RadioButtonImpl(std::string name, bool isHostCreated) : Ape::Replica("RadioButton", isHostCreated)
{
	mpEventManagerImpl = ((Ape::EventManagerImpl*)Ape::IEventManager::getSingletonPtr());
	mpEventManager = Ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(Ape::Event::Group::NODE, std::bind(&RadioButtonImpl::eventCallBack, this, std::placeholders::_1));
	mpScene = Ape::IScene::getSingletonPtr();
	mName = name;
}

Ape::RadioButtonImpl::~RadioButtonImpl()
{
}

void Ape::RadioButtonImpl::eventCallBack(const Ape::Event& event)
{

}

std::string Ape::RadioButtonImpl::getName() const
{
	return mName;
}

void Ape::RadioButtonImpl::WriteAllocationID(RakNet::Connection_RM3 * destinationConnection, RakNet::BitStream * allocationIdBitstream) const
{
}

RakNet::RM3SerializationResult Ape::RadioButtonImpl::Serialize(RakNet::SerializeParameters * serializeParameters)
{
	return RakNet::RM3SerializationResult();
}

void Ape::RadioButtonImpl::Deserialize(RakNet::DeserializeParameters * deserializeParameters)
{
}
