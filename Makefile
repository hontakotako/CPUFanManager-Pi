cpuFanManager:
		gcc -Wall -o cpufm cpuFanManager.c -lwiringPi

clean:
	rm cpufm
