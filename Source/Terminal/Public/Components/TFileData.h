// © 2022, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Terminal/Terminal.h"
#include "TFileData.generated.h"

/** Permission types */
UENUM(BlueprintType)
enum class EPermissions : uint8
{
	None,
	Read,
	Write,
	Execute
};

class ATBaseCharacter;
/** Group data */
USTRUCT(BlueprintType)
struct TERMINAL_API FGroup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText GroupName{FText::FromString("group")};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATBaseCharacter*> GroupMembers{};
};

/** Data for a file's permissions settings */
USTRUCT(BlueprintType)
struct TERMINAL_API FPermissionsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText User{FText::FromString("user")};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPermissions> UserPermissions{EPermissions::Read, EPermissions::Write, EPermissions::Execute};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGroup Group{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPermissions GroupPermissions{EPermissions::Read};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPermissions OtherPermissions{EPermissions::None};
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TERMINAL_API UTFileData : public UActorComponent
{
	GENERATED_BODY()

public:
	UTFileData();

	/* Returns FileData for reading */
	UFUNCTION(BlueprintCallable)
	const UTFileData* GetFileData() const { return this; }

	FText GetFileName() const { return FileName; }
	TObjectPtr<ATBaseCharacter> GetParentDirectory() const { return ParentDirectory; }
	FSlateBrush GetFileIcone() const { return FileIcon; }
	FGuid GetID() const { return ID; }
	FText GetContents() const { return Contents; }
	FPermissionsData GetPermissionsData() const { return PermissionsData; }
	bool GetIsExecutable() const { return bExecutable; }
	bool GetIsDirectory() const { return bIsDirectory; }
	TArray<TObjectPtr<ATBaseCharacter>> GetLinkedFiles() const { return LinkedFiles; }

	void SetLinkedFiles(const TArray<TObjectPtr<ATBaseCharacter>> InLinkedFilesArray)
	{
		LinkedFiles = InLinkedFilesArray;
	}

	/* Returns FileData for modification */
	UFUNCTION(BlueprintCallable)
	UTFileData* ModifyFileData()
	{
		UE_LOG(LogTerminal, Log, TEXT("ModifyFileData() called"))
		return this;
	}

	/* Used by DirectoryVolume to set parent directory during overlap event */
	void SetParentDirectory(ATBaseCharacter* InParentDirectory)
	{
		this->ParentDirectory = InParentDirectory;
		UE_LOG(LogTerminal, Log, TEXT("SetParentDirectory() called"))
	}

	/* Used by a DirectoryVolume to add a new file to the LinkedFiles array */
	void AddFilesToDirectory(ATBaseCharacter& InFile)
	{
		if (bIsDirectory)
		{
			LinkedFiles.Add(&InFile);
		}
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText FileName{FText::FromString("new_file")};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATBaseCharacter> ParentDirectory{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush FileIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid ID{FGuid::NewGuid()};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Contents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPermissionsData PermissionsData{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bExecutable{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDirectory{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ATBaseCharacter>> LinkedFiles{};

	bool operator==(const UTFileData& rhs) const
	{
		return (this->ID == rhs.ID);
	}
};
