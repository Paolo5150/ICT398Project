#include "pch.h"
#include "AffordanceObject.h"
#include "Affordance.h"
#include "AffordanceManager.h"


AffordanceObject::AffordanceObject(GameObject* go) {
	gameObject = go;
};

void AffordanceObject::AddPerceviedAffordance(Affordance* a)
{
perceivedAffordances[a->GetType()].insert(std::unique_ptr<Affordance>(a));
AffordanceManager::Instance().RegisterAffordanceObject(this);

}
