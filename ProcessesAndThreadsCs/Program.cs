using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace ProcessesAndThreadsCs
{
	internal class Program
	{
		private static Mutex mtx = new Mutex();
		private static bool finish = false;
		static void Main(string[] args)
		{
			Thread threadPlus = new Thread(Plus);
			Thread threadMinus = new Thread(Minus);
			threadPlus.Start();
			threadMinus.Start();
			Console.ReadKey();
			finish = true;
		}
		static void Plus()
		{
			while (!finish)
			{
				mtx.WaitOne();
				Console.Write("+ ");
				Thread.Sleep(100);
				mtx.ReleaseMutex();
			}
		}
		static void Minus()
		{
			while (!finish)
			{
				mtx.WaitOne();
				Console.Write("- ");
				Thread.Sleep(100);
				mtx.ReleaseMutex();
			}
		}
	}
}
