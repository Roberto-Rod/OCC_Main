.global    _GoToSleep
.section   .text
.align     4

.equiv SLEEP_MODE, 0x0000
.equiv IDLE_MODE, 0x0001   
   
_GoToSleep:
PWRSAV  #SLEEP_MODE
BRA     TO_FLUSH_QUEUE_LABEL
TO_FLUSH_QUEUE_LABEL:
RETURN
