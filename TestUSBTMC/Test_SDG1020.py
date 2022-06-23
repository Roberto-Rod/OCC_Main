

"""Pachymeter Automated Software Verification Rig SDG1020 Signal Generator test Harness"""

from pickle import FALSE, TRUE
import pyvisa
import time
from SDG1020_Driver import SDG1020Class

def test_basic_wave():
    # # Connect to SDG1020
    sdg1020_con = SDG1020Class()

    # Set a wave using the following parameters
    # Parameters Channel, Type of wave, Frequency, Amplitude, Offset
    channel     = "C1"
    wave_type   = "RAMP"
    frequency   = "1000000"
    amplitude   = "2"
    offset      = 2.5

    if offset != 0:
        offset_str  = str(offset/2)
    else:
        offset_str = "0"

    # Turn both channels OFF
    sdg1020_con.sdg1020_turn_OFF_channels()

    sdg1020_con.sdg1020_set_basic_wave(channel, wave_type, frequency, amplitude, offset_str)
    # Turn Channel ON for 5 seconds
    sdg1020_con.sdg1020_turn_channel_ON(channel)
    time.sleep(5)

    # Turn Channel output OFF
    sdg1020_con.sdg1020_turn_channel_OFF(channel)

    # Close connection
    sdg1020_con.sdg1020_close_connection()



if __name__ == '__main__':
    """"""
    # test generation of a basic wave
    # test_basic_wave()

    # Test generation of a sweeping wave
    # # Connect to SDG1020
    sdg1020_con = SDG1020Class()

    # Set a wave using the following parameters
    # Parameters Channel, Type of wave, Frequency, Amplitude, Offset, Phase
    channel     = "C1"
    wave_type   = "ARB"
    frequency   = 200
    stop_freq   = 100000
    amplitude   = 2
    offset      = 0
    phase = 0
    sweep_t = 1

    # if offset != 0:
    #     offset_str  = str(offset/2)
    # else:
    #     offset_str = 0

    # Turn both channels OFF
    sdg1020_con.sdg1020_turn_OFF_channels()

    # Send a command
    cmd = ":SWeepWaVe?"
    response = sdg1020_con.sdg1020_send_query(channel , cmd)
    print(response)

    sdg1020_con.sdg1020_set_sweeping_wave(channel, wave_type, frequency, amplitude, offset, phase, sweep_t, stop_freq)

    sdg1020_con.sdg1020_turn_channel_ON(channel)

    #sdg1020_con.sdg1020_send_command(channel, ":SWWV STATE,ON,TIME,10S,START,200HZ,STOP,30000HZ,TRSR,INT,TRMD,OFF,SWMD,LINE,DIR,UP")
    
    
    # sdg1020_con.sdg1020_send_command(channel, ":SWWV TIME,10")
    # sdg1020_con.sdg1020_send_command(channel, ":SWWV START,100")
    # sdg1020_con.sdg1020_send_command(channel, ":SWWV STOP,100000")
    # sdg1020_con.sdg1020_send_command(channel, ":SWWV TRSR MAN")
    # sdg1020_con.sdg1020_send_command(channel, ":SWWV MTRIG")
    # sdg1020_con.sdg1020_send_command(channel, ":SWWV MARK_STATE,ON,MARK_FREQ,1000")

    # Send a command
    #sdg1020_con.sdg1020_send_command("C2", ":SWWV STATE,OFF")
    response = sdg1020_con.sdg1020_send_query(channel, ":SWWV?")
    print(response)

    # Close connection
    sdg1020_con.sdg1020_close_connection()
