// raspberryPi CPU CoolingFan Power Manager
// 2018-2020 hontako

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>

#define BUF_SIZE 10
// "1" is wiringPi pinID. Physical pinNo is 12.
#define CPUFAN_PINID 1
#define FP_OFFSET_TOP 0

#define CPUTEMP_HIGH 45000
#define CPUTEMP_MID 40000

// #define USE_PWM

volatile sig_atomic_t abortFlag = 0;

void abort_handler( int signal )
{
	abortFlag = 1;
}

void initGPIO( void )
{
    wiringPiSetup();
#ifdef USE_PWM
    pinMode( CPUFAN_PINID , PWM_OUTPUT );
	pwmSetMode( PWM_MODE_BAL );
	pwmSetClock( 1 );
	pwmSetRange( 1024 );
#else
    pinMode( CPUFAN_PINID , OUTPUT );
#endif
}

void controlCPUFan( int cpuTemp )
{
#ifdef USE_PWM
	if( cpuTemp > CPUTEMP_HIGH )
	{
		pwmWrite( 1 , 1023 );
	}
	else if( cpuTemp > CPUTEMP_MID )
	{
		pwmWrite( 1 , 850 );
	}
	else
	{
		pwmWrite( 1 , 0 );
	}
#else
    if( cpuTemp > CPUTEMP_HIGH )
    {
        digitalWrite( CPUFAN_PINID , HIGH );
    }
    else
    {
        digitalWrite( CPUFAN_PINID , LOW );
    }
#endif
}

int main( void )
{
	FILE *fp;
	const char *tempFileName = "/sys/class/thermal/thermal_zone0/temp";
	char strbuf[BUF_SIZE+1];

	initGPIO();

	fp = fopen( tempFileName , "r" );
	if( fp == NULL )
	{
		printf( "[ERROR]CPUTemp System file open failed...\n" );
		printf( "Can you access and reading the this file?: /sys/class/thermal/thermal_zone0/temp" );
		return EXIT_FAILURE;
	}

	if( signal( SIGINT , abort_handler ) == SIG_ERR )
	{
		printf( "[ERROR]Signal handler regist failed...\n" );
		printf( "Please restart this program after some time.\n" );
		return EXIT_FAILURE;
	}

#ifdef USE_PWM
	pwmWrite( 1 , 1023 );
#endif
	delay( 2000 );

    // Mainloop
	while( !abortFlag )
	{
		int rc;
		int cpuTemp;

		rc = fread( strbuf , 1 , BUF_SIZE , fp );
		fseek( fp ,  FP_OFFSET_TOP , SEEK_SET );
		if( rc != 0 )
		{
			strbuf[rc] = '\0';
			// printf( "[DEBUG]CPUTEMP:%s\n" , strbuf );
			sscanf( strbuf , "%d" , &cpuTemp );
		}
		/*else
		{
		    printf( "[DEBUG]notiong read data.\n" );
		}*/

        controlCPUFan( cpuTemp );

		delay( 10000 );
	}

	fclose( fp );
	printf( "EXIT.\n" );
	pinMode( CPUFAN_PINID , OUTPUT );
	digitalWrite( CPUFAN_PINID , LOW );

	return EXIT_SUCCESS;
}
