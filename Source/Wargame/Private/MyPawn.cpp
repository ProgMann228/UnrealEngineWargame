// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "Camera/CameraComponent.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		Mesh->SetStaticMesh(CubeVisualAsset.Object);
		Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 800.f));
	Camera->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f)); 
	Camera->bUsePawnControlRotation = false; 

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsNearlyZero())
	{
		SetActorLocation(GetActorLocation() + CurrentVelocity * DeltaTime);
	}

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveHorizontal", this, &AMyPawn::MoveHorizontal);
	PlayerInputComponent->BindAxis("MoveVertical", this, &AMyPawn::MoveVertical);
}

void AMyPawn::MoveHorizontal(float Value)
{
	CurrentVelocity.X = Value * MoveSpeed;
}

void AMyPawn::MoveVertical(float Value)
{
	CurrentVelocity.Y = Value * MoveSpeed;
}



