@cd "..\python"
@python btl_host.py -v -f temp.bin -d pic32mz -i %1 -a 0x9D000000
@exit