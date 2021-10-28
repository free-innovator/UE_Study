// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	HitTimeSeconds = 0.f;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetCollisionProfileName("PhysicsActor");
	StaticMeshComp->SetSimulatePhysics(true);
	RootComponent = StaticMeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(StaticMeshComp);
	
	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 2500.0f;
	ForceComp->bImpulseVelChange = true;
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);	
	ForceComp->SetAutoActivate(false);
}

void ASExplosiveBarrel::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	// Blocking Hit
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if(Cast<ASCharacter>(Other)) return;
	Explosion(*Other, FString(L"NotifyHit"));
}

void ASExplosiveBarrel::DispatchPhysicsCollisionHit(const FRigidBodyCollisionInfo& MyInfo, const FRigidBodyCollisionInfo& OtherInfo, const FCollisionImpactData& RigidCollisionData)
{
	// Physics Hit
	// Super::DispatchPhysicsCollisionHit(MyInfo, OtherInfo, RigidCollisionData);
	Explosion(*OtherInfo.Actor, FString(L"DispatchPhysicsCollisionHit"));
}

void ASExplosiveBarrel::Explosion(const AActor& OtherActor, FString String)
{
	if(HitTimeSeconds == GetWorld()->TimeSeconds) return;
	if(OtherActor.GetFName().ToString().Equals(TEXT("Floor"))) return;

	HitTimeSeconds = GetWorld()->TimeSeconds;
	
	UKismetSystemLibrary::PrintString(GetWorld(), FString(L"Explosion!!!"));
	UE_LOG(LogTemp, Warning, TEXT("ASExplosiveBarrel::%s> OtherActor: %s, at game time: %f" ), *String, *OtherActor.GetFName().ToString(), HitTimeSeconds);
	ForceComp->FireImpulse();
		
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor.GetComponentByClass(USAttributeComponent::StaticClass()));
	if(AttributeComp)
	{
		AttributeComp->ApplyHealthChange(-30.f);
		UE_LOG(LogTemp, Warning, TEXT("Call SExplosiveBarrel ApplyHealthChange"));
	}
}

void ASExplosiveBarrel::PostInitProperties()
{
	Super::PostInitProperties();
	// FPhysicsDelegates::OnPhysDispatchNotifications.AddUFunction(this, FName("OnPhysDispatchNotifications"));
}

// void USceneComponent::EndScopedMovementUpdate(class FScopedMovementUpdate& CompletedScope)
// {
// 	
// }