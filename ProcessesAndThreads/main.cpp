#include <Windows.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using std::cin;
using std::cout;
using std::endl;
using namespace std::chrono_literals;

bool finish = false;
std::mutex mtx;

HANDLE hMutex = NULL;

void Plus();
void Minus();

//#define CPLUSPLUS_THREADS
#define WINDOWS_THREADS

void main()
{
	setlocale(LC_ALL, "");
	//Plus();
	//Minus();

#ifdef CPLUSPLUS_THREADS
	std::thread plus_thread(Plus);
	std::thread minus_thread(Minus);

	cin.get();		//ожидает нажатие клавиши Enter
	finish = true;

	if (plus_thread.joinable()) plus_thread.join();		//join() присоединяет поток к другому потоку, когда он отключился
	if (minus_thread.joinable()) minus_thread.join();
	if (minus_thread.joinable()) minus_thread.join();
	if (minus_thread.joinable()) minus_thread.join();
#endif // CPLUSPLUS_THREADS

#ifdef WINDOWS_THREADS
	hMutex = CreateMutex(NULL, FALSE, NULL);

	HANDLE hThreads[2] = {};
	hThreads[0] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Plus, NULL, NULL, NULL);
	hThreads[1] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Minus, NULL, NULL, NULL);
	cin.get();
	finish = true;
	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
#endif // WINDOWS_THREADS

}

void Plus()
{
	while (!finish)
	{
		//mtx.lock();		//блокирует ресурсы, другие потоки не могут получать доступ к ресурсам.
#ifdef WINDOWS_THREADS
		WaitForSingleObject(hMutex, INFINITE);
#endif // WINDOWS_THREADS
		{
			//std::lock_guard<std::mutex> lg(mtx);
			cout << "+ ";
		}
#ifdef WINDOWS_THREADS
		Sleep(100);
		ReleaseMutex(hMutex);
#endif // WINDOWS_THREADS

		//std::this_thread::sleep_for(100ms);
		//mtx.unlock();
	}
}
void Minus()
{
	while (!finish)
	{
		//mtx.lock();
#ifdef WINDOWS_THREADS
		WaitForSingleObject(hMutex, INFINITE);
#endif // WINDOWS_THREADS
		{
			//std::lock_guard<std::mutex> lg(mtx);
			cout << "- ";
		}
#ifdef WINDOWS_THREADS
		Sleep(100);
		ReleaseMutex(hMutex);
#endif // WINDOWS_THREADS

		//std::this_thread::sleep_for(100ms);
		//mtx.unlock();
	}
}