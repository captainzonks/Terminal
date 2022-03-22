// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "TDirectoryVolume.generated.h"

class ATBaseCharacter;
/**
 * 
 */
UCLASS()
class TERMINAL_API ATDirectoryVolume : public AVolume
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATDirectoryVolume();
	void AddToParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	ATBaseCharacter* LinkedDirectoryActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	ATBaseCharacter* LinkedParentDirectory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
	TArray<TObjectPtr<ATBaseCharacter>> CurrentOverlappingCharacters;

	bool bHasSetupDirectoryLinks{false};
};
