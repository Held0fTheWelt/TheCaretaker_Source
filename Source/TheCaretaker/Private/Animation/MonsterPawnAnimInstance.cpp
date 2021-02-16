/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "MonsterPawnAnimInstance.h"

void UMonsterPawnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(TryGetPawnOwner()))
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}
