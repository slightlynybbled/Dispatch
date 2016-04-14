# Purpose #

Dispatch is intended as an easy-to-use serial library that allows a simple exchange
of multi-dimensional, multi-value data.  Dispatch uses the concept of endpoints in
order to get data from the sender to the receiver.

The form of Dispatch was largely inspired by [Telemetry](https://github.com/Overdrivr/Telemetry),
which is described by the author as a publish-subscribe model.

More details may be found at [for(embed)](http://www.forembed.com).

# Project Maturity #

The project is new and has not been fully tested nor optimized.  I expect to add test
cases within the next couple of weeks.

# Example Usage #

    #!c
    uint8_t myData[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    DIS_publish("topic:10,u8", myData);
    
A more complete example may be found within the 'examples' directory.