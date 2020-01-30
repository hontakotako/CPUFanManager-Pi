// raspberryPi CPU CoolingFan Power Manager
// 2018 hontako

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>

#define BUF_SIZE 10
#define CPUFAN_PINID 1
#define FP_OFFSET_TOP 0

volatile sig_atomic_t signalFlag = 0;

void abort_handler( int signal )
{
	signalFlag = 1;
}

int main( void )
{
	FILE *fp;
	const char *filename = "/sys/class/thermal/thermal_zone0/temp";
	char buf[BUF_SIZE+1];

	wiringPiSetup();
	pinMode( CPUFAN_PINID , PWM_OUTPUT );
	pwmSetMode( PWM_MODE_BAL );
	pwmSetClock( 1 );
	pwmSetRange( 1024 );

	fp = fopen( filename , "r" );
	if( fp == NULL )
	{
		printf( "System temp file open failed...\n" );
		return EXIT_FAILURE;
	}

	if( signal( SIGINT , abort_handler ) == SIG_ERR )
	{
		printf( "Signal handler regist failed...\n" );
		return EXIT_FAILURE;
	}

	pwmWrite( 1 , 1023 );
	delay( 2000 );

	while( !signalFlag )
	{
		int rc;
		int cpuTemp;

		rc = fread( buf , 1 , BUF_SIZE , fp );
		fseek( fp ,  FP_OFFSET_TOP , SEEK_SET );
		if( rc == 0 )
		{
			printf( "notiong read data.\n" );
		}
		else
		{
			buf[rc] = '\0';
			printf( "CPUTEMP:%s\n" , buf );
			sscanf( buf , "%d" , &cpuTemp );
		}

		if( cpuTemp > 45000 )
		{
			// digitalWrite(  CPUFAN_PINID , HIGH );
			pwmWrite( 1 , 1023 );
		}
		else if( cpuTemp > 40000 )
		{
			// digitalWrite(  CPUFAN_PINID , LOW );
			pwmWrite( 1 , 850 );
		}
		else
		{
			pwmWrite( 1 , 512 );
		}

		delay( 10000 );
		/*digitalWrite(  CPUFAN_PINID , HIGH );
		delay( 500 );
		digitalWrite(  CPUFAN_PINID , LOW );
		delay( 500 );*/
	}

	fclose( fp );
	printf( "EXIT.\n" );
	pinMode( CPUFAN_PINID , OUTPUT );
	digitalWrite( CPUFAN_PINID , LOW );

	return EXIT_SUCCESS;
}
