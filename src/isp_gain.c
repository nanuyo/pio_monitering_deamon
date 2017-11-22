#include "snx_isp/isp_lib_api.h"
#include "snx_gpio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
  int pid, ret;
  int val, error, firstflag=1, doset=1, satu;

   gpio_pin_info info;

   snx_gpio_open(0);

   info.pinumber = GPIO_PIN_0;
   info.mode = 0;  // 0: input 1: output

 
   // fork 생성
   pid = fork();
   printf("pid = [%d] \n", pid);
     
 
	// fork 에러 발생 시 로그 남긴 후 종료
	if(pid < 0){
		printf("fork Error... : return is [%d] \n", pid );
		perror("fork error : ");
		exit(0);
	// 부모 프로세스 로그 남긴 후 종료
	}else if (pid > 0){
		printf("child process : [%d] - parent process : [%d] \n", pid, getpid());
		exit(0);
	// 정상 작동시 로그
	}else if(pid == 0){
		printf("process : [%d]\n", getpid());
	}
 
	// 터미널 종료 시 signal의 영향을 받지 않도록 처리
	signal(SIGHUP, SIG_IGN);
	close(0);
	close(1);
	close(2);
 
	// 실행위치를 Root로 변경
	chdir("/");
 
	// 새로운 세션 부여
	setsid();
 
	int cnt = 0;
 
	// 반복 실행이 필요한 코드면 while문 안에 삽입
	while(1) {
		// daemon이 죽었을 경우 다시 실행
		if((pid = fork()) < 0) {
			printf("fork error : restart daemon");
		}else if(pid == 0) {
			break;
		}else if(pid > 0) {
			wait(&ret);
		}
 
		// 10초 마다 체크
		sleep(1);
#if 0
    //for the test
    snx_isp_filter_saturation_set(0);
    sleep(5);
    snx_isp_filter_saturation_set(64); 
    sleep(5); 
#else
    snx_gpio_read(&info);
   // printf ("%d\n",info.value);

	    if(firstflag)
	    {
		firstflag = 0;
		val = info.value;
		snx_isp_filter_saturation_get(&satu); //for mono mode
		doset = 1;
	    }
	    else
	    {
		if(val != info.value)
		{
		    val = info.value;
		    doset = 1;
		}else
		{
		    doset = 0;    
		}
		
	    }
    
	    
		if(doset)
		{
		    if(info.value)
		    {
		        snx_isp_filter_saturation_set(satu);
		        printf("saturation:%d  \n", satu);
		    }
		    else
		    {
		        snx_isp_filter_saturation_set(0); 
		        printf("saturation:%d  \n", 0);   
		    }

		}
#endif

	} //while
}
#if 0
int check_pio0(void)
{
   int val, newval, error, firstflag=1, doset=1, satu, new_exp_time;

   gpio_pin_info info;

   snx_gpio_open(0);

   info.pinumber = GPIO_PIN_0;
   info.mode = 0;  // 0: input 1: output

//    while(1)
    {

    snx_gpio_read(&info);
  //  sleep(1);
    
    printf ("%d\n",info.value);

    if(firstflag)
    {
        firstflag = 0;
        val = info.value;
        snx_isp_filter_saturation_get(&satu); //for mono mode
        doset = 1;
    }
    else
    {
        if(val != info.value)
        {
            val = info.value;
            doset = 1;
        }else
        {
            doset = 0;    
        }
        
    }
    
    
        if(doset)
        {
            if(info.value)
            {
                snx_isp_filter_saturation_set(satu);
                printf("saturation:%d  \n", satu);
            }
            else
            {
                snx_isp_filter_saturation_set(0); 
                printf("saturation:%d  \n", 0);   
            }

        }

    }

	
	//snx_gpio_close();

    return;
}

#endif	 
