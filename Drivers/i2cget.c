
		
		          if ((devicestop = open("/dev/i2c-1", O_RDWR)) < 0)
  		  {
  			  perror("open() failed");
    			  exit (1);
  		  }
		
		if (ioctl(devicestop, I2C_SLAVE, PORTMOTORSTART) < 0)
      		   perror("ioctl() I2C_SLAVE failed in stop call\n");
    		else {
			resultLength = i2c_smbus_read_i2c_block_data(devicestop,0x24,0x24,rawData);
			printf("rawData[0]  %d \n",rawData[0]);
			printf("resultLength %d\n", resultLength);
			close(devicestop);
		}
		
		if ((device = open("/dev/i2c-1", O_RDWR)) < 0)
  		  {
  			  perror("open() failed");
    			  exit (1);
  		  }
			printf("device %d\n", device);
			if (ioctl(device, I2C_SLAVE, PORTMOTORSTART) < 0)
      		   perror("ioctl() I2C_SLAVE failed in the start call\n");
    		else {
			resultLength = i2c_smbus_read_i2c_block_data(device,0x25,0x25,rawData);
			printf("rawData[0]  %d \n",rawData[0]);
			printf("resultLength %d\n", resultLength);
					
		}	
