#pragma once
#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifdef WIN32    // включения Windows
#include <Windows.h>
#include <process.h>
#define sleep(x) Sleep(1000*x)
HANDLE handle;
#else    // включения POSIX
#include <pthread.h>
pthread_t mythread;
#endif

void ThreadProc(void*);

#define NUM_ARGUMENTS 5
typedef struct
{
    int argc;
    char* argv[NUM_ARGUMENTS];
} CMD_LINE_STRUCT;

int main(int argc, char* argv[])
{
    int i;
    CMD_LINE_STRUCT cmd;
    pthread_t mythread;

    cmd.argc = argc;
    for (i = 0; i < NUM_ARGUMENTS; i++)
    {
        cmd.argv[i] = argv[i];
    }

    if (argc < 3)
    {
        fprintf(stderr,
            "Usage: call python_filename function_name [args]\n");
        return 1;
    }

    // создать поток
#ifdef WIN32
    // код Windows
    handle = (HANDLE)_beginthread(ThreadProc, 0, &cmd);
#else
    // код POSIX
    pthread_create(&mythread, NULL,
        ThreadProc, (void*)&cmd);
#endif

    // произвольный тестовый код
    for (i = 0; i < 10; i++)
    {
        printf("Printed from the main thread.\n");
        sleep(1);
    }

    printf("Main Thread waiting for My Thread to complete...\n");

    // присоединить и ждать завершения созданного потока...
#ifdef WIN32
    // код Windows
    WaitForSingleObject(handle, INFINITE);
#else
    // код POSIX
    pthread_join(mythread, NULL);
#endif

    printf("Main thread finished gracefully.\n");

    return 0;
}

void ThreadProc(void* data)
{
    int i;
    PyObject* pName, * pModule, * pDict,
        * pFunc, * pInstance, * pArgs, * pValue;
    PyThreadState* mainThreadState, * myThreadState, * tempState;
    PyInterpreterState* mainInterpreterState;

    CMD_LINE_STRUCT* arg = (CMD_LINE_STRUCT*)data;

    // произвольный тестовый код
    for (i = 0; i < 15; i++)
    {
        printf("...Printed from my thread.\n");
        sleep(1);
    }

    // инициализировать интерпретатор python
    Py_Initialize();

    // инициализировать поддержку потоков
    PyEval_InitThreads();

    // сохранить указатель на главный объект PyThreadState
    mainThreadState = PyThreadState_Get();

    // получить ссылку на PyInterpreterState
    mainInterpreterState = mainThreadState->interp;

    // создать объект состояния потока для этого потока
    myThreadState = PyThreadState_New(mainInterpreterState);

    // снять глобальную блокировку
    PyEval_ReleaseLock();

    // получить глобальную блокировку
    PyEval_AcquireLock();

    // загрузить мое состояние потока
    tempState = PyThreadState_Swap(myThreadState);

    // выполнить некоторый код python (вызвать функции python)
    pName = PyString_FromString(arg->argv[1]);
    pModule = PyImport_Import(pName);

    // pDict и pFunc – заимствованные ссылки
    pDict = PyModule_GetDict(pModule);
    pFunc = PyDict_GetItemString(pDict, arg->argv[2]);

    if (PyCallable_Check(pFunc))
    {
        pValue = PyObject_CallObject(pFunc, NULL);
    }
    else {
        PyErr_Print();
    }

    // возврат ресурсов системе
    Py_DECREF(pModule);
    Py_DECREF(pName);

    // выгрузить текущий поток
    PyThreadState_Swap(tempState);

    // снять глобальную блокировку
    PyEval_ReleaseLock();

    // очистить состояние потока
    PyThreadState_Clear(myThreadState);
    PyThreadState_Delete(myThreadState);

    Py_Finalize();
    printf("My thread is finishing...\n");

    // выход из потока
#ifdef WIN32
    // код Windows
    _endthread();
#else
    // код POSIX
    pthread_exit(NULL);
#endif
}