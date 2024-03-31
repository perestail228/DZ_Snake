#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"


template<typename T, typename TMethod>
class MyTimerManager
{
private:
    MyTimerManager() = delete;
    static TMap<FString, FTimerHandle> TimerHandles; // Словарь "имя функции - TimerHandle"

public:
    ~MyTimerManager();
    static void DelayFunction(T* Object, const FString& FunctionName, float DelayTime, TMethod Method, bool bLoop)
    {
        if (TimerHandles.Contains(FunctionName)) // Проверяем, содержит ли словарь уже данный FunctionName
        {
            return;
        }
        FTimerHandle TimerHandle;
        FTimerDelegate TimerCallback;
        TimerCallback.BindLambda([Object, Method]()
            {
                (Object->*Method)();
            });

        if (Object->GetWorld())
        {
            Object->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerCallback, DelayTime, bLoop);
        }
        if (bLoop)
        {
            TimerHandles.Add(FunctionName, TimerHandle); // Добавляем пару "имя функции - TimerHandle" в словарь
        }
    }

    static void StopDelayFunction(T* Object, const FString& FunctionName)
    {
        if (TimerHandles.Contains(FunctionName))
        {
            FTimerHandle TimerHandle = TimerHandles[FunctionName];
            if (Object->GetWorld())
            {
                Object->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
            }
            TimerHandles.Remove(FunctionName);
        }
    }
};

template<typename T, typename TMethod>
TMap<FString, FTimerHandle> MyTimerManager<T, TMethod>::TimerHandles;

template<typename T, typename TMethod>
MyTimerManager<T, TMethod>::~MyTimerManager()
{
    TimerHandles.Empty();
}
