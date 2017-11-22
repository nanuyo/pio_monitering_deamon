#include "snx_isp/isp_lib_api.h"
#include "snx_gpio.h"

int main(int argc, char* argv[])
{
   int val, newval, error, firstflag=1, doset=1, satu, new_exp_time;

   gpio_pin_info info;

   snx_gpio_open(0);

   info.pinumber = GPIO_PIN_0;
   info.mode = 0;  // 0: input 1: output

    while(1)
    {

    snx_gpio_read(&info);
    sleep(1);
    
//printf ("%d\n",info.value);
    if(firstflag)
    {
        firstflag = 0;
        val = info.value;
        if(info.value) //Day mode
        {
            newval = 128;
           // new_exp_time = 0x493e0;    
        }
        else //night mode
        {
            newval = 350;
            //new_exp_time = 0xfffff;
        }
        snx_isp_filter_saturation_get(&satu);
        doset = 1;
    }
    else
    {
        if(val != info.value)
        {
            val = info.value;
            if(info.value) //Day mode
            {
            newval = 128;    
            //new_exp_time = 0x493e0;    
            }
            else //night mode
            {
            newval = 350;
            //new_exp_time = 0xfffff;
            }
            doset = 1;
        }else
        {
            doset = 0;    
        }
        
    }
    

    
        if(doset)
        {
            error = snx_isp_sensor_redGain_set(newval);

            error = snx_isp_sensor_greenGain_set(newval);

            error = snx_isp_sensor_blueGain_set(newval);

            snx_isp_sensor_gain_set(newval);

           // snx_isp_sensor_exposure_set(new_exp_time);

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

            printf("new gain:%d  \n", newval);
        }

    }
	
	//snx_gpio_close();
#if 0

if(argc == 1)
{
    printf("Please enter gain (min 0 - max: 2047) \n");

error = snx_isp_sensor_redGain_get(&val);
//if(error == 0)    printf("snx_isp_sensor_redGain_get success %d\n", val);    else    printf("snx_isp_sensor_redGain_get fail\n");
error = snx_isp_sensor_greenGain_get(&val);
//if(error == 0)    printf("snx_isp_sensor_greenGain_get success %d\n", val);    else    printf("snx_isp_sensor_greenGain_get fail\n");
error = snx_isp_sensor_blueGain_get(&val);
//if(error == 0)    printf("snx_isp_sensor_blueGain_get success %d\n", val);    else    printf("snx_isp_sensor_blueGain_get fail\n");
printf("current gain:%d  \n", val);

}
else
if(argc == 2)
{
    
    newval = atoi(argv[1]);
    //printf("argc:%d argv[1]:%s newval:%d \n", argc, argv[1], newval );

error = snx_isp_sensor_redGain_set(newval);
//if(error == 0)    printf("snx_isp_sensor_redGain_set success\n");    else    printf("snx_isp_sensor_redGain_set fail\n");
error = snx_isp_sensor_greenGain_set(newval);
//if(error == 0)    printf("snx_isp_sensor_greenGain_set success\n");    else    printf("snx_isp_sensor_greenGain_set fail\n");
error = snx_isp_sensor_blueGain_set(newval);
//if(error == 0)    printf("snx_isp_sensor_blueGain_set success\n");    else    printf("snx_isp_sensor_blueGain_set fail\n");
printf("new gain:%d  \n", newval);

//error = snx_isp_sensor_redGain_get(&val);
//if(error == 0)    printf("snx_isp_sensor_redGain_get success %d\n", val);    else    printf("snx_isp_sensor_redGain_get fail\n");
//error = snx_isp_sensor_greenGain_get(&val);
//if(error == 0)    printf("snx_isp_sensor_greenGain_get success %d\n", val);    else    printf("snx_isp_sensor_greenGain_get fail\n");
//error = snx_isp_sensor_blueGain_get(&val);
//if(error == 0)    printf("snx_isp_sensor_blueGain_get success %d\n", val);    else    printf("snx_isp_sensor_blueGain_get fail\n");

    
    
}
#endif
    return;
}

	 
