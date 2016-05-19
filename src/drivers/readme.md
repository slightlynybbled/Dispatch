# Driver Minimum Functionality #

The purpose of this directory is to hold drivers for different processor architectures.  These
drivers should implement, at minimum, the following functions or their equivalent:

    /**
     * Reads data from the UART receive circular buffer
     * 
     * @param data destination array pointer
     * @param length number of bytes to read
     */
    void read(uint8_t* data, uint16_t length);

    /**
     * Writes data to the UART send circular buffer
     * 
     * @param data source array pointer of the data to write
     * @param length length of the data to write
     */
    void write(uint8_t* data, uint16_t length);

    /**
     * Returns the number of bytes waiting to be read
     * from the UART circuilar buffer
     * 
     * @return length of the data
     */
    uint16_t readable(void);

    /**
     * Returns the number of bytes that can be written
     * @return the number of bytes that can be written
     */
    uint16_t writeable(void);
    
# Driver Initialization #

In addition, it is expected that some sort of initialization function will be necessary to
setup the hardware registers.  As a result, most drivers will have an initialization function:

    /**
     * Initializes the UART
     */
    void init(void);
    
# Additional Considerations #

Finally, there may be additional parameters that may be set up for application-specific behavior.
For instance, in `[uart.h](https://github.com/slightlynybbled/Dispatch/blob/master/src/drivers/pic24dspic33/uart.h)`,
you can see two defines, `TX_BUF_LENGTH` and `RX_BUF_LENGTH` which allow the user to tune the 
UART buffers for the driver based on application resources and requirements.  For devices with multiple
UART options, these might be utilized to select the specific UART hardware or pins.

# Example #

There is a complete example within the [pic24dspic33](https://github.com/slightlynybbled/Dispatch/tree/master/src/drivers/pic24dspic33)
directory which should be a resonable guide.  Note that the example uses a circular buffer which is NOT necessary
to write a correct driver.  Only the minimum interface as described above is necessary for the driver to function.