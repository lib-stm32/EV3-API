#pragma once
#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifdef WIN32    // ��������� Windows
#include <Windows.h>
#include <process.h>
#define sleep(x) Sleep(1000*x)
HANDLE handle;
#else    // ��������� POSIX
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

    // ������� �����
#ifdef WIN32
    // ��� Windows
    handle = (HANDLE)_beginthread(ThreadProc, 0, &cmd);
#else
    // ��� POSIX
    pthread_create(&mythread, NULL,
        ThreadProc, (void*)&cmd);
#endif

    // ������������ �������� ���
    for (i = 0; i < 10; i++)
    {
        printf("Printed from the main thread.\n");
        sleep(1);
    }

    printf("Main Thread waiting for My Thread to complete...\n");

    // ������������ � ����� ���������� ���������� ������...
#ifdef WIN32
    // ��� Windows
    WaitForSingleObject(handle, INFINITE);
#else
    // ��� POSIX
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

    // ������������ �������� ���
    for (i = 0; i < 15; i++)
    {
        printf("...Printed from my thread.\n");
        sleep(1);
    }

    // ���������������� ������������� python
    Py_Initialize();

    // ���������������� ��������� �������
    PyEval_InitThreads();

    // ��������� ��������� �� ������� ������ PyThreadState
    mainThreadState = PyThreadState_Get();

    // �������� ������ �� PyInterpreterState
    mainInterpreterState = mainThreadState->interp;

    // ������� ������ ��������� ������ ��� ����� ������
    myThreadState = PyThreadState_New(mainInterpreterState);

    // ����� ���������� ����������
    PyEval_ReleaseLock();

    // �������� ���������� ����������
    PyEval_AcquireLock();

    // ��������� ��� ��������� ������
    tempState = PyThreadState_Swap(myThreadState);

    // ��������� ��������� ��� python (������� ������� python)
    pName = PyString_FromString(arg->argv[1]);
    pModule = PyImport_Import(pName);

    // pDict � pFunc � �������������� ������
    pDict = PyModule_GetDict(pModule);
    pFunc = PyDict_GetItemString(pDict, arg->argv[2]);

    if (PyCallable_Check(pFunc))
    {
        pValue = PyObject_CallObject(pFunc, NULL);
    }
    else {
        PyErr_Print();
    }

    // ������� �������� �������
    Py_DECREF(pModule);
    Py_DECREF(pName);

    // ��������� ������� �����
    PyThreadState_Swap(tempState);

    // ����� ���������� ����������
    PyEval_ReleaseLock();

    // �������� ��������� ������
    PyThreadState_Clear(myThreadState);
    PyThreadState_Delete(myThreadState);

    Py_Finalize();
    printf("My thread is finishing...\n");

    // ����� �� ������
#ifdef WIN32
    // ��� Windows
    _endthread();
#else
    // ��� POSIX
    pthread_exit(NULL);
#endif
}