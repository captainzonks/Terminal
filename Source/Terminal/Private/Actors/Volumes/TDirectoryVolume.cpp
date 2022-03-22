// © 2022, Matthew Barham. All rights reserved.


#include "Actors/Volumes/TDirectoryVolume.h"
#include "Characters/TBaseCharacter.h"
#include "Terminal/Terminal.h"

ATDirectoryVolume::ATDirectoryVolume()
{
}

void ATDirectoryVolume::AddToParent()
{
	FTimerHandle TimerToUpdate;
	GetWorld()->GetTimerManager().SetTimer(TimerToUpdate, [this]()
	{
		if (LinkedParentDirectory && LinkedDirectoryActor && !bHasSetupDirectoryLinks)
		{
			LinkedParentDirectory->GetFileDataComponent()->ModifyFileData()->AddFilesToDirectory(*LinkedDirectoryActor);

			bHasSetupDirectoryLinks = true;
			UE_LOG(LogTerminal, Log, TEXT("Linking directory actor to parent directory"))
		}
	}, 5.f, false, 0.7f);
}

void ATDirectoryVolume::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	if (!LinkedDirectoryActor)
	{
		FMessageLog("PIE").Error(
			FText::FromString("TDirectoryVolume expects a valid file actor as 'LinkedDirectoryActor' target"));
	}
#endif // WITH_EDITOR

	AddToParent();
}

void ATDirectoryVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogTerminal, Log, TEXT("TDirectoryVolume overlapped"))

#if WITH_EDITOR
	if (!LinkedDirectoryActor)
	{
		FMessageLog("PIE").Error(
			FText::FromString("TDirectoryVolume expects a valid file actor as 'LinkedDirectoryActor' target"));
		return;
	}
#endif // WITH_EDITOR

	if (ATBaseCharacter* Character = Cast<ATBaseCharacter>(OtherActor))
	{
		if (Character->GetFileDataComponent()->GetFileData()->GetIsDirectory())
		{
			Character->GetFileDataComponent()->ModifyFileData()->SetParentDirectory(LinkedParentDirectory);
			for (TObjectPtr<ATBaseCharacter> OverlappingCharacter : CurrentOverlappingCharacters)
			{
				Character->GetFileDataComponent()->ModifyFileData()->GetLinkedFiles().AddUnique(OverlappingCharacter);
			}
		}
		else
		{
			Character->GetFileDataComponent()->ModifyFileData()->SetParentDirectory(LinkedDirectoryActor);
			CurrentOverlappingCharacters.AddUnique(Character);
			if (LinkedDirectoryActor)
			{
				LinkedDirectoryActor->GetFileDataComponent()->ModifyFileData()->SetLinkedFiles(
					CurrentOverlappingCharacters);;
			}
		}
	}
}

void ATDirectoryVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}
