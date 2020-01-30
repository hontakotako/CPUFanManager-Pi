cpuFanManager:
		gcc -Wall -o cpuFanManager cpuFanManager.c -lwiringPi

clean:
	rm cpuFanManager
