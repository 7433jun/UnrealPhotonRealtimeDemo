// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "demo_particle_common/LoadBalancingListener.h"
#include "GameFramework/Actor.h"
#include "PhotonLBClient.generated.h"

/**
 * 
 */
UCLASS()
class APhotonLBClient : public AActor, public BaseView
{
	GENERATED_UCLASS_BODY()
	void BeginPlay(void);
	void EndPlay(const EEndPlayReason::Type EndPlayReason);
	void Tick(float DeltaSeconds);
public:
	~APhotonLBClient(void);

	// Demo BaseView overrides (View implementation).
	UFUNCTION(BlueprintImplementableEvent, Category = "Demo")
	void initPlayers();

	// Some of the overrides used as events in UE blueprints directly with only ints replaced with int32s since int is unsupported by UFUNCTION.
	UFUNCTION(BlueprintImplementableEvent, Category = "Demo")
	void removePlayer(int32 playerNr);
	UFUNCTION(BlueprintImplementableEvent, Category = "Demo")
	void changePlayerPos(int32 playerNr, int32 x, int32 y);
	UFUNCTION(BlueprintImplementableEvent, Category = "Demo")
	void setupScene(int32 gridSize);

	// Other overrides wrap UE events for conversion of parameters to FString or FColor.
	virtual void changePlayerColor(int32 playerNr, int32 col)
	{
		changePlayerColor(playerNr, FColor(uint8(col >> 16), uint8(col >> 8), uint8(col), uint8(col >> 24)));
	}
	UFUNCTION(BlueprintImplementableEvent, Category = "Demo")
	void changePlayerColor(int32 playerNr, FColor col);

	virtual void updateState(int state, const ExitGames::Common::JString& stateStr, const ExitGames::Common::JString& joinedRoomName)
	{
		updateState(state, FString(stateStr.UTF8Representation().cstr()), FString(joinedRoomName.UTF8Representation().cstr()));
	}
	UFUNCTION(BlueprintImplementableEvent, Category = "Demo")
	void updateState(int32 state, const FString& stateStr, const FString& joinedRoomName);

	virtual void addPlayer(int playerNr, const ExitGames::Common::JString& playerName, bool local)
	{ 
		addPlayer(playerNr, FString(playerName.UTF8Representation().cstr()), local);
	}
	UFUNCTION(BlueprintImplementableEvent, Category = "Demo")
	void addPlayer(int32 playerNr, const FString& playerName, bool local);

	virtual void updateRoomList(const ExitGames::Common::JVector<ExitGames::Common::JString>& roomNames)
	{
		TArray<FString> a;
		for(unsigned int i=0; i<roomNames.getSize(); ++i)
			a.Push(FString(roomNames[i].UTF8Representation().cstr()));
		updateRoomList(a);
	}
	UFUNCTION(BlueprintImplementableEvent, Category = "Demo")
	void updateRoomList(const TArray<FString>& roomNames);

	// end of Demo BaseView overrrides 

	// Exposing demo properties to blueprint 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Demo)
//	bool gridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
	FString serverAddress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
	FString AppID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
	FString appVersion;

	// Exposing demo methods to blueprint 
	UFUNCTION(BlueprintCallable, Category = "Demo")
	void RandomizeColor();
	UFUNCTION(BlueprintCallable, Category = "Demo")
	void NextGridSize();
	UFUNCTION(BlueprintCallable, Category = "Demo")
	void NewGame();
	UFUNCTION(BlueprintCallable, Category = "Demo")
	void Leave();
	UFUNCTION(BlueprintCallable, Category = "Demo")
	void JoinRoom(FString gameId);
	UFUNCTION(BlueprintCallable, Category = "Demo")
	void SetLocalPlayerPos(int32 x, int32 y);
	UFUNCTION(BlueprintCallable, Category = "Demo")
	bool GetAutomove() const;
	UFUNCTION(BlueprintCallable, Category = "Demo")
	void SetAutomove(bool automove);
	UFUNCTION(BlueprintCallable, Category = "Demo")
	bool GetUseGroups() const;
	UFUNCTION(BlueprintCallable, Category = "Demo")
	void SetUseGroups(bool useGroups);

	// Util
	UFUNCTION(BlueprintCallable, Category = "Demo")
	bool IsInLobby() const;
	UFUNCTION(BlueprintCallable, Category = "Demo")
	bool IsInRoom() const;

private:
	UPROPERTY(EditAnywhere, BlueprintGetter=GetAutomove, Category = "Demo")
	bool automove;
	UPROPERTY(EditAnywhere, BlueprintGetter=GetUseGroups, Category = "Demo")
	bool useGroups;

	void PostEditChangeProperty(struct FPropertyChangedEvent& e);

	LoadBalancingListener* mpListener;
	ExitGames::LoadBalancing::Client* mpClient;
};