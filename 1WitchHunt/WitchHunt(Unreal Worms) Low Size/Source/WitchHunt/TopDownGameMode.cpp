// THIS CLASS IS FOR TESTING PURPOSES ONLY, FOR ACTUAL GAMEMODE SEE BP_WaveGameMode
// THIS CLASS IS FOR TESTING PURPOSES ONLY, FOR ACTUAL GAMEMODE SEE BP_WaveGameMode
// THIS CLASS IS FOR TESTING PURPOSES ONLY, FOR ACTUAL GAMEMODE SEE BP_WaveGameMode

#include "TopDownGameMode.h"
#include "TopDownPlayerController.h"
#include "TopDownCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopDownGameMode::ATopDownGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_TopDownCharacter")); // set file as default player class
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_TopDownPlayerController")); // set as default player controller
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
