// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PhotonDemoParticleTarget : TargetRules
{
	public PhotonDemoParticleTarget(TargetInfo Target) : base(Target)
    {
		bOverrideBuildEnvironment = true;
		Type = TargetType.Game;
		ExtraModuleNames.Add("PhotonDemoParticle");
    }
}
